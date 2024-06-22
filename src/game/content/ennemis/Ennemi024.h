/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI024_H__
#define __ENNEMI024_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi024 : public Ennemi {
    public :
        Ennemi024(int x, int y, bool water);
        ~Ennemi024();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool isToAvoid(Collision c);

    private :

        void moveX(int dx);
        void moveY(int dy);

        int anim;
        int animMax;
        int vanim;

        WImage* image;

        Chrono chrono;

        BoundingBox box;

        bool inWater;
        int vitesse;
};

#endif  // Ennemi024.h
