#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "usercopy.h"

unsigned copyStringFromMachine(int from, char *to, unsigned size) {
  if (size == 0) return 0;
  unsigned i = 0;
  int byte; // ReadMem ecrit dans un int*, pas un char*
  for (; i < size - 1; ++i, ++from) {
    if (!machine->ReadMem(from, 1, &byte)) break; // lecture invalide:stop
    to[i] = (char)(byte & 0xFF);
    if (to[i] == '\0') return i;                  // fin trouvée
  }
  to[i] = '\0';                                   // terminaison sure
  return i;
}

unsigned copyStringToMachine(int to, const char *from, unsigned size) {
  if (size == 0) return 0;
  unsigned i = 0;
  //au plus size-1 chars et forcer '\0'
  for (; i < size - 1 && from[i] != '\0'; ++i) {
    if (!machine->WriteMem(to + i, 1, (int)(unsigned char)from[i])) break;
  }
  int zero = 0;
  machine->WriteMem(to + i, 1, zero);  // forcer '\0'
  return i; //nb de caracteres ecrits (sans '\0')
}

#endif // CHANGED
