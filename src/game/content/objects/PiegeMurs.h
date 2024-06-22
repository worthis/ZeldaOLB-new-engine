/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEMURS_H__
#define __PIEGEMURS_H__

#include "../types/Object.h"
#include "../scene/Map.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeMurs : public Object
{
public:
    PiegeMurs(int x, int y, Map *map, Direction dir = E);
    ~PiegeMurs();

    void loop();

    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    bool isResetable();
    void reset();

    int getDown();

    Direction getDirection();

private:
    int anim;
    int animMax;
    int vanim;

    Chrono chrono;

    Direction direction;

    PiegeMurs *other;

    int x0;
};

#endif // PiegeMurs.h
