/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJECLAIR_H__
#define __PROJECLAIR_H__

#include "../types/Projectile.h"

class ProjEclair : public Projectile {
    public :
        ProjEclair(int x, int y);
        ~ProjEclair();

        void projLoop();
        void draw(int offsetX, int offsetY);

        BoundingBox* getBoundingBox();

        int getX();
        int getY();
        int getDown();

    private :

        int force;
};

#endif  // ProjEclair.h
