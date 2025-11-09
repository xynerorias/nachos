#include "syscall.h"

// Le max est UserStacksAreaSize divisé par stackSlotSize (donc maintenant 2048/256 = 8)
// Voir addrspace.cc pour plus de détails sur stackSlotSize
// Voir addrspace.h pour changer UserStacksAreaSize
#define NB_THREADS 5

void threadFunction(void *arg)
{
    int i;
    int id = (int)arg;

    for (i = 0; i < 10; i++)
    {
        PutChar('A' + id);
    }
    PutChar('\n');

    ThreadExit();
}

int main(int argc, char **argv)
{
    int i;
    for (i = 0; i < NB_THREADS; i++)
    {
        ThreadCreate(threadFunction, i);
    }

    for (i = 0; i < 10; i++)
    {
        PutChar('0');
    }
    PutChar('\n');

    ThreadExit();
    return 0;
}
