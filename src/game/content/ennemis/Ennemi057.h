/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI057_H__
#define __ENNEMI057_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../scene/Map.h"

#include "../types/Ennemi.h"
#include "Ennemi058.h"

class Ennemi057 : public Ennemi {
    public :
        Ennemi057(int x, int y, Map* map);
        ~Ennemi057();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

    protected :

        void giveItem(int x, int y);

        void afterHit();

    private :

        void addEnnemi(int i);
        bool tryToAddEnnemi(int x, int y, int i);

        int anim;
        int animMax;
        int vanim;

        WImage* image;
        WImage* imageBis;

        Ennemi058* ennemis[3];

        Chrono chrono;

        BoundingBox box;

        int cooldown;
        bool encyclopedie;
};

#endif  // Ennemi057.h
