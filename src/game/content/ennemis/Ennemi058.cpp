#include "Ennemi058.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi058::Ennemi058(int i, int j) : anim(0), animMax(1), vanim(180), resetable(true)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi58.png", true);
    chrono.reset();

    type = 53; // ennemi 58 <=> ennemi 53

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 32;
    vitesseRecul = 4;

    items.addType(TI_MAGIE_PEU, 20);
    items.addType(TI_RUBIS_VERT, 30);
    items.addType(TI_MAGIE_BEAUCOUP, 10);

    forceEnn = 1;
    cooldown = 240;
}

Ennemi058::~Ennemi058()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi058::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    cooldown = 240;
    checkPosition();
}

void Ennemi058::setResetableToFalse()
{
    resetable = false;
}

bool Ennemi058::isResetable()
{
    return resetable;
}

bool Ennemi058::isHittable()
{
    return cooldown == 0;
}

void Ennemi058::ennLoop()
{
    if (cooldown > 0)
    {
        cooldown -= 8;
        return;
    }

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist)
    {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        if (dir.first < 0)
            direction = W;
        if (dir.first > 0)
            direction = E;

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

void Ennemi058::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (cooldown > 0)
    {
        WindowManager::getInstance()->draw(image, 29, 30, 12, 6, dstX + 2, dstY + 10); // shadow
        WindowManager::getInstance()->draw(image, 0, 0, 14, 15, dstX + 1, dstY + 1 - cooldown);
    }
    else
    {
        WindowManager::getInstance()->draw(image, (direction % 2) * 14, anim * 15, 14, 15, dstX + 1, dstY + 1);
    }
}

int Ennemi058::getX()
{
    return x;
}

int Ennemi058::getY()
{
    return y;
}

BoundingBox *Ennemi058::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}
