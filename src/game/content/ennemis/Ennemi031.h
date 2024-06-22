/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI031_H__
#define __ENNEMI031_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi031 : public Ennemi {
    public :
        Ennemi031(int x, int y);
        ~Ennemi031();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    protected :

        void giveItem(int x, int y);

        void afterHit();

    private :

        void snipe();

        int anim;
        int animMax;
        int vanim;

        int attLapin;
        int attEclair;
        int nbHit;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi031.h
