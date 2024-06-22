#include "Triforce.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Triforce::Triforce(int i, int j)
{

    x = i;
    y = j - 10;
    persistent = false;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 26;
    height = 36;

    box.setX(x);
    box.setY(y + 10);
    box.setW(26);
    box.setH(26);

    ready = false;
}

Triforce::~Triforce()
{
    ResourceManager::getInstance()->free(image);
}

void Triforce::loop()
{
    if (!ready)
    {
        if (chrono.getElapsedTime() >= vanim)
        {
            anim++;
            if (anim > animMax)
            {
                ready = true;
            }
            chrono.reset();
        }
    }
}

void Triforce::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (ready)
    {
        dstY += 10;
    }
    else
    {
        if (anim <= 10)
            dstY += anim;
        else if (anim <= 14)
            dstY += 10 - (anim - 10);
        else if (anim <= 18)
            dstY += 6 + (anim - 14);
        else
            dstY += 10;
    }

    WindowManager::getInstance()->draw(image, 24, 3, 6, 4, dstX + 10, y - offsetY + 34);
    WindowManager::getInstance()->draw(image, 128, 86, 26, 26, dstX, dstY);
}

void Triforce::action()
{
    if (!ready)
        return;
    getLink()->trouveObjet(TI_TRIFORCE);
    alive = false;
}

bool Triforce::isPickable()
{
    return false;
}
