#include "Interrupteur.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

Interrupteur::Interrupteur(int i, int j, int id, bool down, Map* mp, bool us) : type(id), used(down), usedTmp(false), map(mp), usable(us) {
    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    // no collisions
    box.setX(0);
    box.setY(0);
    box.setW(-1);
    box.setH(-1);

    wasUsable = usable;

    // init map with motif and collisions
    if (usable) {
        displayOnMap();
    }

}

Interrupteur::~Interrupteur() {
}

void Interrupteur::loop() {
    if ((used && map->getId() != 15) || !usable) {
        return;
    }
    if (map->getId() == 15 && !used && x == 95*16 && y == 27*16 && map->getSol(84*16, 17*16) != 1817) {
        used = true;
        map->setSol(x, y, 2177, PIERRE);
        return;
    }

    BoundingBox bb(x + 4, y + 4, 8, 8);
    Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();

    if (map->getId() == 15 && used && x == 95*16 && y == 27*16) {
        if (map->checkCollisions(&bb, this, false, false, false, false, true)
            && !bb.intersect(link->getBoundingBox())) {
            if (map->desactivateInter(x, y)) {
                used = false;
                map->setSol(x, y, 2176, PIERRE);
            }
        }
    } else if (!used && usable && (!map->checkCollisions(&bb, this, false, false, false, false, true)
        || bb.intersect(link->getBoundingBox()))) {
        if (type != 2) used = true; else usedTmp = true;
        map->activateInter(x, y);
        map->setSol(x, y, 2177, PIERRE);
    }
}

void Interrupteur::draw(int offsetX, int offsetY) {
}

bool Interrupteur::isResetable() {
    return !wasUsable;
}

void Interrupteur::reset() {
    usable = wasUsable;
}

void Interrupteur::displayOnMap() {
    usable = true;
    map->setSol(x, y, used ? 2177 : 2176, PIERRE);
}
