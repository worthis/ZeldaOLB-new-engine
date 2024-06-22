/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2022  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI075_H__
#define __ENNEMI075_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi075 : public Ennemi {
    public :
        Ennemi075(int x, int y);
        ~Ennemi075();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        void catchToMask();

    protected :

        void giveItem(int x, int y);

        void afterHit();

    private :

        int anim;
        int animMax;
        int vanim;

        int animSword;
        bool isKo;
        int speed;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi075.h
