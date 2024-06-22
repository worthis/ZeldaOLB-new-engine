#include "PiegeMain.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

PiegeMain::PiegeMain(int i, int j) : cooldown(0), step(0) {
    x = i;
    y = j;
    x0 = x;
    y0 = y;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/piegeMain.png", true);

    // for quadtree operations:
    width = 24;
    height = 24;

    box.setX(-1);
    box.setY(-1);
    box.setW(-1);
    box.setH(-1);
}

PiegeMain::~PiegeMain() {
    ResourceManager::getInstance()->free(image);
}

void PiegeMain::loop() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();

    cooldown++;
    if (step == 0) {
        if (cooldown == 240) {
            AudioManager::getInstance()->playSound(TS_TOMBE);
            step = 1;
            cooldown = 0;
            x = link->getX() - 4;
            y = link->getY();
            checkPosition();
        }
    } else if (step == 1) {
        cooldown++;
        if (cooldown == 120) {
            step = 2;
            cooldown = 0;
            BoundingBox b(x, y, 24, 24);
            if (b.intersect(link->getBoundingBox()) && link->getStatus()->getVirtualLife() > 0) {
                AudioManager::getInstance()->playSound(TS_TELEPORT);
                if (scene->getMap()->getId() == 18) {
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, 169*16+8, 72 * 16, N, false, false, true);
                } else if (scene->getMap()->getId() == 20) {
                    if (scene->getMap()->getBounds()->getX() == 0) {
                        MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, 89*16+8, 87 * 16, N, false, false, true);
                    } else {
                        MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, 9*16+8, 82 * 16, N, false, false, true);
                    }
                } else if (scene->getMap()->getId() == 23) {
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, 109*16+8, 72 * 16, N, false, false, true);
                } else if (scene->getMap()->getId() == 26) {
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, 69*16+8, 102 * 16, N, false, false, true);
                }
                MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            }
        }
    } else if (step == 2) {
        if (cooldown == 120) {
            step = 0;
            cooldown = 0;
        }
    }
}

void PiegeMain::draw(int offsetX, int offsetY) {
    if (step == 1) {
        WindowManager::getInstance()->draw(image, 0, 22, 24, 6, x - offsetX, y - offsetY + 18);
        WindowManager::getInstance()->draw(image, 0, 0, 24, 22, x - offsetX, y - offsetY - 240 + cooldown*2);
    } else if (step == 2) {
        WindowManager::getInstance()->draw(image, 0, 22, 24, 6, x - offsetX, y - offsetY + 18);
        WindowManager::getInstance()->draw(image, 28, 0, 20, 21, x - offsetX + 2, y - offsetY - cooldown*2);
    }
}

BoundingBox* PiegeMain::getBoundingBox() {
    return &box;
}

bool PiegeMain::isResetable() {
    return true;
}

void PiegeMain::reset() {
    x = x0;
    y = y0;
    checkPosition();
    cooldown = 0;
    step = 0;
}

int PiegeMain::getDown() {
    return y + 20;
}
