#include "syscall.h"

void threadFunction(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        PutChar('A');
    }
    ThreadExit();
}

int main()
{
    ThreadCreate(threadFunction, 0);
    while (1)
        ;
    return 0;
}
