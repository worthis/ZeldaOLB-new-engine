#include "OpeningController.h"

#include "../keys/KeyBinder.h"

OpeningController::OpeningController()
{
}

OpeningController::~OpeningController()
{
}

void OpeningController::launch()
{
    opening.init();
    text.init();
}

void OpeningController::handleEvents(Event *event)
{
    Action *action = KeyBinder::getInstance()->getActionForGame(event);
    text.handleActions(action);
}

void OpeningController::loop()
{
    opening.loop();
    text.loop();
}

void OpeningController::draw()
{
    opening.draw();
    text.draw();
}

void OpeningController::nextStep()
{
    opening.nextStep();
}
