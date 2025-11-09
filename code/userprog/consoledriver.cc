#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *g_readAvail;
static Semaphore *g_writeDone;

static void ReadAvailHandler(void *arg)
{
  (void)arg;
  g_readAvail->V();
}
static void WriteDoneHandler(void *arg)
{
  (void)arg;
  g_writeDone->V();
}

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);

  writeLock = new Semaphore("write lock", 1);
  readLock = new Semaphore("read lock", 1);

  g_readAvail = readAvail;
  g_writeDone = writeDone;

  console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

ConsoleDriver::~ConsoleDriver()
{
  delete console;

  delete writeDone;
  delete readAvail;

  delete writeLock;
  delete readLock;
}

void ConsoleDriver::PutChar(int ch)
{
  writeLock->P();

  console->TX(ch);
  writeDone->P(); // attendre fin d’ecriture

  writeLock->V();
}

int ConsoleDriver::GetChar()
{
  readLock->P();

  readAvail->P();        // attendre qu’un caractere arrive
  int c = console->RX(); // puis le lire

  readLock->V();
  return c;
}

void ConsoleDriver::PutString(const char *s)
{
  // Pas besoin de proteger avec un semaphore car on le fait dans PutChar
  while (*s != '\0')
  {
    consoledriver->PutChar(*s);
    s++;
  }
}

void ConsoleDriver::GetString(char *s, int n)
{
  // Pas besoin de proteger avec un semaphore car on le fait dans GetChar
  if (n <= 0)
    return;
  int i = 0;

  while (i < n - 1)
  {
    int c = GetChar();
    if (c == EOF)
      break;
    s[i++] = (char)c;
    if ((char)c == '\n')
      break;
  }
  s[i] = '\0';
}

#endif
