/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI027_H__
#define __ENNEMI027_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi027 : public Ennemi
{
public:
    Ennemi027(int x, int y);
    ~Ennemi027();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();

private:
    int anim;
    int animMax;
    int vanim;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi027.h
