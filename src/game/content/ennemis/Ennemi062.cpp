#include "Ennemi062.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi062::Ennemi062(int i, int j, bool boss) : anim(0), animMax(1), vanim(180), step(0), beforeRegen(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi62.png", true);
    chrono.reset();

    type = 62;

    x = i;
    y = j;

    // for quadtree operations:
    width = 24;
    height = 37;

    box.setX(x+4);
    box.setY(y+21);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 10;
    maxLife = 10;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_FLECHE, 20);
    items.addType(TI_BOMBE, 20);
    items.addType(TI_RUBIS_ROUGE, 10);

    forceEnn = 2;

    isBoss = boss;
    stunnable = true;
}

Ennemi062::~Ennemi062() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi062::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    step = 0;
    recul = 32;
    stunnable = true;
    beforeRegen = 0;
    checkPosition();
}

bool Ennemi062::isResetable() {
    return !isBoss || alive;
}

void Ennemi062::ennLoop() {

    if (step == 0) {

        if (life <= 5) {
            step = 1;
            beforeRegen = 16;
            recul = 0;
            stunnable = false;
        } else {

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
            beforeRegen++;
            if (beforeRegen == 64) {
                if (life < maxLife) {
                    life++;
                }
                beforeRegen = 0;
            }
        }

    } else if (step == 1) {
        beforeRegen--;
        if (beforeRegen == 0) {
            step = 2;
            beforeRegen = 300;
        }
    } else if (step == 2) {
        beforeRegen--;
        if (beforeRegen == 0) {
            step = 3;
            beforeRegen = 16;
        }
    } else if (step == 3) {
        beforeRegen--;
        if (beforeRegen == 0) {
            step = 0;
            recul = 32;
            stunnable = true;
            beforeRegen = 0;
            anim = 0;
            chrono.reset();
            life = maxLife;
        }
    }

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }


}

void Ennemi062::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    switch (step) {
        case 0 :
            WindowManager::getInstance()->draw(image, direction * width + (gel ? width * 4 : 0), anim * height, width, height, dstX, dstY);
            break;
        case 1 :
            WindowManager::getInstance()->draw(image, 14, 74, 24, 17, dstX, dstY + 20);
            WindowManager::getInstance()->draw(image, 0, 74, 14, 16, dstX + 5, dstY + 16 - beforeRegen);
            break;
        case 2 :
            WindowManager::getInstance()->draw(image, 14, 74, 24, 17, dstX, dstY + 20);
            WindowManager::getInstance()->draw(image, 0, 74, 14, 16, dstX + 5, dstY + 16);
            break;
        case 3 :
            WindowManager::getInstance()->draw(image, 14, 74, 24, 17, dstX, dstY + 20);
            WindowManager::getInstance()->draw(image, 0, 74, 14, 16, dstX + 5, dstY + beforeRegen);
            break;
    }


}

int Ennemi062::getX() {
    return x;
}

int Ennemi062::getY() {
    return y;
}

BoundingBox* Ennemi062::getBoundingBox() {
    box.setX(x + 4);
    box.setY(y + 21);
    return &box;
}

bool Ennemi062::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return step == 0 || type == TA_EXPLO;
}

void Ennemi062::giveItem(int i, int j) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    if (isBoss) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 2));
    } else if (map->getId() == 23 && map->getBounds()->getX() == 320 * 7 && map->getBounds()->getY() == 0 && !scene->getCoffre(9, 5)) {
        AudioManager::getInstance()->playSound(TS_KILLENNEMY);
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_CLE, i, j, 5, true));
    } else {
        Ennemi::giveItem(i, j);
    }
}
