#include "Ennemi045.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../effects/Debris.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi045::Ennemi045(int i, int j) : anim(0), animMax(3), vanim(180), mask(0), cooldown(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi45.png", true);
    chrono.reset();

    type = 45;

    x = i;
    y = j;

    // for quadtree operations:
    width = 66;
    height = 76;

    box.setX(x + 1);
    box.setY(y + 12);
    box.setW(64);
    box.setH(64);

    box2.setX(x + 16);
    box2.setY(y + 39);
    box2.setW(34);
    box2.setH(38 + 10);

    // bounding box where the boss is allowed to be
    limit.setX(66 * 16);
    limit.setY(21 * 16);
    limit.setW(28 * 16);
    limit.setH(18 * 16);

    life = 20;
    maxLife = 20;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 6;
}

Ennemi045::~Ennemi045()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi045::reset()
{
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
    mask = 0;
}

bool Ennemi045::isResetable()
{
    return alive;
}

void Ennemi045::ennLoop()
{

    // move
    if (cooldown < 16)
    {
        int randomValue = (int)((float)rand() / RAND_MAX * (100));
        switch (randomValue)
        {
        case 1:
            if (x > limit.getX())
            {
                moveX(-1);
                direction = W;
            }
            break;
        case 2:
            if (x + width < limit.getX() + limit.getW())
            {
                moveX(1);
                direction = E;
            }
            break;
        case 3:
            if (y > limit.getY())
            {
                moveY(-1);
                direction = N;
            }
            break;
        case 4:
            if (y + height < limit.getY() + limit.getH())
            {
                moveY(1);
                direction = S;
            }
            break;
        default:
            if (randomValue < 10)
                break;
            switch (direction)
            {
            case N:
                if (y > limit.getY())
                    moveY(-1);
                break;
            case S:
                if (y + height < limit.getY() + limit.getH())
                    moveY(1);
                break;
            case W:
                if (x > limit.getX())
                    moveX(-1);
                break;
            case E:
                if (x + width < limit.getX() + limit.getW())
                    moveX(1);
                break;
            }
            break;
        }
    }

    testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        cooldown++;
        if (cooldown == 20)
        {
            snipe();
            cooldown = 0;
        }
        chrono.reset();
    }
}

void Ennemi045::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);

    if (cooldown >= 16)
    {
        WindowManager::getInstance()->draw(image, 144, 76, 16, 10, dstX + 25, dstY + 65);
    }

    if (mask < 3)
    {
        WindowManager::getInstance()->draw(image, mask * 48, 76, 48, 38, dstX + 9, dstY + 29);
    }
}

void Ennemi045::moveX(int dx)
{

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + dx);

    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->checkCollisions(bb, this, true, false, true, false))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Ennemi045::moveY(int dy)
{

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + dy);

    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi045::getX()
{
    return x;
}

int Ennemi045::getY()
{
    return y;
}

BoundingBox *Ennemi045::getBoundingBox()
{
    box.setX(x + 1);
    box.setY(y + 12);
    return &box;
}

BoundingBox *Ennemi045::getBoundingBoxForDamage()
{
    box2.setX(x + 16);
    box2.setY(y + 39);
    return &box2;
}

bool Ennemi045::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    if (mask < 3)
    {
        if (type == TA_MARTEAU)
        {
            mask++;
            AudioManager::getInstance()->playSound(TS_BREAK);
            Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            switch (mask)
            {
            case 1:
                map->addEffect(new Debris(x + 9 + 8, y + 29 + 22, direction, 0, false, false, true));
                break;
            case 2:
                map->addEffect(new Debris(x + 9 + 40, y + 29 + 22, direction, 0, false, false, true));
                break;
            case 3:
                map->addEffect(new Debris(x + 9 + 24, y + 29 + 16, direction, 0, false, false, true));
                break;
            }
        }
        return false;
    }
    return true;
}

void Ennemi045::snipe()
{

    // throw proj and play sound
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    double anglx = 0;
    double angly = 0;
    int origx = x + 33;
    int origy = y + 70 - 4;
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

    ProjectileHelper::getInstance()->addProjectile(TP_BIG_FEU, origx, origy, anglx, angly);
    AudioManager::getInstance()->playSound(TS_THROW);
}

void Ennemi045::giveItem(int i, int j)
{
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 4));
}
