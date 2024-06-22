#include "Ennemi037.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi037::Ennemi037(int i, int j) : anim(0), animMax(1), vanim(180), cooldown(0), jump(false) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi37.png", true);
    chrono.reset();

    type = 37;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 26;

    box.setX(x);
    box.setY(y+10);
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

    items.addType(TI_FLECHE, 20);
    items.addType(TI_BOMBE, 20);
    items.addType(TI_RUBIS_ROUGE, 10);

    forceEnn = 5;
}

Ennemi037::~Ennemi037() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi037::reset() {
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

void Ennemi037::ennLoop() {

    if (cooldown) cooldown--;
    if (jump) jump = false;

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

void Ennemi037::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (jump) {
        WindowManager::getInstance()->draw(image, direction * width + (gel ? 64 : 0), 52, width, height, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, direction * width + (gel ? 64 : 0), anim * height, width, height, dstX, dstY);
    }

}

int Ennemi037::getX() {
    return x;
}

int Ennemi037::getY() {
    return y;
}

BoundingBox* Ennemi037::getBoundingBox() {
    box.setX(x);
    box.setY(y + 10);
    return &box;
}

bool Ennemi037::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    /*if ((type == TA_SWORD || type == TA_SWORD_HOLD) && cooldown == 0) {
        cooldown = 32;
        jump = true;
        AudioManager::getInstance()->playSound(TS_THROW);
        jumpBack(dir);
        return false;
    } else {*/
        return true;
    //}
}

void Ennemi037::giveItem(int i, int j) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    if (map->getId() == 20 && !scene->getCoffre(6, 8) && map->getBounds()->getX() < 320 * 7) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 8, true));
    } else if (map->getId() == 20 && !scene->getCoffre(6, 15) && map->getBounds()->getX() > 320 * 7 && !map->nbEnnemis()) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 15, true));
    } else {
        Ennemi::giveItem(i, j);
    }
}
