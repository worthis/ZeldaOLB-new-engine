/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRIFORCE_H__
#define __TRIFORCE_H__

#include "../types/Item.h"

class Triforce : public Item
{
public:
    Triforce(int x, int y);
    ~Triforce();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();
};

#endif // Triforce.h
