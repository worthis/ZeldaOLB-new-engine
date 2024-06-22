#include "OptionsAudioController.h"

OptionsAudioController::OptionsAudioController()
{
}

OptionsAudioController::~OptionsAudioController()
{
}

void OptionsAudioController::launch()
{
    audio.init();
}

void OptionsAudioController::handleEvents(Event *event)
{
    audio.handleEvents(event);
}

void OptionsAudioController::draw()
{
    audio.draw();
}
