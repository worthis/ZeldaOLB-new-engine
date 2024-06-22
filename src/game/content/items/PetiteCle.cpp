#include "PetiteCle.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

PetiteCle::PetiteCle(int i, int j, int id, bool withAnim) : id(id)
{
    x = i;
    y = j - 10;
    persistent = false;
    alive = true;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 8;
    height = 26;

    box.setX(x);
    box.setY(y + 10);
    box.setW(8);
    box.setH(16);

    ready = !withAnim;
}

PetiteCle::~PetiteCle()
{
    ResourceManager::getInstance()->free(image);
}

void PetiteCle::loop()
{
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            if (!ready)
            {
                ready = true;
            }
            anim = 0;
        }
        chrono.reset();
    }
}

void PetiteCle::draw(int offsetX, int offsetY)
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

    WindowManager::getInstance()->draw(image, 24, 3, 6, 4, dstX + 1, y - offsetY + 22);
    WindowManager::getInstance()->draw(image, 100, 48, 8, 16, dstX, dstY);
}

void PetiteCle::action()
{
    if (!ready)
        return;
    getLink()->trouveObjet(TI_CLE, id);
    alive = false;
}
