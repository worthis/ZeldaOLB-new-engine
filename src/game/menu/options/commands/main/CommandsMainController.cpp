#include "CommandsMainController.h"

CommandsMainController::CommandsMainController() {
}

CommandsMainController::~CommandsMainController() {
}

void CommandsMainController::launch() {
    menu.init();
}

void CommandsMainController::handleEvents(Event* event) {
    menu.handleEvents(event);
}

void CommandsMainController::draw() {
    menu.draw();
}
