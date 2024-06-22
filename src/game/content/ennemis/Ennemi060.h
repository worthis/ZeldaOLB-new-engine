/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI060_H__
#define __ENNEMI060_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi060 : public Ennemi {
    public :
        Ennemi060(int x, int y);
        ~Ennemi060();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

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

#endif  // Ennemi060.h

