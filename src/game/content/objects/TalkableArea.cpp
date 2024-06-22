#include "TalkableArea.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

TalkableArea::TalkableArea(int i, int j, int txt) : texte(txt) {
    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

TalkableArea::~TalkableArea() {
}


void TalkableArea::loop() {}

void TalkableArea::draw(int offsetX, int offsetY) {}

bool TalkableArea::action(Direction dir) {
    MainController::getInstance()->getGameController()->displayText(getDynamicText());
    return true;
}

int TalkableArea::getDynamicText() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    switch (texte) {
        case 456 :
            if (link->getStatus()->getVirtualLife() == link->getStatus()->getMaxLife()) {
                return 458;
            }
            break;
        case 459 : case 461 :
            if (!link->getInventory()->hasObject(LANTERNE) || link->getStatus()->getVirtualMagic() == link->getStatus()->getMaxMagic()) {
                return 458;
            }
            break;
        case 464 :
            if (!link->getInventory()->hasObject(ARC) || link->getStatus()->getArrows() == link->getStatus()->getMaxArrows()) {
                return 458;
            }
            break;
        case 466 :
            if (!link->getInventory()->hasObject(BOMBES)) {
                return 468;
            }
            if (link->getStatus()->getBombs() == link->getStatus()->getMaxBombs()) {
                return 458;
            }
            break;
        case 447 :
            if (scene->getCoffre(0, 15)) {
                return 482;
            }
            break;
        default : break;
    }
    return texte;
}
