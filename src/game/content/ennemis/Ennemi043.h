/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI043_H__
#define __ENNEMI043_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi043 : public Ennemi {
    public :
        Ennemi043(int x, int y);
        ~Ennemi043();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool isCollision(Collision c);
        bool isToAvoid(Collision c);

    protected :

        void giveItem(int x, int y);

    private :

        int anim;
        int animMax;
        int vanim;

        int beforeMove;
        int moving;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi043.h
