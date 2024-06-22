/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../../../engine/util/geometry/BoundingBox.h"

#include "../../keys/Action.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);

    void setBox(int x, int y, int w, int h);
    void setPosition(int x, int y);

    void moveTo(int x, int y, int v = 2);

    void setBounds(int x, int y, int w, int h);

    BoundingBox *getBoundingBox();

    void handleAction(Action *action, int x, int y);
    void loop();

    bool isManuel();
    void setManuel(bool b);

private:
    int vitesse;
    int targetX;
    int targetY;
    bool manuel;

    BoundingBox box;
    BoundingBox bounds;
};

#endif // Camera.h
