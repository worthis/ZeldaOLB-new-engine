#include "Ennemi041.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi041::Ennemi041(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi41.png", true);
    chrono.reset();

    type = 41;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 24;

    box.setX(x);
    box.setY(y+8);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 9;
    maxLife = 9;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_RUBIS_BLEU, 40);
    items.addType(TI_MAGIE_PEU, 20);
    items.addType(TI_MAGIE_BEAUCOUP, 10);

    forceEnn = 6;
}

Ennemi041::~Ennemi041() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi041::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi041::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox())) {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }
    } else {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi041::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width + (gel ? width * 4 : 0), anim * height, width, height, dstX, dstY);
}

int Ennemi041::getX() {
    return x;
}

int Ennemi041::getY() {
    return y;
}

BoundingBox* Ennemi041::getBoundingBox() {
    box.setX(x);
    box.setY(y + 8);
    return &box;
}

void Ennemi041::giveItem(int i, int j) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    if (map->getId() == 20 && !scene->getCoffre(6, 11) && map->getBounds()->getX() < 320 * 7) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 11, true));
    } else if (map->getId() == 20 && !scene->getCoffre(6, 17) && map->getBounds()->getX() > 320 * 7 && !map->nbEnnemis()) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 17, true));
    } else {
        Ennemi::giveItem(i, j);
    }
}

