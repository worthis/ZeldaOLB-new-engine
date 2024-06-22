/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI035_H__
#define __ENNEMI035_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi035 : public Ennemi
{
public:
    Ennemi035(int x, int y);
    ~Ennemi035();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

private:
    int anim;
    int animMax;
    int vanim;

    int beforeMove;
    int moving;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi035.h
