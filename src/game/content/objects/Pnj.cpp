#include "Pnj.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

#include "../../algo/AStar.h"

Pnj::Pnj(int i, int j, int tp, int txt) : type(tp), texte(txt), anim(0), animMax(0), vanim(480), w(0), h(0),
    displayW(0), displayH(0), idle(true), direction(S), stop(false) {
    x = i;
    y = j;

    image = 0;

    ostringstream os;
    os << type;
    image = ResourceManager::getInstance()->loadImage("data/images/npcs/personnage" + os.str() + ".png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    w = width;
    h = height;

    displayW = w;
    displayH = h;

    init();

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    chrono.reset();
}

Pnj::~Pnj() {
    ResourceManager::getInstance()->free(image);
}

void Pnj::init() {
    switch (type) {
        case 1 : idle = false; height = 25; animMax = 1; vanim = 240; break;
        case 2 : height = 24; h = height; displayH = h; animMax = 1; break;
        case 3 : idle = false; height = 23; h = height; displayH = h; animMax = 1; vanim = 240; break;
        case 4 : idle = false; height = 17;  h = height; displayH = h; animMax = 3; vanim = 240; break;
        case 5 : idle = false; width = 13; w = width; displayW = w; animMax = 1; vanim = 240; break;
        case 6 : idle = false; width = 15; w = width; displayW = w; animMax = 1; vanim = 240; break;
        case 7 : height = 25; h = height; displayH = h; animMax = 1; break;
        case 8 : height = 23; h = height; displayH = h; animMax = 1; vanim = 240; break;
        case 9 : height = 27; h = height; displayH = h; animMax = 1; break;
        case 10 : height = 26; h = height; displayH = h; animMax = 3; break;
        case 11 : idle = false; height = 24; animMax = 1; vanim = 240; break;
        case 12 : height = 25; h = height; displayH = h; animMax = 1; break;
        case 13 : idle = false; height = 25; animMax = 1; vanim = 240; break;
        case 14 : idle = false; height = 25; animMax = 1; vanim = 240; break;
        case 15 : height = 23; h = height; displayH = h; animMax = 1; vanim = 240; break;
        case 16 : height = 48; h = height; displayH = h; width = 32; w = width; displayW = w; animMax = 1; break;
        case 17 : height = 25; h = height; displayH = h; width = 18; w = width; displayW = w; animMax = 1; break;
        case 18 : height = 24; h = height; displayH = h; animMax = 1; break;
        case 19 : height = 25; h = height; displayH = h; animMax = 1; break;
        case 20 : height = 26; h = height; displayH = h; animMax = 3; break;
        case 21 : height = 25; h = height; displayH = h; width = 17; w = width; displayW = w; animMax = 1; break;
        case 22 : height = 29; h = height; displayH = h; animMax = 3; break;
        case 23 : idle = false; height = 25; animMax = 1; vanim = 240; break;
        case 24 : height = 21; h = height; displayH = h; animMax = 1; break;
        case 25 : height = 25; h = height; displayH = h; animMax = 1; break;
        case 26 : height = 30; h = height; displayH = h; width = 39; w = width; displayW = w; animMax = 3; vanim = 240; break;
        case 27 : height = 17; h = height; displayH = h; animMax = 1; break;
        case 28 : height = 35; h = height; displayH = h; width = 25; w = width; displayW = w; animMax = 4; vanim = 240; break;
        case 29 : height = 27; h = height; displayH = h; width = 21; w = width; displayW = w; animMax = 4; vanim = 240; break;
        case 30 : height = 17; h = height; displayH = h; animMax = 1; break;
        case 31 : height = 17; h = height; displayH = h; animMax = 1; break;
        case 33 : height = 25; h = height; displayH = h; animMax = 1; vanim = 240; break;
        case 34 : height = 25; h = height; displayH = h; animMax = 1; break;
        case 35 : height = 22; h = height; displayH = h; animMax = 3; break;
        case 36 : idle = false; height = 24; animMax = 1; vanim = 240; break;
        case 37 : idle = false; height = 22; h = height; displayH = h; width = 19; w = width; displayW = w; animMax = 1; break;
        case 38 : idle = false; animMax = 1; vanim = 240; break;
        case 39 : width = 24; w = width; displayW = w; animMax = 1; break;
        case 40 : height = 23; h = height; displayH = h; animMax = 1; break;
        case 41 : height = 23; h = height; displayH = h; animMax = 1; break;
        case 42 : height = 23; h = height; displayH = h; animMax = 1; break;
        case 43 : height = 24; h = height; displayH = h; animMax = 1; break;
        case 44 : height = 28; h = height; displayH = h; width = 28; w = width; displayW = w; animMax = 0; break;
        case 45 : height = 24; h = height; displayH = h; animMax = 1; break;
        case 46 : height = 27; h = height; displayH = h; width = 22; w = width; displayW = w; animMax = 0; break;
        case 47 : height = 24; h = height; displayH = h; animMax = 1; vanim = 240; break;
        case 48 : height = 48; h = height; displayH = h; width = 32; w = width; displayW = w; animMax = 1; break;
        case 49 : animMax = 1; vanim = 240; break;
        case 50 : animMax = 1; vanim = 240; break;
        case 51 : idle = false; height = 27; h = height; displayH = h; animMax = 1; vanim = 240; break;
        case 52 : idle = false; height = 24; animMax = 1; vanim = 240; break;
        case 53 : height = 17; h = height; displayH = h; animMax = 1; break;
        case 54 : height = 23; h = height; displayH = h; animMax = 1; break;
        case 55 : height = 25; h = height; displayH = h; width = 17; w = width; displayW = w; animMax = 1; break;
        case 110 : height = 40; h = height; displayH = h; width = 44; w = width; displayW = w; animMax = 0; break;
    }
    if (type == 47 && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAvancement() == AV_TUTO_OK) {
        direction = N;
    }
}

void Pnj::loop() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (type) {
        case 33 :
            if (scene->getAvancement() == AV_MINE_OUVERTE) {
                if (x == 72 * 16 + 8 && y < 16 * 16) {
                    direction = S;
                    moveY(1);
                } else if (x < 74 * 16) {
                    direction = E;
                    moveX(1);
                    break;
                } else if (y > 15 * 16 + 8) {
                    direction = N;
                    moveY(-1);
                } else {
                    direction = S;
                }
            }
            break;
        case 46 :
            if (scene->getAvancement() == AV_MANOIR_OUVERT) {
                if (y < 13 * 16 + 5) {
                    animMax = 1;
                    moveY(1);
                }
                else if (x > 13 * 16 + 8 - 3) {
                    moveX(-1);
                } else {
                    animMax = 0;
                }
            }
            break;
        case 47 :
            if (scene->getMap()->getId() == 1 && scene->getAvancement() >= AV_PIT_A_VOIR) {
                if (y < 16 * 16) {
                    direction = S;
                    moveY(1);
                } else if (x < 40 * 16 + 8) {
                    direction = E;
                    moveX(1);
                } else {
                    alive = false;
                    scene->getAnimationInGame()->stop();
                }
            }
            break;
        case 49 :
            if (scene->getAvancement() >= AV_PASSE_ONI) {
                if (x < 13 * 16) {
                    moveX(1);
                } else if (y > 5 * 16) {
                    moveY(-1);
                }
            }
            break;
        case 50 :
            if (scene->getAvancement() >= AV_PASSE_OK) {
                if (x > 6 * 16) {
                    moveX(-1);
                } else if (y > 5 * 16) {
                    moveY(-1);
                }
            }
            break;
        case 110 :
            if (scene->getAvancement() >= AV_GANON_VU) {
                alive = false;
            }
            break;
    }

    if (!idle) {

        BoundingBox bb(x - 16*2, y - 16*2, width + 32*2, height + 32*2);
        stop = !scene->checkCollisionsWithLink(&bb);

        if (stop) {
            BoundingBox* bblink = scene->getLink()->getBoundingBox();
            int dN = y - (bblink->getY() + bblink->getH());
            int dS = bblink->getY() - (y + height);
            int dW = x - (bblink->getX() + bblink->getW());
            int dE = bblink->getX() - (x + width);
            if (dN >= dS && dN >= dW && dN >= dE) direction = N;
            if (dS >= dN && dS >= dW && dS >= dE) direction = S;
            if (dW >= dS && dW >= dN && dW >= dE) direction = W;
            if (dE >= dS && dE >= dW && dE >= dN) direction = E;
        } else {
            // move
            int randomValue = (int)((float)rand() / RAND_MAX * (100));
            switch (randomValue) {
                case 1 : moveX(-1);direction=W; break;
                case 2 : moveX(1); direction=E; break;
                case 3 : moveY(-1);direction=N; break;
                case 4 : moveY(1); direction=S; break;
                default :
                    if (randomValue < 8) break;
                    switch (direction) {
                        case N : moveY(-1); break;
                        case S : moveY(1); break;
                        case W : moveX(-1); break;
                        case E : moveX(1); break;
                    }
                    break;
            }
        }
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Pnj::draw(int offsetX, int offsetY) {
    if (idle) {
        switch (type) {
            case 15 : case 33 : case 47 :
                WindowManager::getInstance()->draw(image, width * direction, h * anim, displayW, displayH, x - offsetX, y - offsetY);
                break;
            case 46 :
                if (animMax == 0) {
                    WindowManager::getInstance()->draw(image, 0, h * 2, displayW, displayH, x - offsetX, y - offsetY);
                } else {
                    WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
                }
                break;
            default :
                WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
                break;
        }
    } else {
        switch (type) {
            case 3 : case 6 : case 51 :
                WindowManager::getInstance()->draw(image, width * (direction%2), h * anim, displayW, displayH, x - offsetX, y - offsetY);
                break;
            case 4 :
                WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
                break;
            default :
                WindowManager::getInstance()->draw(image, width * direction, height * anim, width, height, x - offsetX, y - offsetY);
                break;
        }

    }
}

bool Pnj::action(Direction dir) {
    MainController::getInstance()->getGameController()->displayText(getDynamicText());
    return true;
}

BoundingBox* Pnj::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    if (idle) {
        box.setW(w);
        box.setH(h);
    }
    if (type == 15) {
        box.setY(y+7);
        box.setH(16);
    }
    if (type == 28) {
        box.setX(x+9);
        box.setW(16);
    }
    if (type == 29) {
        box.setX(x+5);
        box.setW(16);
    }
    if (type == 33) {
        box.setY(y+9);
        box.setH(16);
    }
    if (type == 46) {
        box.setY(y+11);
        box.setH(16);
    }
    return &box;
}

int Pnj::getDown() {
    if (idle) {
        return y + displayH;
    } else {
        return y + height;
    }
}

int Pnj::getDynamicText() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    //int tmp = 0;
    switch (texte) {
        case 188 :
            if (link->getInventory()->hasObject(FLACON_1)) {
                return 193;
            }
            break;
        case 194:
            if (scene->getAvancement() >= AV_CHERCHE_BOMBES && !link->getInventory()->hasObject(BOMBES)) {
                return 195;
            }
            break;
        case 197 :
            if (scene->getAvancement() < AV_CHERCHE_MINE || scene->getAvancement() >= AV_MINE_OUVERTE) {
                return 200;
            }
            if (scene->getAvancement() == AV_HOMME_PIEGE_MINE) {
                return 198;
            }
            if (scene->getAvancement() == AV_AUTORISATION_MINE) {
                return 199;
            }
            break;
        case 222 :
            if (scene->getAvancement() >= AV_MANOIR_OUVERT) {
                return 200;
            }
            if (scene->getAvancement() == AV_AUTORISATION_MANOIR) {
                return 223;
            }
            break;
        case 224 :
            if (link->getBouclier() >= 2) {
                return 227;
            }
            break;
        case 232 :
            if (link->getInventory()->hasObject(OCARINA)) {
                return 233;
            }
            break;
        case 320 :
            if (link->getInventory()->hasObject(BOMBES)) {
                return 200;
            }
            break;
        case 324 :
            if ((scene->getCoffre(2, 5) && x == 16*174)
                || (scene->getCoffre(2, 6) && x == 16*185)
                || (scene->getCoffre(2, 7) && x == 16*194)) {
                return 200;
            }
            break;
        case 329 :
            if (link->getInventory()->hasObject(ARC)) {
                return 200;
            }
            break;
        case 332 :
            if (scene->getAvancement() >= AV_FILLE_MAIRE_SAUVEE) {
                return 333;
            }
            break;
        case 347 :
            if ((scene->getCoffre(9, 27) && scene->getMap()->getId() == 23)
                || (scene->getCoffre(10, 27) && scene->getMap()->getId() == 24)
                || (scene->getCoffre(11, 24) && scene->getMap()->getId() == 25)) {
                return 200;
            }
            break;
        case 369 :
            if (link->getStatus()->getMaxMagic() == 64) {
                return 200;
            }
            break;
        case 372 :
            if (scene->getCoffre(0, 11)) {
                if (link->getStatus()->getMaxBombs() == 30 && link->getStatus()->getMaxArrows() == 70) {
                    return 379;
                }
                return 373;
            }
            break;
        case 380 :
            if (scene->getAvancement() >= AV_PASSE_ONI) {
                return 200;
            }
            if (link->getStatus()->isOniLink()) {
                return 382;
            }
            break;
        case 381 :
            if (scene->getAvancement() >= AV_PASSE_OK) {
                return 200;
            }
            if (!link->getStatus()->isOniLink()) {
                return 383;
            }
            break;
        case 385 :
            if (scene->getAvancement() == AV_ARMEE_UP) {
                return 416;
            }
            if (link->getEpee() == 5 && link->getInventory()->hasObject(CHANT_3) && scene->getAvancement() < AV_GANON_VU) {
                return 414;
            }
            if (link->getEpee() > 1 && scene->getAvancement() < AV_GANON_VU) {
                return 412;
            }
            if (scene->getAvancement() == AV_ZELDA_CHEZ_PIT) {
                return 200;
            }
            if (scene->getAvancement() == AV_PIT_VU && link->getInventory()->hasGraal(0)) {
                return 391;
            }
            if (scene->getAvancement() >= AV_PIT_VU) {
                return 390;
            }
            break;
        case 400 :
            if (scene->getCoffre(0, 12)) {
                return 424;
            }
            if (scene->getAvancement() >= AV_ARMEE_DOWN) {
                return 418;
            }
            if (scene->getAvancement() == AV_ARMEE_UP) {
                return 415;
            }
            if (link->getEpee() == 5 && link->getInventory()->hasObject(CHANT_3)) {
                return 413;
            }
            if (link->getEpee() > 1) {
                return 411;
            }
            break;
        case 442 :
            if (scene->getMap()->areChestsClosed()) {
                return 445;
            }
            if (!link->getInventory()->hasQuartCoeur(15)) {
                return 443;
            }
            break;
        case 449 :
            if (scene->getAvancement() >= AV_MINE_FERMEE && !link->getInventory()->hasObject(BOMBES)) {
                return 448;
            }
            break;
        case 450 :
            if (scene->getAvancement() == AV_HOMME_PIEGE_MINE) {
                return 451;
            }
            break;
        case 469 :
            if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0)
                || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0)
                || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0)) {
                return 470;
            }
            break;
        case 447 :
            if (scene->getCoffre(0, 15)) {
                return 482;
            }
            break;
        case 480 :
            if (scene->getCoffre(0, 15)) {
                return 479;
            }
            if (link->getInventory()->hasGraal(3)) {
                return 481;
            }
            break;
        case 483 :
            if (scene->getAvancement() == AV_MAIRE_VU) {
                return 484;
            }
            if (scene->getAvancement() == AV_INFO_MAIRE_OK) {
                return 486;
            }
            if (scene->getCoffre(0, 17)) {
                return 487;
            }
            if (scene->getCoffre(0, 16)) {
                return 488;
            }
            break;
        case 489 :
            if (scene->getAvancement() < AV_INFO_MAIRE_OK) {
                scene->setAvancement(AV_MAIRE_VU);
                return 200;
            }
            if (scene->getAvancement() == AV_AUTORISATION_MANOIR) {
                return 494;
            }
            if (scene->getAvancement() > AV_AUTORISATION_MANOIR && scene->getAvancement() < AV_FILLE_MAIRE_SAUVEE) {
                return 495;
            }
            if (scene->getAvancement() == AV_FILLE_MAIRE_SAUVEE && !link->getInventory()->hasObject(CHANT_1)) {
                return 496;
            }
            if (scene->getAvancement() >= AV_FILLE_MAIRE_SAUVEE) {
                return 500;
            }
            break;
        case 502 :
            if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0)
                || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0)
                || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0)) {
                break;
            }
            return 469;
        case 504 :
            if (link->getInventory()->hasObject(GRAPPIN)) {
                return 506;
            }
            break;
        case 516 :
            if (link->getInventory()->hasObject(MASQUE)) {
                return 522;
            }
            if (link->getInventory()->hasObject(MASQUE_VIDE) && !link->getInventory()->hasObject(CHANT_3)) {
                return 518;
            }
            if (link->getInventory()->hasObject(MASQUE_VIDE)) {
                return 521;
            }
            break;
        case 524 :
            if (scene->getAvancement() == AV_SAGE_DESERT_VU && link->getInventory()->hasObject(BAGUETTE_FEU) && !link->getInventory()->hasObject(CHANT_2)) {
                return 528;
            }
            if (link->getInventory()->hasObject(CHANT_2)) {
                return 531;
            }
            if (scene->getAvancement() == AV_SAGE_DESERT_VU) {
                return 527;
            }
            break;
        /*case 194 :
            if (!link->getInventory()->hasObject(LIVRE)) {
                return 197;
            }
            if (scene->getAvancement() == AV_AUTORISATION_OK) {
                scene->setAvancement(AV_GARDE_DEPLACE);
                return 195;
            } else if (scene->getAvancement() >= AV_GARDE_DEPLACE) {
                return 196;
            }
            break;
        case 198 : case 199 : case 200 : case 314 : case 326 :
            if (!link->getInventory()->hasObject(LIVRE)) {
                return 197;
            }
            break;
        case 224 :
            if (scene->getAvancement() == AV_ZELDA_SUIT) {
                return 225;
            }
            break;
        case 227 :
            if (link->getEpee() == 5) {
                return 228;
            }
            break;
        case 237 :
            if ((scene->getMap()->getId() == 23 && link->getInventory()->hasMedaillons(0))
                || (scene->getMap()->getId() == 24 && link->getInventory()->hasMedaillons(1))
                || (scene->getMap()->getId() == 25 && link->getInventory()->hasMedaillons(2))
                || (scene->getMap()->getId() == 26 && link->getStatus()->getMaxMagic() == 64)) {

                if (link->getStatus()->getVirtualLife() >= link->getStatus()->getMaxLife()) {
                    return 241;
                } else {
                    return 240;
                }

            }
            if (scene->getMap()->getId() == 26) {
                return 242;
            }
            if (scene->getMap()->getId() != 23) {
                return 237 + scene->getMap()->getId() - 23;
            }
        break;
        case 244 :
            if (link->getInventory()->hasObject(ENCYCLOPEDIE)) {
                if (link->getInventory()->hasQuartCoeur(31)) {
                    if (scene->getTotalMonsters() == 46) {
                        return 254;
                    } else {
                        return 253;
                    }
                }

                int currentNb = scene->getMonstersForPrice();

                if (currentNb >= 7) {
                    return 252;
                }
                if (currentNb == 6) {
                    return 251;
                }
                return 250;
            } else {
                link->getInventory()->setObject(ENCYCLOPEDIE);
            }
        case 255 :
        if (scene->getAvancement() >= AV_MAIRE_VU) {
                if (scene->getAvancement() >= AV_MARCHANT_OK) {
                    if (link->getInventory()->nbGraals() == 5) {
                        if (scene->getAvancement() >= AV_ZELDA_ARRIVEE) {
                            if (link->getEpee() < 5) {
                                return 268;
                            }
                            return 271;
                        }
                        return 267;
                    }
                    return 266;
                }
                return 265;
            }
            break;
        case 272 :
            if (scene->getMap()->getId() == 41 && !link->getInventory()->hasObject(LIVRE)) {
                return 197;
            }

            if ((scene->getMap()->getId() == 30 && link->getInventory()->hasQuartCoeur(32))
                || (scene->getMap()->getId() == 37 && link->getInventory()->hasQuartCoeur(34))
                || (scene->getMap()->getId() == 41 && link->getInventory()->hasQuartCoeur(35))) {
                return 275;
            }
            if (scene->getMap()->areChestsClosed()) {
                return 274;
            }
            break;
        case 296 :
            if (scene->getAvancement() == AV_MAIRE_VU) {
                scene->setAvancement(AV_MARCHANT_OK);
                return 297;
            }
            break;
        case 300 :
            if (link->getInventory()->nbCristaux() >= 3) {
                if (link->getEpee() == 1) {
                    return 302;
                }
                if (link->getInventory()->getCurrent() == GANTS) {
                    return 304;
                }
                if (link->getInventory()->getCurrent() == ARC && link->getInventory()->nbCristaux() == 7) {
                    return 306;
                }
                return 301;
            }
            break;
        case 310 :
            if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0)
                || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0)
                || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0)) {
                return 311;
            }
            break;
        case 315 :
            if (!link->getInventory()->hasObject(LIVRE)) {
                return 197;
            }
            if (link->getEpee() == 5) {
                return 321;
            }
            if (scene->getAvancement() == AV_AUTORISATION_OK) {
                return 318;
            }
            if (scene->getAvancement() > AV_AUTORISATION_OK && scene->getAvancement() < AV_ZELDA_ARRIVEE) {
                return 319;
            }
            if (scene->getAvancement() == AV_ZELDA_ARRIVEE) {
                return 320;
            }
            break;
        case 323 :
            if (!link->getInventory()->hasObject(LIVRE)) {
                return 197;
            }
            if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0)
                || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0)
                || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0)) {
                return 324;
            }
            break;*/
        default : break;
    }
    return texte;
}

void Pnj::moveX(int dx) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(bb->getX() + dx);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb)) {
        x += dx;
    }

    if (x != oldX) checkPosition();
}

void Pnj::moveY(int dy) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(bb->getY() + dy);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb)) {
        y += dy;
    }

    if (y != oldY) checkPosition();
}

void Pnj::moveTo(int i, int j, Direction dir) {
    x = i;
    y = j;
    direction = dir;
    checkPosition();
}
