#include "Inventory.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Inventory::Inventory(Save* save) {
    loadFromSave(save);
    inventaire = ResourceManager::getInstance()->loadImage("data/images/status/inventaire.png");
}

Inventory::~Inventory() {
    ResourceManager::getInstance()->free(inventaire);
}

void Inventory::saveData(Save* save) {
    for (int i = 0; i < NB_EQPMT; i++) {
        save->setEquipment(i, equipment[i]);
    }
    for (int i = 0; i < NB_FLACON; i++) {
        save->setFlacons(i, flacons[i]);
    }
    for (int i = 0; i < NB_QUART_COEUR; i++) {
        save->setQuartCoeur(i, quartCoeur[i]);
    }
    for (int i = 0; i < NB_COEUR; i++) {
        save->setCoeur(i, coeur[i]);
    }
    for (int i = 0; i < NB_GRAALS; i++) {
        save->setGraals(i, graals[i]);
    }
    save->setCurrentStuff(current);
}

void Inventory::loadFromSave(Save* save) {
    for (int i = 0; i < NB_EQPMT; i++) {
        equipment[i] = save->getEquipment(i);
    }
    for (int i = 0; i < NB_FLACON; i++) {
        flacons[i] = save->getFlacons(i);
    }
    for (int i = 0; i < NB_QUART_COEUR; i++) {
        quartCoeur[i] = save->getQuartCoeur(i);
    }
    for (int i = 0; i < NB_COEUR; i++) {
        coeur[i] = save->getCoeur(i);
    }
    for (int i = 0; i < NB_GRAALS; i++) {
        graals[i] = save->getGraals(i);
    }
    current = save->getCurrentStuff();
}

void Inventory::draw(Equipment e, int x, int y) {
    switch (e) {
        case ARC : WindowManager::getInstance()->draw(inventaire, 16, 68, 16, 17, x, y); break;
        case ARC_FEE : WindowManager::getInstance()->draw(inventaire, 0, 0, 16, 17, x, y); break;
        case BOMBES : WindowManager::getInstance()->draw(inventaire, 32, 0, 16, 17, x, y); break;
        case GRAPPIN : WindowManager::getInstance()->draw(inventaire, 16, 0, 16, 17, x, y); break;
        case BAGUETTE_FEU : WindowManager::getInstance()->draw(inventaire, 0, 17, 16, 17, x, y); break;
        case BAGUETTE_GLACE : WindowManager::getInstance()->draw(inventaire, 16, 17, 16, 17, x, y); break;
        case LANTERNE : WindowManager::getInstance()->draw(inventaire, 32, 17, 16, 17, x, y); break;
        case MARTEAU : WindowManager::getInstance()->draw(inventaire, 0, 34, 16, 17, x, y); break;
        case FLACON_1 : drawFlacon(x, y, flacons[0]); break;
        case FLACON_2 : drawFlacon(x, y, flacons[1]); break;
        case FLACON_3 : drawFlacon(x, y, flacons[2]); break;
        case GANTS : WindowManager::getInstance()->draw(inventaire, 48, 34, 16, 17, x, y); break;
        case GANTS_2 : WindowManager::getInstance()->draw(inventaire, 32, 34, 16, 17, x, y); break;
        case PALMES : WindowManager::getInstance()->draw(inventaire, 16, 34, 16, 17, x, y); break;
        case OCARINA : WindowManager::getInstance()->draw(inventaire, 0, 68, 16, 17, x, y); break;
        case MASQUE : WindowManager::getInstance()->draw(inventaire, 16, 136, 16, 17, x, y); break;
        case MASQUE_VIDE : WindowManager::getInstance()->draw(inventaire, 0, 136, 16, 17, x, y); break;
        case BOTTES : WindowManager::getInstance()->draw(inventaire, 48, 85, 16, 17, x, y); break;
        default : break;
    }
}

void Inventory::drawFlacon(int x, int y, int value) {
    WindowManager::getInstance()->draw(inventaire, (value%4) * 16, 51 + 68 * (value / 4), 16, 17, x, y);
}

void Inventory::setObject(Equipment e, int value) {
    equipment[e] = value;
}

bool Inventory::hasObject(Equipment e) {
    return (equipment[e] == 1);
}

bool Inventory::hasObject() {
    for (int i = 0; i < NB_EQPMT; i++) {
        if (i != CARTE && i != ENCYCLOPEDIE && equipment[i]) return true;
    }
    return false;
}

Equipment Inventory::getCurrent() {
    return current;
}

void Inventory::setCurrent(Equipment e) {
    current = e;
    if (current == ARC && hasObject(ARC_FEE)) {
        current = ARC_FEE;
    }
    if (current == MASQUE_VIDE && hasObject(MASQUE)) {
        current = MASQUE;
    }
}

bool Inventory::hasQuartCoeur(int i) {
    return (quartCoeur[i] == 1);
}

void Inventory::setQuartCoeur(int i, int value) {
    quartCoeur[i] = value;
}

int Inventory::nbQuartCoeur() {
    return totalQuartCoeur() % 4;
}

int Inventory::totalQuartCoeur() {
    int total = 0;
    for (int i = 0; i < NB_QUART_COEUR; i++) {
        if (quartCoeur[i]) total++;
    }
    return total;
}

bool Inventory::hasCoeur(int i) {
    return (coeur[i] == 1);
}

void Inventory::setCoeur(int i, int value) {
    coeur[i] = value;
}

void Inventory::setGraal(int i, int value) {
    graals[i] = value;
}

bool Inventory::hasGraal(int i) {
    return (graals[i] == 1);
}

int Inventory::nbGraals() {
    int total = 0;
    for (int i = 0; i < NB_GRAALS; i++) {
        if (graals[i]) total++;
    }
    return total;
}

int Inventory::getFlacon(int i) {
    return flacons[i];
}

void Inventory::setFlacon(int i, int value) {
    flacons[i] = value;
}

int Inventory::getCurrentFlacon() {
    switch (current) {
        case FLACON_1 : return flacons[0];
        case FLACON_2 : return flacons[1];
        case FLACON_3 : return flacons[2];
        default : return 0;
    }
}

void Inventory::setCurrentFlacon(int value) {
    switch (current) {
        case FLACON_1 : flacons[0] = value; break;
        case FLACON_2 : flacons[1] = value; break;
        case FLACON_3 : flacons[2] = value; break;
        default : break;
    }
}
