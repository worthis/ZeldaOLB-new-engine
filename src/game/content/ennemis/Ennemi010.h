/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI010_H__
#define __ENNEMI010_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi010 : public Ennemi
{
public:
    Ennemi010(int x, int y);
    ~Ennemi010();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();

private:
    int cooldown;

    WImage *image;

    BoundingBox box;
};

#endif // Ennemi010.h
