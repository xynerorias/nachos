#ifdef CHANGED
#ifndef CONSOLEDRIVER_H
#define CONSOLEDRIVER_H

#include "copyright.h"
#include "utility.h"
#include "console.h"

class Semaphore;

class ConsoleDriver : dontcopythis
{
public:
  // initialize the hardware console device
  ConsoleDriver(const char *readFile, const char *writeFile);
  ~ConsoleDriver(); // clean up

  void PutChar(int ch); // like putchar(3S)
  int GetChar();        // like getchar(3S)

  void PutString(const char *s);  // like fputs(3S)
  void GetString(char *s, int n); // like fgets(3S)

private:
  Console *console;
  Semaphore *readAvail;
  Semaphore *writeDone;
  Semaphore *writeLock;
  Semaphore *readLock;
};

#endif // CONSOLEDRIVER_H
#endif // CHANGED
