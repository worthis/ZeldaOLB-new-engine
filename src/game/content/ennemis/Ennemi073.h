/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2022  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI073_H__
#define __ENNEMI073_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"
#include "Ennemi074.h"

class Map;

class Ennemi073 : public Ennemi {
    public :
        Ennemi073(int x, int y, Map* map);
        ~Ennemi073();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();
        BoundingBox* getBoundingBoxTail();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    protected :

        void giveItem(int x, int y);

        void afterHit();

    private :

        int anim;
        int animMax;
        int vanim;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
        BoundingBox tail;

        Ennemi074* otherBoss;

        int cooldown;
};

#endif  // Ennemi073.h
