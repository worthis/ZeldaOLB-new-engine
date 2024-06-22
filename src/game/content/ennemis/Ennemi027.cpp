#include "Ennemi027.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi027::Ennemi027(int i, int j) : anim(0), animMax(9), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi27.png", true);
    chrono.reset();

    type = 27;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 17;

    box.setX(x);
    box.setY(y+1);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 3;
    maxLife = 3;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_FLECHE, 20);
    items.addType(TI_MAGIE_PEU, 20);
    items.addType(TI_BOMBE, 10);

    forceEnn = 2;
}

Ennemi027::~Ennemi027() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi027::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi027::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        if (anim < 8) {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);
            move(dir.first, dir.second);
        } else {
            idle = true;
        }
        if (link->getBoundingBox()->intersect(getBoundingBox())) {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }

        if (chrono.getElapsedTime() >= vanim) {
            if (!gel) anim++;
            if (anim > animMax) {
                anim = 0;
            }
            if (anim == animMax) {

                switch(direction) {
                    case N : ProjectileHelper::getInstance()->addProjectile(TP_BOULET, x+4, y - 8, N); break;
                    case S : ProjectileHelper::getInstance()->addProjectile(TP_BOULET, x+4, y + 12, S); break;
                    case W : ProjectileHelper::getInstance()->addProjectile(TP_BOULET, x - 4, y + 4, W); break;
                    case E : ProjectileHelper::getInstance()->addProjectile(TP_BOULET, x + 12, y + 4, E); break;
                }
                AudioManager::getInstance()->playSound(TS_THROW);
            }
            chrono.reset();
        }
    } else {
        idle = true;
    }
}

void Ennemi027::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (anim < 8) {
        WindowManager::getInstance()->draw(image, direction * width, (anim%2) * height, width, height, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, direction * width, (2 + (anim%2)) * height, width, height, dstX, dstY);
    }
}

int Ennemi027::getX() {
    return x;
}

int Ennemi027::getY() {
    return y;
}

BoundingBox* Ennemi027::getBoundingBox() {
    box.setX(x);
    box.setY(y + 1);
    return &box;
}
