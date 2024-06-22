/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI040_H__
#define __ENNEMI040_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi040 : public Ennemi
{
public:
    Ennemi040(int x, int y);
    ~Ennemi040();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

protected:
    void giveItem(int x, int y);

private:
    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    WImage *image;

    Chrono chrono;

    BoundingBox box;

    int cooldown;
};

#endif // Ennemi040.h
