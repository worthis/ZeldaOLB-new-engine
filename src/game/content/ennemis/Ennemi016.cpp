#include "Ennemi016.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi016::Ennemi016(int i, int j) : cooldown(96)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi16.png", true);

    type = 16;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 24;

    box.setX(x);
    box.setY(y + 8);
    box.setW(16);
    box.setH(16);

    startDir = direction;

    life = 6;
    maxLife = 6;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    items.addType(TI_PETIT_COEUR, 20);
    items.addType(TI_FLECHE, 20);
    items.addType(TI_RUBIS_ROUGE, 10);

    forceEnn = 5;
}

Ennemi016::~Ennemi016()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi016::reset()
{
    Ennemi::reset();
    direction = startDir;
    cooldown = 96;
    checkPosition();
}

void Ennemi016::ennLoop()
{

    if (cooldown)
        cooldown--;

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist)
    {

        int srcX = x + 8;
        int srcY = y + 24;

        if (cooldown <= 96)
        {
            if (abs(dstX - srcX) > abs(dstY - srcY))
            {
                direction = (dstX > srcX) ? E : W;
            }
            else
            {
                direction = (dstY > srcY) ? S : N;
            }
        }

        if (cooldown == 96 || cooldown == 64 || cooldown == 32 || cooldown == 0)
        {
            if (cooldown > 0)
            {
                switch (direction)
                {
                case N:
                    ProjectileHelper::getInstance()->addProjectile(TP_ARC_MAGIQUE, x, y, N);
                    break;
                case S:
                    ProjectileHelper::getInstance()->addProjectile(TP_ARC_MAGIQUE, x, y + 16, S);
                    break;
                case W:
                    ProjectileHelper::getInstance()->addProjectile(TP_ARC_MAGIQUE, x - 8, y + 8, W);
                    break;
                case E:
                    ProjectileHelper::getInstance()->addProjectile(TP_ARC_MAGIQUE, x + 16, y + 8, E);
                    break;
                }
                AudioManager::getInstance()->playSound(TS_MAGIC);
            }
            if (!cooldown)
                cooldown = 160;
        }
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }
}

void Ennemi016::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, (cooldown <= 96) ? 0 : 24, width, height, dstX, dstY);
}

int Ennemi016::getX()
{
    return x;
}

int Ennemi016::getY()
{
    return y;
}

BoundingBox *Ennemi016::getBoundingBox()
{
    return &box;
}

bool Ennemi016::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return type == TA_MAGIC && effect == TE_NORMAL;
}
