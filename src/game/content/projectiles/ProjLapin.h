/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJLAPIN_H__
#define __PROJLAPIN_H__

#include "../types/Projectile.h"

class ProjLapin : public Projectile
{
public:
    ProjLapin(int x, int y, double dx, double dy);
    ~ProjLapin();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    int getX();
    int getY();
    int getDown();

private:
    int speed;
    double dx;
    double dy;
    double longX;
    double longY;
};

#endif // ProjLapin.h
