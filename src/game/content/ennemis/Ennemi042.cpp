#include "Ennemi042.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi042::Ennemi042(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi42.png", true);
    chrono.reset();

    type = 42;

    x = i;
    y = j;

    // for quadtree operations:
    width = 26;
    height = 19;

    box.setX(x+5);
    box.setY(y+3);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 3;
    maxLife = 3;
    recul = 32;
    vitesseRecul = 4;

    items.addType(TI_MAGIE_PEU, 40);
    items.addType(TI_MAGIE_BEAUCOUP, 20);

    forceEnn = 10;
}

Ennemi042::~Ennemi042() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi042::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi042::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox())) {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_GLACE);
        }
    } else {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi042::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

int Ennemi042::getX() {
    return x;
}

int Ennemi042::getY() {
    return y;
}

BoundingBox* Ennemi042::getBoundingBox() {
    box.setX(x + 5);
    box.setY(y + 3);
    return &box;
}

bool Ennemi042::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return effect == TE_FEU;
}
