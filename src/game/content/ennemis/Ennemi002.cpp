#include "Ennemi002.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi002::Ennemi002(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi2.png", true);
    chrono.reset();

    type = 2;

    x = i;
    y = j;

    // for quadtree operations:
    width = 21;
    height = 26;

    box.setX(x + 3);
    box.setY(y + 10);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 12;
    maxLife = 12;
    recul = 16;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_RUBIS_BLEU, 40);
    items.addType(TI_RUBIS_ROUGE, 20);
    items.addType(TI_MAGIE_PEU, 10);

    forceEnn = 8;
}

Ennemi002::~Ennemi002()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi002::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi002::ennLoop()
{

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

void Ennemi002::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height + (gel ? height * 2 : 0), width, height, dstX, dstY);
}

int Ennemi002::getX()
{
    return x;
}

int Ennemi002::getY()
{
    return y;
}

BoundingBox *Ennemi002::getBoundingBox()
{
    box.setX(x + 3);
    box.setY(y + 10);
    return &box;
}

void Ennemi002::giveItem(int i, int j)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map *map = scene->getMap();
    if (map->getId() == 20 && !scene->getCoffre(6, 10) && map->getBounds()->getX() < 320 * 7)
    {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 10, true));
    }
    else if (map->getId() == 20 && !scene->getCoffre(6, 16) && map->getBounds()->getX() > 320 * 7 && !map->nbEnnemis())
    {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 16, true));
    }
    else
    {
        Ennemi::giveItem(i, j);
    }
}
