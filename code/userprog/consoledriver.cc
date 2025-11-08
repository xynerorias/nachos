#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg)
{
  (void)arg;
  readAvail->V();
}
static void WriteDoneHandler(void *arg)
{
  (void)arg;
  writeDone->V();
}

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);
  console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

ConsoleDriver::~ConsoleDriver()
{
  delete console;
  delete writeDone;
  delete readAvail;
}

void ConsoleDriver::PutChar(int ch)
{
  console->TX(ch);
  writeDone->P(); // attendre fin d’ecriture
}

int ConsoleDriver::GetChar()
{
  readAvail->P();       // attendre qu’un caractere arrive
  return console->RX(); // puis le lire
}

void ConsoleDriver::PutString(const char *s)
{
  while (*s != '\0')
  {
    consoledriver->PutChar(*s);
    s++;
  }
}

void ConsoleDriver::GetString(char *s, int n)
{
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

#endif // CHANGED
