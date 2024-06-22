#include "Ennemi052.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi052::Ennemi052(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi52.png", true);
    chrono.reset();

    type = 52;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 17;

    box.setX(x);
    box.setY(y + 1);
    box.setW(width);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 999;
    maxLife = 999;
    recul = 32;
    vitesseRecul = 4;

    forceEnn = 2;
}

Ennemi052::~Ennemi052()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi052::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi052::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    for (int i = 0; i < 4; i++)
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

void Ennemi052::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, (direction % 2) * 16, 34 + anim * 17, 16, 17, dstX, dstY);
}

int Ennemi052::getX()
{
    return x;
}

int Ennemi052::getY()
{
    return y;
}

BoundingBox *Ennemi052::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 1);
    return &box;
}

bool Ennemi052::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return false;
}
