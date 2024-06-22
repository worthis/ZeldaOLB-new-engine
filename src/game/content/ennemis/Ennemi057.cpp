#include "Ennemi057.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi057::Ennemi057(int i, int j, Map* map) : anim(0), animMax(2), vanim(240), cooldown(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi57.png", true);
    imageBis = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi59.png", true);
    chrono.reset();

    type = 57;

    x = i;
    y = j;

    // for quadtree operations:
    width = 48;
    height = 65;

    box.setX(x + 8);
    box.setY(y + 33);
    box.setW(32);
    box.setH(32);

    life = 8;
    maxLife = 8;
    recul = 0;
    vitesseRecul = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 2;

    if (map != 0) {
        map->setSol(89*16, 24*16, 2, 1, 1615, MURRET);
        encyclopedie = false;
    } else {
        encyclopedie = true;
    }
    for (i = 0; i < 3; i++) ennemis[i] = 0;
}

Ennemi057::~Ennemi057() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(imageBis);
}

void Ennemi057::reset() {
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
}

bool Ennemi057::isResetable() {
    return alive;
}

void Ennemi057::addEnnemi(int i) {
    int dstX = getLink()->getX();
    int dstY = getLink()->getY() + 8;

    if (!tryToAddEnnemi(dstX, dstY, i) && !tryToAddEnnemi(dstX-8, dstY, i) && !tryToAddEnnemi(dstX+8, dstY, i)
        && !tryToAddEnnemi(dstX, dstY-8, i) && !tryToAddEnnemi(dstX-8, dstY-8, i) && !tryToAddEnnemi(dstX+8, dstY-8, i)
        && !tryToAddEnnemi(dstX, dstY+8, i) && !tryToAddEnnemi(dstX-8, dstY+8, i) && !tryToAddEnnemi(dstX+8, dstY+8, i)
        && !tryToAddEnnemi(dstX-16, dstY, i) && !tryToAddEnnemi(dstX+16, dstY, i)
        && !tryToAddEnnemi(dstX, dstY-16, i) && !tryToAddEnnemi(dstX-16, dstY-16, i) && !tryToAddEnnemi(dstX+16, dstY-16, i)
        && !tryToAddEnnemi(dstX, dstY+16, i) && !tryToAddEnnemi(dstX-16, dstY+16, i) && !tryToAddEnnemi(dstX+16, dstY+16, i)
        && !tryToAddEnnemi(dstX-32, dstY, i) && !tryToAddEnnemi(dstX+32, dstY, i)
        && !tryToAddEnnemi(dstX, dstY-32, i) && !tryToAddEnnemi(dstX-32, dstY-32, i) && !tryToAddEnnemi(dstX+32, dstY-32, i)
        && !tryToAddEnnemi(dstX, dstY+32, i) && !tryToAddEnnemi(dstX-32, dstY+32, i) && !tryToAddEnnemi(dstX+32, dstY+32, i)) {
        anim = 0;
        cooldown = 8;
    }
}

bool Ennemi057::tryToAddEnnemi(int a, int b, int i) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    BoundingBox bb(a, b, 16, 16);
    if (scene->checkCollisions(&bb, this, true)) {
        ennemis[i] = new Ennemi058(a, b);
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEnnemi(ennemis[i]);
        AudioManager::getInstance()->playSound(TS_THROW);
        return true;
    }
    return false;
}

void Ennemi057::ennLoop() {
    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        if (cooldown == 16) {
            anim++;
            if (anim == animMax) {
                for (int i = 0; i < 3; i++) {
                    if (ennemis[i] != 0 && !ennemis[i]->isAlive()) {
                        ennemis[i]->setResetableToFalse();
                        ennemis[i] = 0;
                    }
                    if (ennemis[i] == 0) {
                        addEnnemi(i);
                        break;
                    }
                }
            } else if (anim > animMax) {
                anim = 0;
                cooldown = 0;
            }
        } else if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->nbEnnemis() < 4) {
            cooldown++;
        }
        chrono.reset();
    }
}

void Ennemi057::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (encyclopedie) {
        WindowManager::getInstance()->draw(image, width, 0, width, height, dstX, dstY);
    } else {

        WindowManager::getInstance()->draw(image, getLink()->getX() > x + 24 ? width : 0, anim * height, width, height, dstX, dstY);

        if (life > 2) {
            WindowManager::getInstance()->draw(imageBis, 0, 0, 16, 16, 89*16 - offsetX, 24*16 - offsetY);
            WindowManager::getInstance()->draw(imageBis, 0, 0, 16, 16, 90*16 - offsetX, 24*16 - offsetY);
        }

    }

}

int Ennemi057::getX() {
    return x;
}

int Ennemi057::getY() {
    return y;
}

BoundingBox* Ennemi057::getBoundingBox() {
    return &box;
}

void Ennemi057::afterHit() {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (life <= 2 && map->getMur(89*16, 24*16) == MURRET) {
        map->setSol(89*16, 24*16, 2, 1, 1615, PIERRE);
        map->addEffect(new FumeeBlanche(89*16+8, 24*16+8));
        map->addEffect(new FumeeBlanche(90*16+8, 24*16+8));
    }
}

void Ennemi057::giveItem(int i, int j) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 0));
    for (int i = 0; i < 3; i++) {
        if (ennemis[i] != 0 && ennemis[i]->isAlive()) {
            ennemis[i]->underAttack(S, 1, TA_PHYSIC, TE_NORMAL, ennemis[i]->getBoundingBox());
            ennemis[i]->setResetableToFalse();
            ennemis[i] = 0;
        }
    }
}
