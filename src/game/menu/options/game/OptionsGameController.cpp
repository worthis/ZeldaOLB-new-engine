#include "OptionsGameController.h"

OptionsGameController::OptionsGameController() {
}

OptionsGameController::~OptionsGameController() {
}

void OptionsGameController::launch() {
    menu.init();
}

void OptionsGameController::handleEvents(Event* event) {
    menu.handleEvents(event);
}

void OptionsGameController::draw() {
    menu.draw();
}
