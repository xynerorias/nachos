#include "syscall.h"

int main() {
    PutString("Bonjour Nachos!\n");
    {
        int i;
        for (i = 0; i < 30; i++) {
            PutChar('x');
        }
    }

    PutChar('\n');
    //Halt();
    return 0;
}
