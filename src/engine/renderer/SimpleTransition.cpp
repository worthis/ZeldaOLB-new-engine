#include "SimpleTransition.h"

#include "../window/WindowManager.h"

SimpleTransition::SimpleTransition() : texture(0)
{
    reset();
}

SimpleTransition::~SimpleTransition()
{
    SDL_DestroyTexture(texture);
}

void SimpleTransition::init()
{
    if (!texture)
    {
        SDL_Surface *tmp = SDL_CreateRGBSurface(0, GAME_SIZE_W, GAME_SIZE_H, 32, 0, 0, 0, 0);
        texture = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
        SDL_FreeSurface(tmp);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}

void SimpleTransition::loop()
{
    if (step == 1)
    {
        alpha += 15;
        if (alpha == 255)
        {
            step = 2;
        }
        SDL_SetTextureAlphaMod(texture, alpha);
    }
    else if (step == 3)
    {
        alpha -= 15;
        if (alpha == 0)
        {
            step = 4;
        }
        SDL_SetTextureAlphaMod(texture, alpha);
    }
}

void SimpleTransition::draw()
{
    WindowManager::getInstance()->draw(texture);
}

bool SimpleTransition::isRunning()
{
    return run;
}

void SimpleTransition::start()
{
    init();
    run = true;
    step = 1;
}

bool SimpleTransition::isWaiting()
{
    return (step == 2);
}

void SimpleTransition::restart()
{
    step = 3;
    alpha = 255;
}

bool SimpleTransition::isAchieved()
{
    return (step == 4);
}

void SimpleTransition::reset()
{
    run = false;
    step = 0;
    alpha = 0;
}
