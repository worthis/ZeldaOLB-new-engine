/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI011_H__
#define __ENNEMI011_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi011 : public Ennemi {
    public :
        Ennemi011(int x, int y, bool actif = false);
        ~Ennemi011();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        void reset();

    private :

        int anim;
        int animMax;
        int vanim;

        bool actif;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi011.h

