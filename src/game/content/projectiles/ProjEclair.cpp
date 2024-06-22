#include "ProjEclair.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjEclair::ProjEclair(int i, int j)
{
    x = i - 41;
    y = j;

    // for quadtree operations:
    width = 83;
    height = 148;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    vanim = 40;
    anim = 0;
    animMax = 4;
    chrono.reset();

    force = 4;

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/eclair.png", true);
}

ProjEclair::~ProjEclair()
{
    ResourceManager::getInstance()->free(image);
}

void ProjEclair::projLoop()
{
    if (!alive)
    {
        return;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    scene->testDegatOnLink(getBoundingBox(), direction, force, TA_MAGIC, TE_ELECTRIC);

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            alive = false;
        }
        chrono.reset();
    }
}

void ProjEclair::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

BoundingBox *ProjEclair::getBoundingBox()
{
    return &box;
}

int ProjEclair::getX() { return x; }
int ProjEclair::getY() { return y; }
int ProjEclair::getDown() { return y + 240; }
