#include "Ennemi071.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi071::Ennemi071(int i, int j) : anim(0), animMax(3), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi71.png", true);
    chrono.reset();

    type = 71;

    beforeMove = 0;
    moving = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 52;
    height = 55;

    box.setX(x+10);
    box.setY(y+23);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 30;
    maxLife = 30;
    recul = 8;
    vitesseRecul = 4;
    maxGel = 128;

    isBoss = true;
    stunnable = false;

    forceEnn = 12;
}

Ennemi071::~Ennemi071() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi071::reset() {
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

bool Ennemi071::isResetable() {
    return alive;
}

void Ennemi071::ennLoop() {

    if (moving) {

        // retrieve target position ( = link ^^)
        Link* link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    } else {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }
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
        chrono.reset();
    }
}

void Ennemi071::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width + (gel ? width * 4 : 0), anim * height, width, height, dstX, dstY);
}

int Ennemi071::getX() {
    return x;
}

int Ennemi071::getY() {
    return y;
}

BoundingBox* Ennemi071::getBoundingBox() {
    box.setX(x+10);
    box.setY(y+23);
    return &box;
}

void Ennemi071::giveItem(int i, int j) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 8));
}
