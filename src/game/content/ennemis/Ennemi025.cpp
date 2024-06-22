#include "Ennemi025.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi025::Ennemi025(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi25.png", true);
    chrono.reset();

    type = 25;

    x = i;
    y = j;

    // for quadtree operations:
    width = 28;
    height = 30;

    box.setX(x+6);
    box.setY(y+14);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 7;
    maxLife = 7;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_BOMBE, 20);
    items.addType(TI_RUBIS_ROUGE, 20);
    items.addType(TI_PETIT_COEUR, 10);

    forceEnn = 4;
}

Ennemi025::~Ennemi025() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi025::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi025::ennLoop() {

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

void Ennemi025::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height + (gel ? height * 2 : 0), width, height, dstX, dstY);
}

int Ennemi025::getX() {
    return x;
}

int Ennemi025::getY() {
    return y;
}

BoundingBox* Ennemi025::getBoundingBox() {
    box.setX(x + 6);
    box.setY(y + 14);
    return &box;
}

void Ennemi025::giveItem(int i, int j) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    if (map->getId() == 20 && !scene->getCoffre(6, 7) && map->getBounds()->getX() < 320 * 7) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 7, true));
    } else if (map->getId() == 20 && !scene->getCoffre(6, 14) && map->getBounds()->getX() > 320 * 7 && !map->nbEnnemis()) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 14, true));
    } else {
        Ennemi::giveItem(i, j);
    }
}
