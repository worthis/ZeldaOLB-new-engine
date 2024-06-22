/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI016_H__
#define __ENNEMI016_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi016 : public Ennemi
{
public:
    Ennemi016(int x, int y);
    ~Ennemi016();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

private:
    int cooldown;

    WImage *image;

    BoundingBox box;
};

#endif // Ennemi016.h
