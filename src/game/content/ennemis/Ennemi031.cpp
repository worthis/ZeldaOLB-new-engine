#include "Ennemi031.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi031::Ennemi031(int i, int j) : anim(0), animMax(9), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi31.png", true);

    type = 31;
    chrono.reset();

    attLapin = 0;
    attEclair = 0;
    nbHit = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 16;
    maxLife = 16;
    recul = 0;
    vitesseRecul = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi031::~Ennemi031() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi031::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    attLapin = 0;
    attEclair = 0;
    nbHit = 0;
    checkPosition();
}

bool Ennemi031::isResetable() {
    return alive;
}

void Ennemi031::ennLoop() {

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }

        if (anim == 8) {
            if (attLapin) {
                snipe();
                attLapin--;
            } else if (attEclair) {
                ProjectileHelper::getInstance()->addProjectile(TP_ECLAIR, x + 16, y + 24, S);
                AudioManager::getInstance()->playSound(TS_MAGIC);
                attEclair--;
            } else {
                ProjectileHelper::getInstance()->addProjectile(TP_BOULE_ULTIME, x + 16, y + 24, getLink());
                AudioManager::getInstance()->playSound(TS_THROW);
            }
        }
        chrono.reset();
    }
}

void Ennemi031::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int anim2 = anim > 3 ? 3 : anim;

    WindowManager::getInstance()->draw(image, anim2 * width, 0, width, height, dstX, dstY);
}

void Ennemi031::snipe() {

    // throw proj and play sound
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    double anglx = 0;
    double angly = 0;
    int origx = x + 16;
    int origy = y + 24;
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

    ProjectileHelper::getInstance()->addProjectile(TP_LAPIN, origx, origy, anglx, angly);
    AudioManager::getInstance()->playSound(TS_MAGIC);
}

int Ennemi031::getX() {
    return x;
}

int Ennemi031::getY() {
    return y;
}

BoundingBox* Ennemi031::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

bool Ennemi031::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return type == TA_MAGIC && effect == TE_NORMAL;
}

void Ennemi031::afterHit() {
    attLapin = 1;
    attEclair = ++nbHit;
}

void Ennemi031::giveItem(int x, int y) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    //map->addItem(ItemHelper::getInstance()->createItem(TI_CRISTAL, x, y, 3));
}
