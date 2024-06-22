#include "Hud.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

Hud::Hud(Status* status, Inventory* inventory, bool isFrench) : status(status), inventory(inventory), french(isFrench), animOni(0),
animBoss(0), animBoss2(0), animBossX(0), bossLife(0), bossMaxLife(0), bossLife2(0), bossMaxLife2(0), removeBoss(false), etage(0), displayEtg(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/status/status.png", true);
    chiffres = ResourceManager::getInstance()->loadImage("data/images/status/chiffres.png", true);
    level = ResourceManager::getInstance()->loadImage("data/images/status/level.png", true);
}

Hud::~Hud() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(chiffres);
    ResourceManager::getInstance()->free(level);
}

void Hud::loop() {
    if (animBoss > 0 && (bossLife <= 0 || removeBoss))  {
        animBoss--;
    } else if (animBoss > 0 && animBoss < 50) {
        animBoss++;
    }
    if (animBoss2 > 0 && (bossLife2 <= 0 || removeBoss))  {
        animBoss2--;
    } else if (animBoss2 > 0 && animBoss2 < 50) {
        animBoss2++;
    }
    if (animBoss && animBoss2 && animBossX < 50) {
        animBossX++;
    }
    if (animBossX > 0 && (animBoss == 0 || animBoss2 == 0)) {
        animBossX--;
    }
    if (animOni > 0)  {
        animOni--;
    }

    if (displayEtg) displayEtg--;
}

void Hud::draw() {
    drawLife();
    drawOni();
    drawMagic();
    drawItems();
    drawObject();
    drawBonus();
    drawBoss();
    drawEtage();
}

void Hud::reset() {
    removeBoss = true;
}

void Hud::displayEtage() {
    displayEtg = 128;
    etage = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getEtage();
    if (etage == 3) {
        displayEtg = 0;
    }
}

void Hud::drawEtage() {
    if (displayEtg) {
        WindowManager::getInstance()->draw(level, french ? 0 : 32, 32 - etage * 16, 32, 16, 288, 0);
    }
}

void Hud::setBossLife(int life, int maxLife) {
    bossLife = life;
    bossMaxLife = maxLife;
    removeBoss = false;
    if (animBoss == 0) {
        animBoss = 1;
    }
}

void Hud::setBossLife2(int life, int maxLife) {
    bossLife2 = life;
    bossMaxLife2 = maxLife;
    removeBoss = false;
    if (animBoss2 == 0) {
        animBoss2 = 1;
    }
}

void Hud::drawBoss() {
    if (animBoss) {
        int dstY = 220 + 50 - animBoss;
        WindowManager::getInstance()->draw(image, 100, 45, 100, 10, 110 - animBossX, dstY);
        int srcW = (bossLife * 90) / bossMaxLife;
        WindowManager::getInstance()->draw(image, 95 - srcW, 49, srcW, 2, 115 - animBossX, dstY + 4);
    }
    if (animBoss2) {
        int dstY = 220 + 50 - animBoss2;
        WindowManager::getInstance()->draw(image, 100, 45, 100, 10, 110 + animBossX, dstY);
        int srcW = (bossLife2 * 90) / bossMaxLife2;
        WindowManager::getInstance()->draw(image, 95 - srcW, 49, srcW, 2, 115 + animBossX, dstY + 4);
    }
}

void Hud::drawBonus() {
    int dstX = 320 - 24;
    int dstY = 240 - 24;
    if (status->getGel()) {
        WindowManager::getInstance()->draw(image, 104, 55, 12, 12, dstX + 2, dstY);
        WindowManager::getInstance()->draw(image, 68, 67, 16, 3, dstX, dstY + 13);
        int value = (status->getGel() * 14) / status->getMaxGel();
        if (value < 14) value ++;
        WindowManager::getInstance()->draw(image, 49, 65, value, 1, dstX + 1, dstY + 14);
    }
}

void Hud::drawLife() {

    //life
    int srcY = french ? 17 : 0;
    int srcH = french ? 8 : 7;
    WindowManager::getInstance()->draw(image, 158, srcY, 44, srcH, 250, 10);

    //hearts
    int srcX = 0;
    int life = status->getLife();
    for(int i = 0; i < status->getMaxLife() / 2; i++) {
        if (life - (i * 2) > 1) srcX = 141;
        if (life - (i * 2) == 1) srcX = 149;
        if (life - (i * 2) < 1) srcX = 157;

        WindowManager::getInstance()->draw(image, srcX, 9, 7, 7, 233 + ((i % 10) * 8), 19 + 8 * ((int)(i / 10)));
    }
}

void Hud::drawOni() {

    int dstX = animOni ? animOni - 10 : 10;

    // jaugeOni
    if (status->isOniLinkable() || animOni) {
        WindowManager::getInstance()->draw(image, 212, 0, 10, 45, dstX, 10);
        int ratio = (status->getValueOni() * 32) / status->getMaxOni();
        WindowManager::getInstance()->draw(image, 222, 8, 8, ratio, dstX, 50 - ratio);
    }
}

void Hud::drawMagic() {

    int dstX = animOni ? animOni : 10;
    if (dstX < 10) dstX = 10;
    if (status->isOniLinkable()) dstX += 10;

    //jauge magie
    if (status->getMaxMagic() > 0) {
        WindowManager::getInstance()->draw(image, 0, 0, 16, 45, dstX, 10);

        //demi magie
        if (status->getMaxMagic() > 32) {
            WindowManager::getInstance()->draw(image, 186, 37, 16, 8, dstX, 10);
        }

        int ratio = status->getMagic() / (status->getMaxMagic() / 32);
        WindowManager::getInstance()->draw(image, 124, 8, 8, ratio, dstX + 4, 50 - ratio);
    }
}

void Hud::drawItems() {

    //rupees
    WindowManager::getInstance()->draw(image, 52, 0, 8, 8, 129, 10);
    drawNombre(status->getRupees(), status->getMaxRupees(), 121, 20, 3);

    //bombs
    if (inventory->hasObject(BOMBES)) {
        WindowManager::getInstance()->draw(image, 80, 0, 8, 8, 157, 10);
        drawNombre(status->getBombs(), status->getMaxBombs(), 153, 20, 2);
    }

    //arrows
    if (inventory->hasObject(ARC)) {
        int srcY = inventory->hasObject(ARC_FEE) ? 21 : 0;
        WindowManager::getInstance()->draw(image, 101, srcY, 14, 8, 178, 10);
        drawNombre(status->getArrows(), status->getMaxArrows(), 177, 20, 2);
    }

    //keys
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (scene->getMap()->getId() >= 15 && scene->getMap()->getId() < 29) {
        int nbKeys = scene->getCoffre(scene->getMap()->getId() - 14, 3);
        WindowManager::getInstance()->draw(image, 50, 28, 8, 8, 89, 10);
        drawNombre(nbKeys, 99, nbKeys > 9 ? 85 : 89, 20, nbKeys > 9 ? 2 : 1);
    }
}

void Hud::drawObject() {
    if (inventory->hasObject()) {

        int dstX = animOni ? animOni : 10;
        if (dstX < 10) dstX = 10;
        if (status->isOniLinkable()) dstX += 10;
        if (status->getMaxMagic() > 0) dstX += 17;

        WindowManager::getInstance()->draw(image, 17, 5, 22, 22, dstX, 15);

        Equipment e = inventory->getCurrent();
        if (inventory->hasObject(e)) {
            if (e == BOMBES && !status->getBombs()) {
                return;
            }
            inventory->draw(e, dstX + 3, 18);
        }
    }
}

void Hud::drawNombre(int val, int max, int x, int y, int nb) {
    int val2;
    int srcX;
    int srcY;
    int dstX = x;

    //si on commence par les centaines
    if (nb >= 3) {
        val2 = val / 100;
        srcX = (val2%5)*8;
        srcY = ((int)(val2/5))*8;
        if (val == max) srcY += 16;
        WindowManager::getInstance()->draw(chiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    //les dizaines
    if (nb >= 2) {
        val2 = (val%100)/10;
        srcX = (val2%5)*8;
        srcY = ((int)(val2/5))*8;
        if (val == max) srcY += 16;
        WindowManager::getInstance()->draw(chiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    //unitées
    val2 = val%10;
    srcX = (val2%5)*8;
    srcY = ((int)(val2/5))*8;
    if (val == max) srcY += 16;
    WindowManager::getInstance()->draw(chiffres, srcX, srcY, 8, 8, dstX, y);

}
