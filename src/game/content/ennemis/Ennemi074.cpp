#include "Ennemi074.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi074::Ennemi074(int i, int j) : anim(0), animMax(3), vanim(180), cooldown(1) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi74.png", true);
    chrono.reset();

    type = 74;

    x = i;
    y = j;

    // for quadtree operations:
    width = 104;
    height = 153;

    box.setX(x + 36);
    box.setY(y + 38);
    box.setW(32);
    box.setH(64);

    tail.setX(x + 58);
    tail.setY(y + 38);
    tail.setW(16);
    tail.setH(112);

    life = 60;
    maxLife = 60;
    recul = 0;
    vitesseRecul = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 24;
}

Ennemi074::~Ennemi074() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi074::reset() {
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 1;
}

bool Ennemi074::isResetable() {
    return alive;
}

void Ennemi074::ennLoop() {
    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    testDegatOnLink(getBoundingBoxTail(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (y < 240 && y > 240-152) {
        y++;
        checkPosition();
    }

    if (chrono.getElapsedTime() >= vanim) {
        //if (y < 0) y++;
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (y == 240) cooldown++;
        }
        if (cooldown == 5) {

            // retrieve target position ( = link ^^)
            Link* link = getLink();

            int dstX = link->getX() + 8;
            int dstY = link->getY() + 24;

            // throw proj and play sound
            double anglx = 0;
            double angly = 0;
            int origx = x + 30;
            int origy = y + 72;
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

            ProjectileHelper::getInstance()->addProjectile(TP_BIG_GLACE, origx, origy, anglx, angly);
            AudioManager::getInstance()->playSound(TS_THROW);
            cooldown = 0;
        }
        chrono.reset();
    }
}

void Ennemi074::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (cooldown || anim) {
        WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, 4 * width, 0, width, height, dstX, dstY);
    }
}

int Ennemi074::getX() {
    return x;
}

int Ennemi074::getY() {
    return y;
}

BoundingBox* Ennemi074::getBoundingBox() {
    box.setX(x + 36);
    box.setY(y + 38);
    return &box;
}

BoundingBox* Ennemi074::getBoundingBoxTail() {
    tail.setX(x + 58);
    tail.setY(y + 38);
    return &tail;
}

void Ennemi074::start() {
    y++;
    checkPosition();
}

bool Ennemi074::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return effect == TE_FEU;
}

void Ennemi074::giveItem(int i, int j) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->nbEnnemis() == 0) {
        map->addEffect(new FumeeBlanche(i, j));
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, 190*16+1, 22*16, 10));
    } else {
        Ennemi::giveItem(i, j);
    }
}
