/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJFEULONG_H__
#define __PROJFEULONG_H__

#include "../types/Projectile.h"

class ProjFeuLong : public Projectile
{
public:
    ProjFeuLong(int x, int y, Direction dir, bool byLink = false);
    ~ProjFeuLong();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

private:
    int speed;
    int dx;
    int dy;
    int level;
    int force;
    bool byLink;
};

#endif // ProjFeuLong.h
