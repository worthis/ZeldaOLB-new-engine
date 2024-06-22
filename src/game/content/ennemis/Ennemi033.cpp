#include "Ennemi033.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi033::Ennemi033(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi33.png", true);
    chrono.reset();

    type = 33;

    x = i;
    y = j;

    // for quadtree operations:
    width = 22;
    height = 25;

    box.setX(x + 3);
    box.setY(y + 9);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 10;
    maxLife = 10;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_RUBIS_BLEU, 40);
    items.addType(TI_MAGIE_PEU, 20);
    items.addType(TI_FLECHE, 10);

    forceEnn = 6;
}

Ennemi033::~Ennemi033()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi033::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi033::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist)
    {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox()))
        {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }
    }
    else
    {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi033::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height + (gel ? height * 2 : 0), width, height, dstX, dstY);
}

int Ennemi033::getX()
{
    return x;
}

int Ennemi033::getY()
{
    return y;
}

BoundingBox *Ennemi033::getBoundingBox()
{
    box.setX(x + 3);
    box.setY(y + 9);
    return &box;
}
