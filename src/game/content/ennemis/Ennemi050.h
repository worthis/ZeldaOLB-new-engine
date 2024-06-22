/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI050_H__
#define __ENNEMI050_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi050 : public Ennemi
{
public:
    Ennemi050(int x, int y);
    ~Ennemi050();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

protected:
    void beforeHit(TypeAttack typeAtt, TypeEffect effect);
    void afterHit();

    void giveItem(int x, int y);

private:
    int anim;
    int animMax;
    int vanim;

    WImage *image;

    Chrono chrono;

    BoundingBox box;

    bool snipeMode;
    int cooldown;
};

#endif // Ennemi050.h
