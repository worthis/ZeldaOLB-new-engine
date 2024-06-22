/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI058_H__
#define __ENNEMI058_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi058 : public Ennemi
{
public:
    Ennemi058(int x, int y);
    ~Ennemi058();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();
    void setResetableToFalse();
    bool isHittable();

private:
    int anim;
    int animMax;
    int vanim;
    bool resetable;

    WImage *image;

    Chrono chrono;

    BoundingBox box;

    int cooldown;
};

#endif // Ennemi058.h
