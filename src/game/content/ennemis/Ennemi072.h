/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2022  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI072_H__
#define __ENNEMI072_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi072 : public Ennemi
{
public:
    Ennemi072(int x, int y);
    ~Ennemi072();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    void pousseX(int dx);
    void pousseY(int dy);

protected:
    void afterFall();

private:
    int anim;
    int animMax;
    int vanim;

    int cooldown;
    bool jump;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi072.h
