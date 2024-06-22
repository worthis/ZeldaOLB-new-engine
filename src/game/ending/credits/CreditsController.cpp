#include "CreditsController.h"

CreditsController::CreditsController()
{
}

CreditsController::~CreditsController()
{
}

void CreditsController::launch()
{
    credits.init();
}

void CreditsController::handleActions(Action *action)
{
    credits.handleActions(action);
}

void CreditsController::loop()
{
    credits.loop();
}

void CreditsController::draw()
{
    credits.draw();
}
