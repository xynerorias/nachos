#include "syscall.h"

void threadFunction(void *arg)
{
    PutChar('A'); // simple affichage
    ThreadExit(); // fin du thread utilisateur
}

int main()
{
    ThreadCreate(threadFunction, 0); // crée un thread qui affiche 'A'

    // boucle infinie pour empêcher le thread principal de finir trop tôt
    while (1)
    {
        // on peut même faire une petite attente active
    }

    return 0;
}
