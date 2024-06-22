/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRANSITIONROOMS_H__
#define __TRANSITIONROOMS_H__

#include "../../content/CommonGame.h"
#include "../../content/scene/Camera.h"

class TransitionRooms
{
public:
    TransitionRooms();
    ~TransitionRooms();

    void loop();

    void init();

private:
    Camera *camera;
    int dstX;
    int dstY;
    int moveLink;
    Direction direction;
};

#endif // TransitionRooms.h
