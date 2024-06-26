/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJBOULEFEU_H__
#define __PROJBOULEFEU_H__

#include "../types/Projectile.h"

class ProjBouleFeu : public Projectile
{
public:
    ProjBouleFeu(int x, int y, double dx, double dy, BoundingBox *safeBox = 0);
    ~ProjBouleFeu();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    int getX();
    int getY();
    int getDown();

    void renvoie(Direction dir);

private:
    int speed;
    double dx;
    double dy;
    int force;
    int parcouru;
    double histX[16];
    double histY[16];
    double longX;
    double longY;
    bool retour;
    BoundingBox *safeBox;
};

#endif // ProjBouleFeu.h
