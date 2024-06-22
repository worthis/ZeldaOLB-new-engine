#include "RecordsController.h"

RecordsController::RecordsController()
{
}

RecordsController::~RecordsController()
{
}

void RecordsController::launch()
{
    menu.init();
}

void RecordsController::handleEvents(Event *event)
{
    menu.handleEvents(event);
}

void RecordsController::draw()
{
    menu.draw();
}
