#include "Ennemi075.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi075::Ennemi075(int i, int j) : anim(0), animMax(7), vanim(80)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi75.png", true);
    chrono.reset();

    type = 75;

    x = i;
    y = j;

    // for quadtree operations:
    width = 19;
    height = 24;

    box.setX(x + 1);
    box.setY(y + 8);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 100;
    maxLife = 100;
    recul = 32;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 24;

    animSword = 0;
    isKo = false;
    speed = 1;
}

Ennemi075::~Ennemi075()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi075::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animSword = 0;
    isKo = false;
    speed = 1;
    recul = 32;
    vitesseRecul = 4;
    checkPosition();
}

bool Ennemi075::isResetable()
{
    return alive;
}

void Ennemi075::ennLoop()
{

    if (animSword)
    {
        if (chrono.getElapsedTime() >= 40)
        {
            animSword++;
            chrono.reset();
        }
        if (animSword > 5)
        {
            animSword = 0;
            anim = 0;
            idle = true;
        }
        else
        {
            BoundingBox hitZone;
            switch (animSword)
            {
            case 1:
                if (direction == N)
                {
                    hitZone.setX(x + 14);
                    hitZone.setY(y + 6);
                    hitZone.setW(12);
                    hitZone.setH(8);
                }
                if (direction == S)
                {
                    hitZone.setX(x - 6);
                    hitZone.setY(y + 15);
                    hitZone.setW(12);
                    hitZone.setH(9);
                }
                if (direction == W)
                {
                    hitZone.setX(x - 1);
                    hitZone.setY(y - 1);
                    hitZone.setW(8);
                    hitZone.setH(14);
                }
                if (direction == E)
                {
                    hitZone.setX(x + 12);
                    hitZone.setY(y - 1);
                    hitZone.setW(8);
                    hitZone.setH(14);
                }
                break;
            case 2:
                if (direction == N)
                {
                    hitZone.setX(x + 4);
                    hitZone.setY(y - 13);
                    hitZone.setW(12);
                    hitZone.setH(16);
                }
                if (direction == S)
                {
                    hitZone.setX(x - 4);
                    hitZone.setY(y + 20);
                    hitZone.setW(14);
                    hitZone.setH(5);
                }
                if (direction == W)
                {
                    hitZone.setX(x - 11);
                    hitZone.setY(y + 1);
                    hitZone.setW(16);
                    hitZone.setH(13);
                }
                if (direction == E)
                {
                    hitZone.setX(x + 14);
                    hitZone.setY(y + 1);
                    hitZone.setW(16);
                    hitZone.setH(13);
                }
                break;
            case 3:
                if (direction == N)
                {
                    hitZone.setX(x + 1);
                    hitZone.setY(y - 20);
                    hitZone.setW(7);
                    hitZone.setH(20);
                }
                if (direction == S)
                {
                    hitZone.setX(x + 10);
                    hitZone.setY(y + 24);
                    hitZone.setW(7);
                    hitZone.setH(19);
                }
                if (direction == W)
                {
                    hitZone.setX(x - 19);
                    hitZone.setY(y + 12);
                    hitZone.setW(20);
                    hitZone.setH(7);
                }
                if (direction == E)
                {
                    hitZone.setX(x + 18);
                    hitZone.setY(y + 12);
                    hitZone.setW(20);
                    hitZone.setH(7);
                }
                break;
            case 4:
                if (direction == N)
                {
                    hitZone.setX(x - 14);
                    hitZone.setY(y - 6);
                    hitZone.setW(16);
                    hitZone.setH(15);
                }
                if (direction == S)
                {
                    hitZone.setX(x + 16);
                    hitZone.setY(y + 18);
                    hitZone.setW(10);
                    hitZone.setH(15);
                }
                if (direction == W)
                {
                    hitZone.setX(x - 11);
                    hitZone.setY(y + 16);
                    hitZone.setW(14);
                    hitZone.setH(14);
                }
                if (direction == E)
                {
                    hitZone.setX(x + 16);
                    hitZone.setY(y + 16);
                    hitZone.setW(14);
                    hitZone.setH(14);
                }
                break;
            case 5:
                if (direction == N)
                {
                    hitZone.setX(x - 13);
                    hitZone.setY(y + 2);
                    hitZone.setW(14);
                    hitZone.setH(13);
                }
                if (direction == S)
                {
                    hitZone.setX(x + 18);
                    hitZone.setY(y + 16);
                    hitZone.setW(13);
                    hitZone.setH(12);
                }
                if (direction == W)
                {
                    hitZone.setX(x - 4);
                    hitZone.setY(y + 21);
                    hitZone.setW(14);
                    hitZone.setH(14);
                }
                if (direction == E)
                {
                    hitZone.setX(x + 9);
                    hitZone.setY(y + 21);
                    hitZone.setW(14);
                    hitZone.setH(14);
                }
                break;
            }
            if (hitZone.intersect(getLink()->getBoundingBox()))
            {
                testDegatOnLink(&hitZone, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
            }
        }
    }
    else if (isKo)
    {
        if (chrono.getElapsedTime() >= 40)
        {
            life += 4;
            if (life >= maxLife)
            {
                life = maxLife;
                isKo = false;
                anim = 0;
                animSword = 0;
                idle = true;
                speed = 1;
                recul = 32;
                vitesseRecul = 4;
            }
            chrono.reset();
        }
    }
    else
    {

        // retrieve target position ( = link ^^)
        Link *link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
        if (dist <= maxDist)
        {
            for (int s = 0; s < speed; s++)
            {
                pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

                move(dir.first, dir.second);

                if (link->getBoundingBox()->intersect(getBoundingBox()))
                {
                    testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
                }
            }
        }
        else
        {
            idle = true;
        }

        BoundingBox hitZone(box.getX(), box.getY(), box.getW(), box.getH());
        switch (direction)
        {
        case N:
            hitZone.setY(box.getY() - 16);
            break;
        case S:
            hitZone.setY(box.getY() + 16);
            break;
        case W:
            hitZone.setX(box.getX() - 16);
            break;
        case E:
            hitZone.setX(box.getX() + 16);
            break;
        }
        if (hitZone.intersect(link->getBoundingBox()))
        {
            animSword = 1;
            chrono.reset();
        }
        else if (chrono.getElapsedTime() >= vanim)
        {
            anim++;
            if (anim > animMax)
            {
                anim = 0;
            }
            chrono.reset();
        }
    }
}

void Ennemi075::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (isKo)
    {
        WindowManager::getInstance()->draw(image, 0, 216, 24, 15, dstX - 5, dstY + 9);
    }
    else if (animSword)
    {
        switch (direction)
        {
        case N:
            WindowManager::getInstance()->draw(image, 113, 44 * (animSword - 1), 40, 44, dstX - 14, dstY - 20);
            break;
        case S:
            WindowManager::getInstance()->draw(image, 76, 43 * (animSword - 1), 37, 43, dstX - 6, dstY);
            break;
        case W:
            WindowManager::getInstance()->draw(image, 153, 36 * (animSword - 1), 39, 36, dstX - 18, dstY - 1);
            break;
        case E:
            WindowManager::getInstance()->draw(image, 192, 36 * (animSword - 1), 39, 36, dstX - 1, dstY - 1);
            break;
        }
    }
    else if (idle)
    {
        WindowManager::getInstance()->draw(image, direction * width, 0, width, height, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, direction * width, (anim + 1) * height, width, height, dstX, dstY);
    }
}

int Ennemi075::getX()
{
    return x;
}

int Ennemi075::getY()
{
    return y;
}

BoundingBox *Ennemi075::getBoundingBox()
{
    box.setX(x + 1);
    box.setY(y + 8);
    return &box;
}

bool Ennemi075::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return !isKo && (type == TA_SWORD || type == TA_SWORD_HOLD);
}

void Ennemi075::afterHit()
{
    if (life <= 0)
    {
        life = 1;
        isKo = true;
        recul = 0;
        vitesseRecul = 0;
        animSword = 0;
        anim = 0;
    }
    if (speed == 1 && life <= 75)
    {
        speed = 2;
    }
}

void Ennemi075::giveItem(int i, int j)
{
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 11));
}

void Ennemi075::catchToMask()
{
    if (isKo)
    {
        alive = false;
        life = 0;
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        scene->getHud()->setBossLife(0, maxLife);
        giveItem(x + 9, y + 16);
        getLink()->trouveObjet(TI_MASQUE);
        scene->getMap()->testAnimRoom();
    }
}
