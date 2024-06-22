#include "Credits.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/texts/TextManager.h"
#include "../../../engine/audio/AudioManager.h"

Credits::Credits() : over(false), step(0), anim(0)
{
    for (int i = 0; i < 19; i++)
    {
        texts[i] = 0;
    }
    ostringstream os;
    for (int i = 0; i < 7; i++)
    {
        os << (i + 1);
        string filename = "data/images/ending/credits/credits_" + os.str() + ".png";
        images[i] = ResourceManager::getInstance()->loadImage(filename);
        SDL_SetTextureBlendMode(images[i]->getImage(), SDL_BLENDMODE_BLEND);
        os.str("");
    }
}

Credits::~Credits()
{
    for (int i = 0; i < 19; i++)
    {
        delete texts[i];
    }
    for (int i = 0; i < 7; i++)
    {
        ResourceManager::getInstance()->free(images[i]);
    }
}

void Credits::init()
{
    for (int i = 0; i < 19; i++)
    {
        delete texts[i];
        texts[i] = TextManager::getInstance()->getText(559 + i);
    }

    over = false;
    step = 0;
    anim = 0;
}

void Credits::handleActions(Action *action)
{
}

void Credits::loop()
{

    anim++;
    if (step == 10)
    {
        if (anim == 768)
        {
            MainController::getInstance()->getEndingController()->setStep(END_END);
        }
    }
    else if (step == 6)
    {
        if (anim == 900)
        {
            images[(step / 2) + 1]->setAlpha(0);
            anim = 0;
            step++;
        }
    }
    else if (step == 8)
    {
        if (anim == 768)
        {
            images[(step / 2) + 1]->setAlpha(0);
            anim = 0;
            step++;
        }
    }
    else if (step % 2 == 0)
    {
        if (anim == 512)
        {
            images[(step / 2) + 1]->setAlpha(0);
            anim = 0;
            step++;
        }
    }
    else
    {
        images[(step / 2) + 1]->setAlpha(anim);
        if (anim == 255)
        {
            anim = 0;
            step++;
        }
    }
}

void Credits::draw()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = 0;

    switch (step)
    {
    case 0:
        WindowManager::getInstance()->draw(images[0], 0, 0, 320, 240, 0, 0);
        if (anim >= 128)
        {
            size = texts[0]->getLength() * letterSize;
            texts[0]->display(160 - (size / 2), 20);
        }
        if (anim >= 256)
        {
            size = texts[1]->getLength() * letterSize;
            texts[1]->display(160 - (size / 2), 100);
        }
        break;
    case 1:
        WindowManager::getInstance()->draw(images[0], 0, 0, 320, 240, 0, 0);
        WindowManager::getInstance()->draw(images[1], 0, 0, 320, 240, 0, 0);
        break;
    case 2:
        WindowManager::getInstance()->draw(images[1], 0, 0, 320, 240, 0, 0);
        if (anim >= 128)
        {
            size = texts[2]->getLength() * letterSize;
            texts[2]->display(160 - (size / 2), 20);
        }
        if (anim >= 256)
        {
            size = texts[3]->getLength() * letterSize;
            texts[3]->display(160 - (size / 2), 100);
        }
        break;
    case 3:
        WindowManager::getInstance()->draw(images[1], 0, 0, 320, 240, 0, 0);
        WindowManager::getInstance()->draw(images[2], 0, 0, 320, 240, 0, 0);
        break;
    case 4:
        WindowManager::getInstance()->draw(images[2], 0, 0, 320, 240, 0, 0);
        if (anim >= 128)
        {
            size = texts[4]->getLength() * letterSize;
            texts[4]->display(160 - (size / 2), 20);
        }
        if (anim >= 256)
        {
            size = texts[5]->getLength() * letterSize;
            texts[5]->display(160 - (size / 2), 100);
        }
        break;
    case 5:
        WindowManager::getInstance()->draw(images[2], 0, 0, 320, 240, 0, 0);
        WindowManager::getInstance()->draw(images[3], 0, 0, 320, 240, 0, 0);
        break;
    case 6:
        WindowManager::getInstance()->draw(images[3], 0, 0, 320, 240, 0, 0);
        if (anim >= 128)
        {
            size = texts[6]->getLength() * letterSize;
            texts[6]->display(160 - (size / 2), 20);
        }
        if (anim >= 256)
        {
            size = texts[7]->getLength() * letterSize;
            texts[7]->display(160 - (size / 2), 60);
        }
        if (anim >= 384)
        {
            size = texts[8]->getLength() * letterSize;
            texts[8]->display(160 - (size / 2), 120);
        }
        if (anim >= 512)
        {
            size = texts[9]->getLength() * letterSize;
            texts[9]->display(160 - (size / 2), 160);
        }
        if (anim >= 640)
        {
            size = texts[10]->getLength() * letterSize;
            texts[10]->display(160 - (size / 2), 200);
        }
        break;
    case 7:
        WindowManager::getInstance()->draw(images[3], 0, 0, 320, 240, 0, 0);
        WindowManager::getInstance()->draw(images[4], 0, 0, 320, 240, 0, 0);
        break;
    case 8:
        WindowManager::getInstance()->draw(images[4], 0, 0, 320, 240, 0, 0);
        if (anim >= 128)
        {
            size = texts[11]->getLength() * letterSize;
            texts[11]->display(160 - (size / 2), 20);
        }
        if (anim >= 256)
        {
            size = texts[12]->getLength() * letterSize;
            texts[12]->display(160 - (size / 2), 80);
        }
        if (anim >= 384)
        {
            size = texts[13]->getLength() * letterSize;
            texts[13]->display(160 - (size / 2), 120);
        }
        if (anim >= 512)
        {
            size = texts[14]->getLength() * letterSize;
            texts[14]->display(160 - (size / 2), 160);
        }
        break;
    case 9:
        WindowManager::getInstance()->draw(images[4], 0, 0, 320, 240, 0, 0);
        WindowManager::getInstance()->draw(images[5], 0, 0, 320, 240, 0, 0);
        break;
    case 10:
        WindowManager::getInstance()->draw(images[6], 0, 0, 320, 240, 0, 0);
        if (anim >= 128)
        {
            size = texts[15]->getLength() * letterSize;
            texts[15]->display(160 - (size / 2), 20);
        }
        if (anim >= 256)
        {
            size = texts[16]->getLength() * letterSize;
            texts[16]->display(160 - (size / 2), 80);
        }
        if (anim >= 384)
        {
            size = texts[17]->getLength() * letterSize;
            texts[17]->display(160 - (size / 2), 100);
        }
        if (anim >= 512)
        {
            size = texts[18]->getLength() * letterSize;
            texts[18]->display(160 - (size / 2), 120);
        }
        break;
    }
}
