#include "CommandsJoystickController.h"

CommandsJoystickController::CommandsJoystickController()
{
}

CommandsJoystickController::~CommandsJoystickController()
{
}

void CommandsJoystickController::launch()
{
    menu.init();
}

void CommandsJoystickController::handleEvents(Event *event)
{
    menu.handleEvents(event);
}

void CommandsJoystickController::draw()
{
    menu.draw();
}
