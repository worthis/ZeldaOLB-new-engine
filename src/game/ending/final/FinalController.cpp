#include "FinalController.h"

FinalController::FinalController()
{
}

FinalController::~FinalController()
{
}

void FinalController::launch()
{
    final.init();
}

void FinalController::handleActions(Action *action)
{
    final.handleActions(action);
}

void FinalController::loop()
{
    final.loop();
}

void FinalController::draw()
{
    final.draw();
}
