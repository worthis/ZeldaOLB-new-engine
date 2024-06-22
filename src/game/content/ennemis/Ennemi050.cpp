#include "Ennemi050.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi050::Ennemi050(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi50.png", true);
    chrono.reset();

    type = 50;

    x = i;
    y = j;

    // for quadtree operations:
    width = 52;
    height = 36;

    box.setX(x + 10);
    box.setY(y + 4);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 200;
    maxLife = 200;
    recul = 8;
    vitesseRecul = 4;
    maxGel = 128;

    isBoss = true;
    stunnable = false;

    forceEnn = 50;
    snipeMode = false;
}

Ennemi050::~Ennemi050()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi050::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    snipeMode = false;
    checkPosition();
}

bool Ennemi050::isResetable()
{
    return alive;
}

void Ennemi050::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    if (life > 1)
    {
        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);
        move(dir.first, dir.second);
    }
    else if (x != 149 * 16 - 10 || y != 109 * 16 - 4 + 8)
    {
        if (x < 149 * 16 - 10)
        {
            direction = E;
            move(1, 0);
        }
        else if (x > 149 * 16 - 10)
        {
            direction = W;
            move(-1, 0);
        }
        if (y > 109 * 16 - 4 + 8)
        {
            direction = N;
            move(0, -1);
        }
        else if (y < 109 * 16 - 4 + 8)
        {
            direction = S;
            move(0, 1);
        }
    }
    else if (!snipeMode)
    {
        direction = S;
        snipeMode = true;
        cooldown = 0;
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        if (snipeMode)
        {
            cooldown++;
            if (cooldown >= 8)
            {
                // retrieve target position ( = link ^^)
                Link *link = getLink();

                int dstX = link->getX() + 8;
                int dstY = link->getY() + 24;

                // throw proj and play sound
                double anglx = 0;
                double angly = 0;
                int origx = x + 26;
                int origy = y + 10;
                int destx = dstX;
                int desty = dstY - 8;

                double coef1 = 0;
                double coef2 = 0;

                if ((destx - origx) == 0)
                {
                    anglx = 0;
                    angly = 12;
                }
                else if ((desty - origy) == 0)
                {
                    anglx = 12;
                    angly = 0;
                }
                else
                {
                    coef1 = ((double)(desty - origy)) / ((double)(destx - origx));
                    coef2 = ((double)(destx - origx)) / ((double)(desty - origy));
                    anglx = (sqrt(12 / (1 + (coef1 * coef1))));
                    angly = (sqrt(12 / (1 + (coef2 * coef2))));
                }
                if (destx - origx < 0)
                    anglx = -anglx;
                if (desty - origy < 0)
                    angly = -angly;

                if (anglx > 4)
                    anglx = 4;
                if (angly > 4)
                    angly = 4;
                if (anglx < -4)
                    anglx = -4;
                if (angly < -4)
                    angly = -4;

                ProjectileHelper::getInstance()->addProjectile(TP_BOULE_MORT, origx, origy, anglx, angly);
                AudioManager::getInstance()->playSound(TS_THROW);
                cooldown = 0;
            }
        }
        chrono.reset();
    }
}

void Ennemi050::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (snipeMode)
    {
        WindowManager::getInstance()->draw(image, cooldown > 4 ? width : 0, 113, width, 42, dstX, dstY - 6);
    }
    else if (gel)
    {
        WindowManager::getInstance()->draw(image, direction == N ? 0 : width, 72, width, 41, dstX, dstY - 5);
    }
    else
    {
        WindowManager::getInstance()->draw(image, direction == N ? 0 : width, anim * height, width, height, dstX, dstY);
    }
}

int Ennemi050::getX()
{
    return x;
}

int Ennemi050::getY()
{
    return y;
}

BoundingBox *Ennemi050::getBoundingBox()
{
    box.setX(x + 10);
    box.setY(y + 4);
    return &box;
}

bool Ennemi050::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    Link *link = getLink();
    return (effect == TE_MORT) || (life > 1 && (type == TA_SWORD || type == TA_SWORD_HOLD) &&
                                   ((life > 100 && !link->getStatus()->isOniLink()) || (life <= 100 && link->getStatus()->isOniLink())));
}

void Ennemi050::beforeHit(TypeAttack typeAtt, TypeEffect effect)
{
    Link *link = getLink();
    if (typeAtt == TA_ARROW && link->getInventory()->hasObject(ARC_FEE) && life > 100)
    {
        gel = maxGel;
    }
}

void Ennemi050::afterHit()
{
    if (life <= 0)
    {
        life = 1;
        recul = 0;
        vitesseRecul = 0;
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getHud()->setBossLife(life, maxLife);
    }
}

void Ennemi050::giveItem(int x, int y)
{
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    map->addItem(ItemHelper::getInstance()->createItem(TI_TRIFORCE, x, y));
}
