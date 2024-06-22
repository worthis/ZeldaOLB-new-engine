#include "Splash.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Splash::Splash(int i, int j) : x(i), y(j), anim(0), animMax(3), vanim(40)
{
    image = ResourceManager::getInstance()->loadImage("data/images/effects/splash.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

Splash::~Splash()
{
    ResourceManager::getInstance()->free(image);
}

void Splash::loop()
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

void Splash::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }
    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, x - offsetX, y - offsetY);
}

int Splash::getX()
{
    return x;
}

int Splash::getY()
{
    return y;
}
