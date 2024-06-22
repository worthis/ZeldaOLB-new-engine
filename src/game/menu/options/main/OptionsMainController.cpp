#include "OptionsMainController.h"

OptionsMainController::OptionsMainController() {
}

OptionsMainController::~OptionsMainController() {
}

void OptionsMainController::launch() {
    menu.init();
}

void OptionsMainController::handleEvents(Event* event) {
    menu.handleEvents(event);
}

void OptionsMainController::draw() {
    menu.draw();
}
