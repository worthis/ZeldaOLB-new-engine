#include "Ennemi022.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi022::Ennemi022(int i, int j) : anim(0), animMax(15), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi22.png", true);
    chrono.reset();

    type = 22;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 23;

    box.setX(x);
    box.setY(y+7);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 2;
    maxLife = 2;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_PETIT_COEUR, 10);
    items.addType(TI_RUBIS_BLEU, 20);
    items.addType(TI_FLECHE, 20);

    forceEnn = 2;
}

Ennemi022::~Ennemi022() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi022::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi022::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + 8 - dstX) + abs(y + 23 - dstY);
    if (dist <= maxDist) {

        if (anim < 6) {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

            move(dir.first, dir.second);

            if (link->getBoundingBox()->intersect(getBoundingBox())) {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
            }
        } else {
            idle = true;
            testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_ELECTRIC);
        }
    } else {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi022::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (anim < 6) {
        WindowManager::getInstance()->draw(image, (anim%2) * width, (gel ? 23 : 0), width, height, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, (1+((1+anim)%2)) * width, (gel ? 23 : 0), width, height, dstX, dstY);
    }
}

int Ennemi022::getX() {
    return x;
}

int Ennemi022::getY() {
    return y;
}

BoundingBox* Ennemi022::getBoundingBox() {
    box.setX(x);
    box.setY(y+7);
    return &box;
}

bool Ennemi022::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    if (anim < 6) return true;
    if (type == TA_SWORD || type == TA_SWORD_HOLD) {
        testDegatOnLink(getLink()->getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_ELECTRIC);
        return false;
    }
    return true;
}

bool Ennemi022::isToAvoid(Collision c) {
    return false;
}
