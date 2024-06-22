#include "Ennemi019.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi019::Ennemi019(int i, int j) : anim(0), animMax(3), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi19.png", true);
    chrono.reset();

    type = 19;

    beforeMove = 0;
    moving = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 64;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(64);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 8;
    maxLife = 8;
    recul = 8;
    vitesseRecul = 4;

    //isBoss = true;
    stunnable = false;

    forceEnn = 2;
}

Ennemi019::~Ennemi019() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi019::reset() {
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

bool Ennemi019::isResetable() {
    return alive;
}

void Ennemi019::ennLoop() {

    BoundingBox* tmpBox = new BoundingBox(box.getX(), box.getY(), box.getW(), box.getH());
    switch (anim) {
        case 0 : tmpBox->setX(x); tmpBox->setW(64); break;
        case 1 : case 3 : tmpBox->setX(x + 10); tmpBox->setW(44); break;
        default : tmpBox->setX(x + 21); tmpBox->setW(22); break;
    }

    if (moving) {

        // retrieve target position ( = link ^^)
        Link* link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox())) {
            testDegatOnLink(tmpBox, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }

    } else {
        testDegatOnLink(tmpBox, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }
    delete tmpBox;

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
        } else if (moving < 8) {
            moving++;
            if (moving == 8) {
                moving = 0;
                beforeMove = 4;
            }
        }
        chrono.reset();
    }
}

void Ennemi019::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int anim2 = anim;
    if (anim2 == 3) anim2 = 1;

    WindowManager::getInstance()->draw(image, anim2 * width, 0, width, height, dstX, dstY);
}

int Ennemi019::getX() {
    return x;
}

int Ennemi019::getY() {
    return y;
}

BoundingBox* Ennemi019::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

/*void Ennemi019::giveItem(int x, int y) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    map->addItem(ItemHelper::getInstance()->createItem(TI_CRISTAL, x, y, 0));
}*/
