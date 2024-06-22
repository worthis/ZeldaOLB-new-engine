#include "Ennemi040.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi040::Ennemi040(int i, int j) : anim(0), animMax(2), vanim(180), cooldown(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi40.png", true);
    chrono.reset();

    type = 40;

    x = i;
    y = j;

    // for quadtree operations:
    width = 54;
    height = 42;

    box.setX(x + 11);
    box.setY(y + 10);
    box.setW(32);
    box.setH(32);

    life = 20;
    maxLife = 20;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi040::~Ennemi040() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi040::reset() {
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
}

bool Ennemi040::isResetable() {
    return alive;
}

void Ennemi040::ennLoop() {

    // move
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    switch (randomValue) {
        case 1 : moveX(-1);direction=W; break;
        case 2 : moveX(1); direction=E; break;
        case 3 : moveY(-1);direction=N; break;
        case 4 : moveY(1); direction=S; break;
        default :
            if (randomValue < 10) break;
            switch (direction) {
                case N : moveY(-1); break;
                case S : moveY(1); break;
                case W : moveX(-1); break;
                case E : moveX(1); break;
            }
            break;
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        cooldown++;
        if (cooldown == 16) {

            // retrieve target position ( = link ^^)
            Link* link = getLink();

            int dstX = link->getX() + 8;
            int dstY = link->getY() + 24;

            // throw proj and play sound
            double anglx = 0;
            double angly = 0;
            int origx = x + 27;
            int origy = y + 18;
            int destx = dstX;
            int desty = dstY - 8;

            double coef1 = 0;
            double coef2 = 0;

            if ((destx-origx) == 0) {anglx=0; angly=12;}
            else if ((desty-origy) == 0) {anglx=12; angly=0;}
            else {
                coef1=((double)(desty-origy))/((double)(destx-origx));
                coef2=((double)(destx-origx))/((double)(desty-origy));
                anglx=(sqrt(12/(1+(coef1*coef1))));
                angly=(sqrt(12/(1+(coef2*coef2))));
            }
            if (destx - origx < 0) anglx = -anglx;
            if (desty - origy < 0) angly = -angly;

            if (anglx>4) anglx=4;
            if (angly>4) angly=4;
            if (anglx<-4) anglx=-4;
            if (angly<-4) angly=-4;

            ProjectileHelper::getInstance()->addProjectile(TP_BIG_FEU, origx, origy, anglx, angly);
            AudioManager::getInstance()->playSound(TS_THROW);
            cooldown = 0;
        }
        chrono.reset();
    }
}

void Ennemi040::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);

}

void Ennemi040::moveX(int dx) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + 11 + dx);

    if (map->checkCollisions(bb, this, true, false, true, false)) {
        x += dx;
    }

    if (x != oldX) checkPosition();
}

void Ennemi040::moveY(int dy) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(y + 10 + dy);

    if (map->checkCollisions(bb, this, false, false, true, false)) {
        y += dy;
    }

    if (y != oldY) checkPosition();
}

int Ennemi040::getX() {
    return x;
}

int Ennemi040::getY() {
    return y;
}

BoundingBox* Ennemi040::getBoundingBox() {
    box.setX(x + 11);
    box.setY(y + 10);
    return &box;
}

void Ennemi040::giveItem(int i, int j) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 5));
    map->disablePiege();
}
