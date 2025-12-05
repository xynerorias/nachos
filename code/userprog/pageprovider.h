#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"

class PageProvider {
public:
    PageProvider(int numPhysPages);
    ~PageProvider();

    int GetEmptyPage();     // retourne un numéro de page physique libre
    void ReleasePage(int p); // libère une page physique
    int NumAvailPage();
private:
    BitMap *bitmap;
};

#endif // PAGEPROVIDER_H
