#include "MonstersController.h"

MonstersController::MonstersController() {
}

MonstersController::~MonstersController() {
}

void MonstersController::launch() {
    monsters.init();
}

void MonstersController::handleActions(Action* action) {
    monsters.handleActions(action);
}

void MonstersController::loop() {
}

void MonstersController::draw() {
    monsters.draw();
}
