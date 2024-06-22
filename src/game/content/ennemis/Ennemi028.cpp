#include "Ennemi028.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi028::Ennemi028(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi28.png", true);
    chrono.reset();

    type = 28;

    beforeMove = 0;
    moving = 0;
    step = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 38;

    box.setX(x);
    box.setY(y + 6);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 24;
    maxLife = 24;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi028::~Ennemi028()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi028::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    beforeMove = 0;
    moving = 0;
    step = 0;
    recul = 8;
    vitesseRecul = 4;
    forceEnn = 4;
    checkPosition();
}

bool Ennemi028::isResetable()
{
    return alive;
}

void Ennemi028::ennLoop()
{

    if (step == 0 && life <= 10)
    {
        step = 1;
        forceEnn = 7;
        recul = 0;
        vitesseRecul = 0;
    }

    if (step == 1 || moving)
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
        if (step == 0)
        {
            if (beforeMove > 0)
            {
                beforeMove--;
                if (beforeMove == 0)
                {
                    moving = 1;
                }
            }
            else if (moving < 8)
            {
                moving++;
                if (moving == 8)
                {
                    moving = 0;
                    beforeMove = 4;
                }
            }
        }
        chrono.reset();
    }
}

void Ennemi028::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, step * height, width, height, dstX, dstY);
}

int Ennemi028::getX()
{
    return x;
}

int Ennemi028::getY()
{
    return y;
}

BoundingBox *Ennemi028::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 6);
    return &box;
}

void Ennemi028::giveItem(int i, int j)
{
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 7));
}
