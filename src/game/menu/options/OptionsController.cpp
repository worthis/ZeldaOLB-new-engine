#include "OptionsController.h"

OptionsController::OptionsController()
{
}

OptionsController::~OptionsController()
{
}

void OptionsController::launch()
{
    setInternalStep(OPTIONS_MAIN);
}

void OptionsController::handleEvents(Event *event)
{
    if (transition.isRunning())
    {
        return;
    }
    switch (step)
    {
    case OPTIONS_MAIN:
        main.handleEvents(event);
        break;
    case OPTIONS_GAME:
        game.handleEvents(event);
        break;
    case OPTIONS_AUDIO:
        audio.handleEvents(event);
        break;
    case OPTIONS_COMMANDS:
        commands.handleEvents(event);
        break;
    default:
        break;
    }
}

void OptionsController::loop()
{
    if (transition.isRunning())
    {
        return;
    }
    switch (step)
    {
    case OPTIONS_MAIN:
        break;
    case OPTIONS_GAME:
        break;
    case OPTIONS_AUDIO:
        break;
    case OPTIONS_COMMANDS:
        commands.loop();
    default:
        break;
    }
}

void OptionsController::draw()
{
    switch (step)
    {
    case OPTIONS_MAIN:
        main.draw();
        break;
    case OPTIONS_GAME:
        game.draw();
        break;
    case OPTIONS_AUDIO:
        audio.draw();
        break;
    case OPTIONS_COMMANDS:
        commands.draw();
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

void OptionsController::setStep(OptionsStep newStep)
{
    nextStep = newStep;
    transition.start();
}

void OptionsController::setInternalStep(OptionsStep newStep)
{
    step = newStep;
    switch (step)
    {
    case OPTIONS_MAIN:
        main.launch();
        break;
    case OPTIONS_GAME:
        game.launch();
        break;
    case OPTIONS_AUDIO:
        audio.launch();
        break;
    case OPTIONS_COMMANDS:
        commands.launch();
        break;
    default:
        break;
    }
}

OptionsCommandsController *OptionsController::getOptionsCommandsController()
{
    return &commands;
}
