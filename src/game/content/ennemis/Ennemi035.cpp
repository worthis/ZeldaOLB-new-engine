#include "Ennemi035.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi035::Ennemi035(int i, int j) : anim(0), animMax(3), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi35.png", true);
    chrono.reset();

    type = 35;

    beforeMove = 0;
    moving = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x + 8);
    box.setY(y + 16);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 20;
    maxLife = 20;
    recul = 8;
    vitesseRecul = 4;

    stunnable = false;

    forceEnn = 4;
}

Ennemi035::~Ennemi035()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi035::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    beforeMove = 0;
    moving = 0;
    checkPosition();
}

bool Ennemi035::isResetable()
{
    return alive;
}

void Ennemi035::ennLoop()
{

    if (moving)
    {

        // retrieve target position ( = link ^^)
        Link *link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }
    else
    {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        if (beforeMove > 0)
        {
            beforeMove--;
            if (beforeMove == 0)
            {
                moving = 1;
            }
        }
        else if (moving < 12)
        {
            moving++;
            if (moving == 12)
            {
                moving = 0;
                beforeMove = 4;
            }
        }
        chrono.reset();
    }
}

void Ennemi035::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int anim2 = anim;
    if (anim2 > 2)
        anim2 = 1;

    WindowManager::getInstance()->draw(image, anim2 * width, 0, width, height, dstX, dstY);
}

int Ennemi035::getX()
{
    return x;
}

int Ennemi035::getY()
{
    return y;
}

BoundingBox *Ennemi035::getBoundingBox()
{
    box.setX(x + 8);
    box.setY(y + 16);
    return &box;
}
