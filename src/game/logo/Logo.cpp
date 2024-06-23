#include "Logo.h"

#include "../MainController.h"
#include "../../engine/window/WindowManager.h"
#include "../../engine/resources/ResourceManager.h"
#include "../../engine/audio/AudioManager.h"

#include "../../config/ConfigurationManager.h"

Logo::Logo() : anim(0), animMax(15), vanim(60), first(true)
{
    lastLang = ConfigurationManager::getInstance()->getLang();

    loadLogoFond();
    imageLogo = ResourceManager::getInstance()->loadImage("data/images/logos/logo.png");
}

Logo::~Logo()
{
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(imageLogo);
}

void Logo::init()
{
    int currentLang = ConfigurationManager::getInstance()->getLang();
    if (lastLang != currentLang)
    {
        lastLang = currentLang;

        ResourceManager::getInstance()->free(image);

        loadLogoFond();
    }

    anim = 0;
    chrono.reset();
}

void Logo::handleEvents(Event *event)
{
    if (anim < animMax)
        return;
    if (event->isPushed(kReturn) || event->isPushed(kSpace))
    {
        AudioManager::getInstance()->playSound(TS_MENU1);
        MainController::getInstance()->setStep(TITRE);
    }
}

void Logo::loop()
{
    if (anim == animMax)
        return;
    if (first)
    {
        if (chrono.getElapsedTime() >= 500)
        {
            first = false;
            chrono.reset();
        }
        return;
    }
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        chrono.reset();
    }
}

void Logo::draw()
{
    if (first)
        return;
    WindowManager::getInstance()->draw(image, 0, 0, 320, 240, 0, 0);

    WindowManager::getInstance()->draw(imageLogo, 144 * (anim % 4), 144 * (anim / 4), 144, 144, 88, 60);
}

void Logo::loadLogoFond()
{
    if (ConfigurationManager::getInstance()->isFrench())
    {
        image = ResourceManager::getInstance()->loadImage("data/images/logos/logo_fond.png");
        return;
    }

    if (ConfigurationManager::getInstance()->isRussian())
    {
        image = ResourceManager::getInstance()->loadImage("data/images/logos/logo_fond_ru.png");
        return;
    }

    image = ResourceManager::getInstance()->loadImage("data/images/logos/logo_fond_us.png");
}
