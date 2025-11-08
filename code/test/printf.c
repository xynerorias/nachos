#include "syscall.h"
#include <stdarg.h>

#define MAX_BUFFER_SIZE 256

extern int vsprintf(char *buf, const char *fmt, va_list args);

int printf(const char *fmt, ...)
{
    // On definit un buffer local pour stocker la chaine
    char buffer[MAX_BUFFER_SIZE];

    // D'apres 'man va_start', on doit declarer une variable de type va_list
    va_list args;
    // On doit ensuite appeler va_start en lui passant la va-list et le dernier argument avant les "..."
    va_start(args, fmt);
    // On utilisr maintenant vsprintf que l'on a récupéré pour ecrire dans le buffer
    int len = vsprintf(buffer, fmt, args);
    // On appelle enfin va_end pour nettoyer la va_list (toujours d'après le 'man va_start')
    va_end(args);

    // On utilise PutString que l'on a implémenté pour afficher le buffer
    PutString(buffer);
    return len;
}

int main()
{
    printf("Hello Nachos!\n");
    printf("Number: %d\n", 42);
    Halt();
    return 0;
}
