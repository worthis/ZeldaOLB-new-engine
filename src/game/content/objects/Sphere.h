/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "../types/Object.h"

class Sphere : public Object {
    public :
        Sphere(int x, int y);
        ~Sphere();

        void loop();
        void draw(int offsetX, int offsetY);

        void underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect);

        void setBlue(bool b);

    private :

        bool blue;
        int invul; // 16 to 0 when activated
};

#endif  // Sphere.h
