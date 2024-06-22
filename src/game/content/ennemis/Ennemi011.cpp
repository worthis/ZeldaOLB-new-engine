#include "Ennemi011.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "cstdlib"

Ennemi011::Ennemi011(int i, int j, bool act) : anim(act ? 3 : 0), animMax(3), vanim(180), actif(act) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi11.png", true);
    chrono.reset();

    type = 11;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 21;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 32;
    vitesseRecul = 4;
    maxDist = 48;
    maxGel = 128;

    items.addType(TI_BOMBE, 30);
    items.addType(TI_RUBIS_BLEU, 20);
    items.addType(TI_PETIT_COEUR, 10);

    forceEnn = 8;
}

Ennemi011::~Ennemi011() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi011::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    anim = 0;
    actif = false;
    maxDist = 48;
    checkPosition();
}

void Ennemi011::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + 8 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        if (!actif) {
            actif = true;
            maxDist = 200;
            anim = 0;
            chrono.reset();
        } else {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

            move(dir.first, dir.second);

            if (link->getBoundingBox()->intersect(getBoundingBox())) {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
            }
        }
    } else {
        idle = true;
    }

    if (actif && chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi011::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (actif) {
        WindowManager::getInstance()->draw(image, 16 * anim, 0, 16, 21, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, 64, 0, 16, 16, dstX, dstY);
    }
}

int Ennemi011::getX() {
    return x;
}

int Ennemi011::getY() {
    return y;
}

BoundingBox* Ennemi011::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

bool Ennemi011::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return actif && type == TA_MARTEAU;
}
