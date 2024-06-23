#include "Title.h"

#include "../MainController.h"
#include "../../engine/window/WindowManager.h"
#include "../../engine/resources/ResourceManager.h"
#include "../../engine/audio/AudioManager.h"
#include "../../engine/texts/TextManager.h"

Title::Title() : anim(0), animMax(3), vanim(256), text(0), textSize(0), ready(false), alpha(0), wait(0)
{
    metronomeText = new Metronome(2, 1000);
    ostringstream os;
    for (int i = 0; i < 4; i++)
    {
        os << (i + 1);
        string filename = "data/images/title/fond" + os.str() + ".png";
        images[i] = ResourceManager::getInstance()->loadImage(filename);
        os.str("");
    }

    logo = ResourceManager::getInstance()->loadImage("data/images/title/titre.png", true);
}

Title::~Title()
{
    delete metronomeText;
    for (int i = 0; i < 4; i++)
    {
        ResourceManager::getInstance()->free(images[i]);
    }
    ResourceManager::getInstance()->free(logo);
    delete text;
}

void Title::init()
{
    AudioManager::getInstance()->playMusic(0);
    text = TextManager::getInstance()->getText(0);
    textSize = text->getLength() * TextManager::getInstance()->getWSpace();
    anim = 0;
    chrono.reset();
    ready = false;
    alpha = 0;
    logo->setAlpha(alpha);
}

void Title::handleEvents(Event *event)
{
    if (event->isPushed(kReturn) || event->isPushed(kSpace))
    {
        if (ready)
        {
            AudioManager::getInstance()->playSound(TS_MENU1);
            AudioManager::getInstance()->stopMusic();
            MainController::getInstance()->setStep(MENU);
        }
        else
        {
            alpha = 255;
            logo->setAlpha(alpha);
            ready = true;
            metronomeText->reset();
        }
    }
}

void Title::loop()
{
    metronomeText->loop();
    if (alpha < 255 && alpha > 0)
    {
        alpha += 2;
        if (alpha > 255)
            alpha = 255;
        logo->setAlpha(alpha);
        if (alpha == 255)
        {
            ready = true;
            metronomeText->reset();
        }
    }
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (!alpha && anim == 3 && wait == 2)
            alpha = 1;
        if (anim > animMax)
        {
            if (!alpha)
                wait++;
            anim = 0;
        }
        chrono.reset();
    }
}

void Title::draw()
{
    WindowManager::getInstance()->draw(images[anim], 0, 0, 320, 240, 0, 0);
    if (alpha)
        WindowManager::getInstance()->draw(logo, 0, 0, 150, 149, 85, 45);
    if (ready && metronomeText->getValue())
        text->display((320 - textSize) / 2, 200);
}
