/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2018  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __BARRIERE_H__
#define __BARRIERE_H__

#include "../types/Object.h"
#include "../scene/Map.h"

#include "../../../engine/util/time/Chrono.h"

class Barriere : public Object {
    public :
        Barriere(int x, int y, Map* map);
        ~Barriere();

        void loop();

        void draw(int offsetX, int offsetY);

        BoundingBox* getBoundingBox();

        void underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect);

    private :

        int anim;
        int animMax;
        int vanim;

        int force;

        Chrono chrono;
};

#endif  // Barriere.h
