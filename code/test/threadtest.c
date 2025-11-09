#include "syscall.h"

void threadFunction(void *arg)
{
    int i;
    int id = (int)arg;

    for (i = 0; i < 5; i++)
    {
        PutChar('A' + id);
    }
    PutChar('\n');

    ThreadExit();
}

int main()
{
    ThreadCreate(threadFunction, 0);

    int i;
    for (i = 0; i < 5; i++)
    {
        PutChar('0');
    }
    PutChar('\n');

    ThreadExit();

    PutString("Si on voit ça dans la console, big problème\n");
    return 0;
}
