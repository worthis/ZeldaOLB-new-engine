#include "ProjLapin.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjLapin::ProjLapin(int i, int j, double dx, double dy) : dx(dx), dy(dy)
{
    x = i - 11;
    y = j - 11;
    longX = i;
    longY = j;

    if (dx > 0)
    {
        if (dy > 0)
        {
            if (dx > dy)
                direction = E;
            else
                direction = S;
        }
        else
        {
            if (dx > -dy)
                direction = E;
            else
                direction = N;
        }
    }
    else
    {
        if (dy > 0)
        {
            if (-dx > dy)
                direction = W;
            else
                direction = S;
        }
        else
        {
            if (-dx > -dy)
                direction = W;
            else
                direction = N;
        }
    }

    // for quadtree operations:
    width = 22;
    height = 22;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    vanim = 120;
    anim = 0;
    animMax = 1;
    chrono.reset();

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/lapin.png", true);
}

ProjLapin::~ProjLapin()
{
    ResourceManager::getInstance()->free(image);
}

void ProjLapin::projLoop()
{
    if (!alive)
    {
        return;
    }

    int oldX = x;
    int oldY = y;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // compute bounding box for collisions
    box.setX(longX - 11 + dx);
    box.setY(longY - 11 + dy);

    longX += dx;
    longY += dy;

    x = longX - 11;
    y = longY - 11;

    if (scene->testDegatOnLink(getBoundingBox(), N, 0, TA_MAGIC, TE_LAPIN) || scene->testDegat(getBoundingBox(), N, 0, TA_MAGIC, TE_LAPIN, false))
    {
        alive = false;
        return;
    }

    if (!scene->checkCollisions(&box, (Collisionable *)this, false, false, false, false, false))
    {

        BoundingBox b2(oldX, oldY, 22, 22);

        b2.setY(y);
        if (!scene->checkCollisions(&b2, (Collisionable *)this, false, false, false, false, false))
        {
            dy = -dy;
        }

        b2.setY(oldY);
        b2.setX(x);
        if (!scene->checkCollisions(&b2, (Collisionable *)this, false, false, false, false, false))
        {
            dx = -dx;
        }
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void ProjLapin::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = longX - 11 - offsetX;
    int dstY = longY - 11 - offsetY;

    WindowManager::getInstance()->draw(image, 0, anim * 22, 22, 22, dstX, dstY);
}

BoundingBox *ProjLapin::getBoundingBox()
{
    box.setX(longX - 11);
    box.setY(longY - 11);
    return &box;
}

int ProjLapin::getX() { return x; }
int ProjLapin::getY() { return y; }
int ProjLapin::getDown() { return y + 240; }
