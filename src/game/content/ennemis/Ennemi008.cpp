#include "Ennemi008.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi008::Ennemi008(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi8.png", true);
    chrono.reset();

    type = 8;

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

    life = 4;
    maxLife = 4;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_RUBIS_BLEU, 40);
    items.addType(TI_RUBIS_ROUGE, 20);

    forceEnn = 2;
}

Ennemi008::~Ennemi008() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi008::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi008::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox())) {
            if (testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL)) {
                link->getStatus()->updateRupees(-5);
            }
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

void Ennemi008::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height + (gel ? height * 2 : 0), width, height, dstX, dstY);
}

int Ennemi008::getX() {
    return x;
}

int Ennemi008::getY() {
    return y;
}

BoundingBox* Ennemi008::getBoundingBox() {
    box.setX(x);
    box.setY(y+8);
    return &box;
}

void Ennemi008::giveItem(int x, int y) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    BoundingBox* bounds = map->getBounds();
    if (map->getId() == 16 && bounds->getX() == 320 * 6 && bounds->getY() == 240 && !scene->getCoffre(2, 4)) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(x, y));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, x, y, 4, true));
    } else if (map->getId() == 16 && bounds->getX() == 320 * 14 && bounds->getY() == 240*4 && !scene->getCoffre(2, 8)) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(x, y));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, x, y, 8, true));
    } else {
        Ennemi::giveItem(x, y);
    }
}
