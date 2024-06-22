#include "CommandsKeyboardController.h"

CommandsKeyboardController::CommandsKeyboardController()
{
}

CommandsKeyboardController::~CommandsKeyboardController()
{
}

void CommandsKeyboardController::launch()
{
    menu.init();
}

void CommandsKeyboardController::handleEvents(Event *event)
{
    menu.handleEvents(event);
}

void CommandsKeyboardController::draw()
{
    menu.draw();
}
