#include "FumeeRose.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

FumeeRose::FumeeRose(int x, int y) : x(x - 14), y(y - 14), anim(0), animMax(2), vanim(60)
{
    image = ResourceManager::getInstance()->loadImage("data/images/effects/exploLapin.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 28;
    height = 28;
}

FumeeRose::~FumeeRose()
{
    ResourceManager::getInstance()->free(image);
}

void FumeeRose::loop()
{
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            alive = false;
        }
        chrono.reset();
    }
}

void FumeeRose::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, width * anim, 0, width, height, dstX, dstY);
}

int FumeeRose::getX() { return x; }
int FumeeRose::getY() { return y; }
