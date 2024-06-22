/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2022  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI074_H__
#define __ENNEMI074_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi074 : public Ennemi {
    public :
        Ennemi074(int x, int y);
        ~Ennemi074();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();
        BoundingBox* getBoundingBoxTail();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        void start();

    protected :

        void giveItem(int x, int y);

    private :

        int anim;
        int animMax;
        int vanim;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
        BoundingBox tail;

        int cooldown;
};

#endif  // Ennemi074.h
