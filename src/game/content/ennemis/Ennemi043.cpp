#include "Ennemi043.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi043::Ennemi043(int i, int j) : anim(0), animMax(2), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi43.png", true);
    chrono.reset();

    type = 43;

    beforeMove = 0;
    moving = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 30;
    maxLife = 30;
    recul = 8;
    vitesseRecul = 4;
    maxGel = 128;

    isBoss = true;
    stunnable = false;

    forceEnn = 10;
}

Ennemi043::~Ennemi043()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi043::reset()
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

bool Ennemi043::isResetable()
{
    return alive;
}

void Ennemi043::ennLoop()
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

void Ennemi043::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height, width, height, dstX, dstY);
}

int Ennemi043::getX()
{
    return x;
}

int Ennemi043::getY()
{
    return y;
}

BoundingBox *Ennemi043::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}

bool Ennemi043::isCollision(Collision c)
{
    return true;
}

bool Ennemi043::isToAvoid(Collision c)
{
    return false;
}

void Ennemi043::giveItem(int x, int y)
{
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, x, y, 9));
}
