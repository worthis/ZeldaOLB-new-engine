#include "Ennemi072.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi072::Ennemi072(int i, int j) : anim(0), animMax(1), vanim(180), cooldown(0), jump(false)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi72.png", true);
    chrono.reset();

    type = 72;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 26;

    box.setX(x);
    box.setY(y + 10);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    forceEnn = 12;
}

Ennemi072::~Ennemi072()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi072::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    cooldown = 0;
    jump = false;
    checkPosition();
}

bool Ennemi072::isResetable()
{
    return MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCoffre(11, 23) < 5;
}

void Ennemi072::ennLoop()
{

    if (cooldown)
        cooldown--;
    if (jump)
        jump = false;

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

void Ennemi072::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (jump)
    {
        WindowManager::getInstance()->draw(image, direction * width + (gel ? 64 : 0), 52, width, height, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, direction * width + (gel ? 64 : 0), anim * height, width, height, dstX, dstY);
    }
}

int Ennemi072::getX()
{
    return x;
}

int Ennemi072::getY()
{
    return y;
}

BoundingBox *Ennemi072::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 10);
    return &box;
}

bool Ennemi072::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    /*if ((type == TA_SWORD || type == TA_SWORD_HOLD) && cooldown == 0) {
        cooldown = 32;
        jump = true;
        AudioManager::getInstance()->playSound(TS_THROW);
        jumpBack(dir);
        return false;
    } else {*/
    return false;
    //}
}

void Ennemi072::pousseX(int dx)
{
    Direction old = direction;
    move(dx, 0);
    if (getLink()->getBoundingBox()->intersect(getBoundingBox()))
    {
        testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }
    direction = old;
}

void Ennemi072::pousseY(int dy)
{
    Direction old = direction;
    move(0, dy);
    if (getLink()->getBoundingBox()->intersect(getBoundingBox()))
    {
        testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }
    direction = old;
}

void Ennemi072::afterFall()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (scene->getCoffre(11, 23))
    {
    case 0:
        startX = 136 * 16;
        startY = 36 * 16 + 6;
        scene->setCoffre(11, 23, 1);
        break;
    case 1:
        startX = 39 * 16;
        startY = 104 * 16 + 6;
        scene->setCoffre(11, 23, 2);
        break;
    case 2:
        startX = 103 * 16;
        startY = 115 * 16 + 6;
        scene->setCoffre(11, 23, 3);
        break;
    case 3:
        startX = 194 * 16;
        startY = 111 * 16 + 6;
        scene->setCoffre(11, 23, 4);
        break;
    }
}
