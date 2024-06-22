#include "EndingController.h"

#include "../keys/KeyBinder.h"

EndingController::EndingController()
{
}

EndingController::~EndingController()
{
}

void EndingController::launch()
{
    setInternalStep(END_STORY);
}

void EndingController::handleEvents(Event *event)
{
    if (transition.isRunning())
    {
        return;
    }
    Action *action = KeyBinder::getInstance()->getActionForGame(event);
    switch (step)
    {
    case END_STORY:
        story.handleActions(action);
        break;
    case END_SCORE:
        score.handleActions(action);
        break;
    case END_CREDITS:
        credits.handleActions(action);
        break;
    case END_END:
        final.handleActions(action);
        break;
    default:
        break;
    }
    // Escape should not end the game
    if (event->isPushed(kEscape))
    {
        event->setEvent(kEscape, false);
    }
}

void EndingController::loop()
{
    if (transition.isRunning())
    {
        return;
    }
    switch (step)
    {
    case END_STORY:
        story.loop();
        break;
    case END_SCORE:
        score.loop();
        break;
    case END_CREDITS:
        credits.loop();
        break;
    case END_END:
        final.loop();
        break;
    default:
        break;
    }
}

void EndingController::draw()
{
    switch (step)
    {
    case END_STORY:
        story.draw();
        break;
    case END_SCORE:
        score.draw();
        break;
    case END_CREDITS:
        credits.draw();
        break;
    case END_END:
        final.draw();
        break;
    default:
        break;
    }

    if (transition.isRunning())
    {
        transition.loop();
        transition.draw();

        if (transition.isWaiting())
        {
            setInternalStep(nextStep);
            transition.restart();
        }
        else if (transition.isAchieved())
        {
            transition.reset();
        }
    }
}

void EndingController::setStep(EndingStep newStep)
{
    nextStep = newStep;
    transition.start();
}

void EndingController::setInternalStep(EndingStep newStep)
{
    step = newStep;
    switch (step)
    {
    case END_STORY:
        story.launch();
        break;
    case END_SCORE:
        score.launch();
        break;
    case END_CREDITS:
        credits.launch();
        break;
    case END_END:
        final.launch();
        break;
    default:
        break;
    }
}
