/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GRAAL_H__
#define __GRAAL_H__

#include "../types/Item.h"

class Graal : public Item
{
public:
    Graal(int x, int y, int id);
    ~Graal();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();

private:
    int id;
};

#endif // Graal.h
