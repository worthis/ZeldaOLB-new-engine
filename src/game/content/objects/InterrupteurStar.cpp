#include "InterrupteurStar.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

InterrupteurStar::InterrupteurStar(int i, int j, bool down, Map* mp, bool us) : used(down), map(mp), usable(us) {
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

InterrupteurStar::~InterrupteurStar() {
}

void InterrupteurStar::loop() {
    if (used || !usable) {
        return;
    }

    BoundingBox bb(x + 4, y + 4, 8, 8);
    Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();

    if (!used && usable && (!map->checkCollisions(&bb, this, false, false, false, false, true) || bb.intersect(link->getBoundingBox()))) {
        map->switchStar();
        map->activateInterStar(x, y);
        map->setSol(x, y, 3174, PIERRE);
    }
}

void InterrupteurStar::draw(int offsetX, int offsetY) {
}

bool InterrupteurStar::isResetable() {
    return !wasUsable;
}

void InterrupteurStar::reset() {
    usable = wasUsable;
}

void InterrupteurStar::displayOnMap() {
    usable = true;
    map->setSol(x, y, used ? 3174 : 3175, PIERRE);
}

void InterrupteurStar::switchMode() {
    used = !used;
    if (usable) {
        displayOnMap();
    }
}
