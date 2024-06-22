/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __BOMB_H__
#define __BOMB_H__

#include "../types/Item.h"

class Bomb : public Item
{
public:
    Bomb(int x, int y);
    ~Bomb();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // Bomb.h
