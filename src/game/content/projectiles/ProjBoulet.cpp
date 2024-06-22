#include "ProjBoulet.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjBoulet::ProjBoulet(int i, int j, Direction dir) : speed(2), dx(0), dy(0), force(2)
{
    x = i;
    y = j;
    direction = dir;

    // for quadtree operations:
    width = 8;
    height = 13;

    switch (direction)
    {
    case N:
        dy = -speed;
        break;
    case S:
        dy = speed;
        break;
    case W:
        dx = -speed;
        break;
    case E:
        dx = speed;
        break;
    }

    box.setW(8);
    box.setH(8);

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/boulet.png", true);
}

ProjBoulet::~ProjBoulet()
{
    ResourceManager::getInstance()->free(image);
}

void ProjBoulet::projLoop()
{
    if (!alive)
    {
        return;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->testDegatOnLink(getBoundingBox(), direction, force, TA_PHYSIC, TE_NORMAL))
    {
        alive = false;
        return;
    }

    if (scene->checkCollisions(getBoundingBox(), (Collisionable *)this, false))
    {
        x += dx;
        y += dy;
    }
    else
    {
        alive = false;
        return;
    }
}

void ProjBoulet::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 0, 0, width, height, dstX, dstY);
}

BoundingBox *ProjBoulet::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 5);
    return &box;
}
