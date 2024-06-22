#include "Barriere.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Barriere::Barriere(int i, int j, Map *map) : anim(0), animMax(1), vanim(120)
{
    x = i;
    y = j;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/barriere.png", true);

    // for quadtree operations:
    width = 80;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    force = 1;

    attackable = true;

    map->setAir(x, y, 1221);
    map->setAir(x + width, y, 1222);

    chrono.reset();
}

Barriere::~Barriere()
{
    ResourceManager::getInstance()->free(image);
}

void Barriere::loop()
{
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;

        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        if (anim > animMax)
        {
            anim = 0;
            map->setAir(x, y, 1221);
            map->setAir(x + width, y, 1222);
        }
        else
        {
            map->setAir(x, y, 1223);
            map->setAir(x + width, y, 1224);
        }

        chrono.reset();
    }
}

void Barriere::draw(int offsetX, int offsetY)
{
    WindowManager::getInstance()->draw(image, 0, height * anim, width, height, x - offsetX, y - offsetY);
}

BoundingBox *Barriere::getBoundingBox()
{
    return &box;
}

void Barriere::underAttack(Direction dir, int f, TypeAttack type, TypeEffect effect)
{
    if (type == TA_SWORD || type == TA_SWORD_HOLD)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();
        if (link->getEpee() < 2)
        {
            scene->testDegatOnLink(link->getBoundingBox(), S, force, TA_PHYSIC, TE_ELECTRIC);
        }
        else
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            scene->setCoffre(0, 0, 1);
            Map *map = scene->getMap();
            map->setAir(x, y, 1217);
            map->setAir(x + width, y, 1218);
            map->addEffect(new FumeeBlanche(x + 40, y + 8));
            alive = false;
        }
    }
}
