#include "Graal.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Graal::Graal(int i, int j, int num) : id(num)
{
    x = i;
    y = j;
    persistent = true;
    alive = true;
    ready = true;

    vanim = 120;
    animMax = 7;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);
}

Graal::~Graal()
{
    ResourceManager::getInstance()->free(image);
}

void Graal::loop()
{
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

void Graal::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }
    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, 16 * anim, 112, 16, 16, dstX, dstY);
}

void Graal::action()
{
    getLink()->trouveObjet(TI_GRAAL, id);
    alive = false;
}

bool Graal::isPickable()
{
    return false;
}
