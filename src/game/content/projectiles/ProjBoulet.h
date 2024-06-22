/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJBOULET_H__
#define __PROJBOULET_H__

#include "../types/Projectile.h"

class ProjBoulet : public Projectile
{
public:
    ProjBoulet(int x, int y, Direction dir);
    ~ProjBoulet();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

private:
    int speed;
    int dx;
    int dy;
    int level;
    int force;
};

#endif // ProjBoulet.h
