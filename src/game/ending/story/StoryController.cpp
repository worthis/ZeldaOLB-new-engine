#include "StoryController.h"

StoryController::StoryController()
{
}

StoryController::~StoryController()
{
}

void StoryController::launch()
{
    story.init();
}

void StoryController::handleActions(Action *action)
{
    story.handleActions(action);
}

void StoryController::loop()
{
    story.loop();
}

void StoryController::draw()
{
    story.draw();
}
