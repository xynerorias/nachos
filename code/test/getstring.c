#include "syscall.h"
#define N 64
int main() {
  char buf[N];
  PutString("Texte:\n");
  GetString(buf, N);
  PutString("Texte ecrit: ");
  PutString(buf);
  return 0;
}
