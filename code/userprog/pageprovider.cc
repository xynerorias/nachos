#include "pageprovider.h"
#include "system.h"
#include <string.h> // memset

PageProvider::PageProvider(int numPhysPages)
{
    bitmap = new BitMap(numPhysPages);
}

PageProvider::~PageProvider()
{
    delete bitmap;
}

int PageProvider::GetEmptyPage()
{
    int page = bitmap->Find();  // Cherche un bit à 1 -> page libre

    if (page == -1)
        return -1; // Plus de pages disponibles

    ASSERT(page >= 0 && page < NumPhysPages);

    // On remet à zéro la page physique
    memset(&machine->mainMemory[page * PageSize], 0, PageSize);

    return page;
}

void PageProvider::ReleasePage(int p)
{
    ASSERT(p >= 0 && p < NumPhysPages);
    bitmap->Clear(p);
}

int PageProvider::NumAvailPage()
{
    return bitmap->NumClear();
}
