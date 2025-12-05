#include "system.h"
#include "userthread.h"
#include "addrspace.h"

struct ThreadParams
{
    int f;
    int arg;
};

int do_ThreadCreate(int f, int arg)
{
    // On check si l'adresse espace est valide
    if (currentThread->space == nullptr)
    {
        return -1;
    }

    // On crée les parametres à passer au thread
    ThreadParams *params = new ThreadParams();
    params->f = f;
    params->arg = arg;

    // On cree le thread
    Thread *newThread = new Thread("new user thread");

    // On vérifie que le thread a bien été créé
    if (newThread == nullptr)
    {
        delete params;
        return -1;
    }

    // On donne le meme espace d'adresse au nouveau thread
    newThread->space = currentThread->space;

    // On incremente le compteur de thread dans l'espace d'adresse
    newThread->space->incrementThreadCount();

    DEBUG('x', "do_ThreadCreate: created thread %s in address space %p\n",
          newThread->getName(), newThread->space);

    // Et on le start enfin en lui donnant les parametres
    newThread->Start(StartUserThread, (void *)params);

    return 0;
}

void do_ThreadExit()
{
    DEBUG('x', "Thread %s finishing\n", currentThread->getName());

    // On decremente le compteur de thread, désalloue la pile utilisateur, et on termine le thread
    currentThread->space->decrementThreadCount();
    currentThread->space->DeallocateUserStack(machine->ReadRegister(StackReg));
    currentThread->Finish();
}

static void StartUserThread(void *schmurtz)
{
    // On récupère les paramètres
    ThreadParams *params = (ThreadParams *)schmurtz;
    DEBUG('x', "StartUserThread: f=%d arg=%d\n", params->f, params->arg);

    // On initialise les registres
    currentThread->space->InitRegisters();

    // On positionne le PC et NextPC comme dans InitRegisters
    machine->WriteRegister(PCReg, params->f);
    machine->WriteRegister(NextPCReg, params->f + 4);

    // On alloue une pile utilisateur
    int userStackAddress = currentThread->space->AllocateUserStack();
    machine->WriteRegister(StackReg, userStackAddress);

    // On passe l'argument dans r4
    machine->WriteRegister(4, params->arg);

    // Debug pour voir les valeurs des registres
    DEBUG('x', "StartUserThread: PCReg=%d StackReg=%d argument=%d\n",
          machine->ReadRegister(PCReg),
          machine->ReadRegister(StackReg),
          machine->ReadRegister(4));

    // On libère les paramètres
    delete params;

    // On lance le thread utilisateur
    machine->Run();
}