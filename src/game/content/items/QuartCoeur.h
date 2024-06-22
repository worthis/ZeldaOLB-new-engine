/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __QUARTCOEUR_H__
#define __QUARTCOEUR_H__

#include "../types/Item.h"

class QuartCoeur : public Item
{
public:
    QuartCoeur(int x, int y, int id);
    ~QuartCoeur();

    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();

private:
    int id;
};

#endif // QuartCoeur.h
