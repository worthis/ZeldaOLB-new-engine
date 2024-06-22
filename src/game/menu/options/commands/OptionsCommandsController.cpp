#include "OptionsCommandsController.h"

OptionsCommandsController::OptionsCommandsController() {
}

OptionsCommandsController::~OptionsCommandsController() {
}

void OptionsCommandsController::launch() {
    setInternalStep(COMMANDS_MAIN);
}

void OptionsCommandsController::handleEvents(Event* event) {
    if (transition.isRunning()) {
        return;
    }
    switch(step) {
        case COMMANDS_MAIN : main.handleEvents(event); break;
        case COMMANDS_KEYBOARD : keyboard.handleEvents(event); break;
        case COMMANDS_JOYSTICK : joystick.handleEvents(event); break;
        default : break;
    }
}

void OptionsCommandsController::loop() {
    if (transition.isRunning()) {
        return;
    }
    switch(step) {
        case COMMANDS_MAIN : break;
        case COMMANDS_KEYBOARD : break;
        case COMMANDS_JOYSTICK : break;
        default : break;
    }
}

void OptionsCommandsController::draw() {
    switch(step) {
        case COMMANDS_MAIN : main.draw(); break;
        case COMMANDS_KEYBOARD : keyboard.draw(); break;
        case COMMANDS_JOYSTICK : joystick.draw(); break;
        default : break;
    }

    if (transition.isRunning()) {
        transition.loop();
        transition.draw();

        if (transition.isWaiting()) {
            setInternalStep(nextStep);
            transition.restart();
        } else if (transition.isAchieved()) {
            transition.reset();
        }
    }
}

void OptionsCommandsController::setStep(CommandsStep newStep) {
    nextStep = newStep;
    transition.start();
}

void OptionsCommandsController::setInternalStep(CommandsStep newStep) {
    step = newStep;
    switch(step) {
        case COMMANDS_MAIN : main.launch(); break;
        case COMMANDS_KEYBOARD : keyboard.launch(); break;
        case COMMANDS_JOYSTICK : joystick.launch(); break;
        default : break;
    }
}
