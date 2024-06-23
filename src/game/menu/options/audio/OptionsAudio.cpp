#include "OptionsAudio.h"

#include "../../../MainController.h"
#include "../../../../engine/window/WindowManager.h"
#include "../../../../engine/resources/ResourceManager.h"
#include "../../../../engine/audio/AudioManager.h"
#include "../../../../engine/texts/TextManager.h"
#include "../../../../config/ConfigurationManager.h"

OptionsAudio::OptionsAudio() : line(2), skin(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    niveau = ResourceManager::getInstance()->loadImage("data/images/menus/niveau.png", true);
    for (int i = 0; i < 4; i++)
    {
        texts[i] = 0;
    }
}

OptionsAudio::~OptionsAudio()
{
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    ResourceManager::getInstance()->free(niveau);
    for (int i = 0; i < 4; i++)
    {
        delete texts[i];
    }
}

void OptionsAudio::init()
{
    for (int i = 0; i < 4; i++)
    {
        delete texts[i];
    }
    texts[0] = TextManager::getInstance()->getText(12);
    texts[1] = TextManager::getInstance()->getText(21);
    texts[2] = TextManager::getInstance()->getText(22);
    texts[3] = TextManager::getInstance()->getText(13);

    skin = ConfigurationManager::getInstance()->getSkin();
    volume = ConfigurationManager::getInstance()->getVolume();
    volson = ConfigurationManager::getInstance()->getVolson();
}

void OptionsAudio::handleEvents(Event *event)
{

    if ((event->isPushed(kReturn) || event->isPushed(kSpace)) && line == 2)
    {
        MainController::getInstance()->getMenuController()->getOptionsController()->setStep(OPTIONS_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    if (event->isPushed(KeyBinder::getInstance()->getKey(BT_ACTION)))
    {
        MainController::getInstance()->getMenuController()->getOptionsController()->setStep(OPTIONS_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    if (event->isPushed(kUp))
    {
        line--;
        if (line < 0)
            line = 2;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kDown))
    {
        line++;
        if (line > 2)
            line = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kLeft))
    {
        if (line == 0 && volume > 0)
        {
            volume -= 16;
            ConfigurationManager::getInstance()->setVolume(volume);
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
        if (line == 1 && volson > 0)
        {
            volson -= 16;
            ConfigurationManager::getInstance()->setVolson(volson);
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
    }
    if (event->isPushed(kRight))
    {
        if (line == 0 && volume < 128)
        {
            volume += 16;
            ConfigurationManager::getInstance()->setVolume(volume);
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
        if (line == 1 && volson < 128)
        {
            volson += 16;
            ConfigurationManager::getInstance()->setVolson(volson);
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
    }
}

void OptionsAudio::draw()
{
    drawPage();
    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21, 26, 53 + 16 + 64 * line);

    WindowManager::getInstance()->draw(niveau, 0, 0, 8, 16, 136 + volume, 72);
    WindowManager::getInstance()->draw(niveau, 0, 0, 8, 16, 136 + volson, 136);
}

void OptionsAudio::drawPage()
{

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    drawTitle();

    drawCadre(16, 48 + 16, 288, 32);
    drawCadre(16, 144 - 16, 288, 32);
    drawCadre(16, 192, 136, 32);

    texts[1]->display(44, 56 + 16);

    texts[2]->display(44, 104 + 32);

    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[3]->getLength() * letterSize;
    texts[3]->display(16 + (136 - size) / 2, 200);

    WindowManager::getInstance()->draw(image, 0, 96, 16, 16, 128, 72);
    for (int i = 144; i < 264; i += 16)
    {
        WindowManager::getInstance()->draw(image, 16, 96, 16, 16, i, 72);
    }
    WindowManager::getInstance()->draw(image, 32, 96, 16, 16, 264, 72);

    WindowManager::getInstance()->draw(image, 0, 96, 16, 16, 128, 136);
    for (int i = 144; i < 264; i += 16)
    {
        WindowManager::getInstance()->draw(image, 16, 96, 16, 16, i, 136);
    }
    WindowManager::getInstance()->draw(image, 32, 96, 16, 16, 264, 136);
}

void OptionsAudio::drawTitle()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[0]->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++)
    {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    texts[0]->display(32 + 8 + ((blocs * 16) - size) / 2, 16);
}

void OptionsAudio::drawCadre(int x, int y, int w, int h)
{

    // center
    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        for (int i = x + 16; i < x + w - 16; i += 16)
        {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    // top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    // left and right
    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    // top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    // top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    // bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    // bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);
}
