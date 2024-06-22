#include "Ennemi032.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi032::Ennemi032(int i, int j) : anim(0), animMax(2), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi32.png", true);
    chrono.reset();

    type = 32;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 23;

    box.setX(x);
    box.setY(y + 7);
    box.setW(width);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 5;
    maxLife = 5;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_RUBIS_VERT, 40);
    items.addType(TI_RUBIS_BLEU, 20);
    items.addType(TI_RUBIS_ROUGE, 10);

    forceEnn = 4;
}

Ennemi032::~Ennemi032()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi032::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi032::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + (width / 2) - dstX) + abs(y + height - dstY);
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
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi032::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, (gel ? height : 0), width, height, dstX, dstY);
}

int Ennemi032::getX()
{
    return x;
}

int Ennemi032::getY()
{
    return y;
}

BoundingBox *Ennemi032::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 7);
    return &box;
}
