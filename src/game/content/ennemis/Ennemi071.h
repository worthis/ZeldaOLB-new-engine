/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2022  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI071_H__
#define __ENNEMI071_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi071 : public Ennemi
{
public:
    Ennemi071(int x, int y);
    ~Ennemi071();

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
    int anim;
    int animMax;
    int vanim;

    int beforeMove;
    int moving;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi071.h
