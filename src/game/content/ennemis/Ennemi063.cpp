#include "Ennemi063.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi063::Ennemi063(int i, int j) : anim(0), animMax(0), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi63.png", true);
    chrono.reset();

    type = 63;

    beforeMove = 0;
    moving = 0;
    step = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 58;
    height = 68;

    box.setX(x+13);
    box.setY(y+36);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 30;
    maxLife = 30;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 5;
}

Ennemi063::~Ennemi063() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi063::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    beforeMove = 0;
    moving = 0;
    checkPosition();
}

bool Ennemi063::isResetable() {
    return alive;
}

void Ennemi063::ennLoop() {

    if (step == 0 && life <= 10) {
        step = 1;
        moving = 1;
        chrono.reset();
        animMax = 1;
        x -= 12;
        y += 8;
        width = 71;
        height = 60;
        checkPosition();
    }

    if (moving) {

        // retrieve target position ( = link ^^)
        Link* link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL)) {
            life += (step == 0 ? 1 : 2);
            if (life > maxLife) {
                life = maxLife;
            }
        }

    } else {
        if (testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL)) {
            life += (step == 0 ? 2 : 4);
            if (life > maxLife) {
                life = maxLife;
            }
        }
    }

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 1) {
                step = 2;
                y += 4;
                width = 82;
                height = 56;
                checkPosition();
            }
        }
        if (step == 0) {
            if (beforeMove > 0) {
                beforeMove--;
                if (beforeMove == 0) {
                    moving = 1;
                }
            } else if (moving < 12) {
                moving++;
                if (moving == 12) {
                    moving = 0;
                    beforeMove = 4;
                }
            }
        }
        chrono.reset();
    }
}

void Ennemi063::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step == 0) {
        WindowManager::getInstance()->draw(image, 0, 0, width, height, dstX, dstY);
    } else if (step == 1) {
        WindowManager::getInstance()->draw(image, 0, 68, width, height, dstX, dstY);
    } else if (step == 2) {
        WindowManager::getInstance()->draw(image, 0, 128 + 56 * anim, width, height, dstX, dstY);
    }
}

int Ennemi063::getX() {
    return x;
}

int Ennemi063::getY() {
    return y;
}

BoundingBox* Ennemi063::getBoundingBox() {
    if (step == 0) {
        box.setX(x+13);
        box.setY(y+36);
    } else if (step == 1) {
        box.setX(x+25);
        box.setY(y+28);
    } else if (step == 2) {
        box.setX(x+25);
        box.setY(y+24);
    }
    return &box;
}

void Ennemi063::giveItem(int i, int j) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 3));
}
