#include "PiegeMurs.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../effects/Splash.h"

#include "../../MainController.h"

PiegeMurs::PiegeMurs(int i, int j, Map* map, Direction dir) : anim(25), animMax(152), vanim(120), direction(dir) {
    x = i;
    y = j;
    x0 = x;
    image = ResourceManager::getInstance()->loadImage("data/images/objects/piegeMurs.png");

    // for quadtree operations:
    width = 25;
    height = 144;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    if (direction == E) {
        other = new PiegeMurs(x + 320 - width, y, map, W);
        map->addObject(other);
    }

    chrono.reset();
}

PiegeMurs::~PiegeMurs() {
    ResourceManager::getInstance()->free(image);
}

Direction PiegeMurs::getDirection() {
    return direction;
}

void PiegeMurs::loop() {
    if (chrono.getElapsedTime() >= vanim) {
        if (anim < animMax) {
            anim++;
            width++;
            if (direction == W) {
                x--;
            }
            computeMaxSize();
            checkPosition();
        } else if (width == 152) {
            width = 160;
            if (direction == W) {
                x-=8;
            }
            computeMaxSize();
            checkPosition();
        }
        chrono.reset();
    }

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    BoundingBox* bb = getBoundingBox();
    if (link->getStatus()->getVirtualLife() > 0 && link->getAnimation() != CHUTE && link->getBoundingBox()->intersect(bb)) {
        if (width < 160) {
            int tmp = 0;
            while (link->getBoundingBox()->intersect(bb) && tmp < 4) {
                if (direction == E) {
                    link->pousseX(1);
                } else if (direction == W) {
                    link->pousseX(-1);
                }
                tmp++;
            }
        } else {
            link->setAnimation(NOYE);
            link->getStatus()->setLife(0);
            AudioManager::getInstance()->playSound(TS_SPLASH);
            AudioManager::getInstance()->playMusic(3);
            scene->getMap()->addEffect(new Splash(link->getX() - 8, link->getY()));
        }
    }
}

void PiegeMurs::draw(int offsetX, int offsetY) {
    if (direction == E) {
        WindowManager::getInstance()->draw(image, 169 - width, 0, width, height, x - offsetX, y - offsetY);
    } else if (direction == W) {
        WindowManager::getInstance()->draw(image, 169, 0, width, height, x - offsetX, y - offsetY);
    }
}

BoundingBox* PiegeMurs::getBoundingBox() {
    if (direction == E) {
        box.setX(x);
    } else {
        box.setX(x+1);
    }
    box.setW(width-1);
    return &box;
}

bool PiegeMurs::isResetable() {
    return true;
}

void PiegeMurs::reset() {
    x = x0;
    width = 25;
    computeMaxSize();
    checkPosition();
}

int PiegeMurs::getDown() {
    return y;
}
