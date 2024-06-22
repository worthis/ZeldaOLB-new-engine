#include "MapOcarina.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

#include "../../../config/ConfigurationManager.h"

MapOcarina::MapOcarina() : started(false), teleport(false), position(0), offsetSkin(0)
{
    imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/overworld.png");
    imageLink = ResourceManager::getInstance()->loadImage("data/images/maps/link.png", true);
}

MapOcarina::~MapOcarina()
{
    ResourceManager::getInstance()->free(imageMap);
    ResourceManager::getInstance()->free(imageLink);
}

void MapOcarina::handleActions(Action *action)
{
    if (teleport || !started)
        return;
    if (action->isAction(ACTION))
    {
        AudioManager::getInstance()->playSound(TS_TELEPORT, 2);
        teleport = true;
        return;
    }
    if (action->isAction(QUIT_GAME))
    {
        started = false;
        MainController::getInstance()->getGameController()->hideMap();
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    int old = position;
    if (action->isAction(MAP_1))
        position = 0;
    if (action->isAction(MAP_2))
        position = 1;
    if (action->isAction(MAP_3))
        position = 2;
    if (action->isAction(MAP_4))
        position = 3;
    if (action->isAction(MAP_5))
        position = 4;
    if (action->isAction(MAP_6))
        position = 5;
    if (action->isAction(MAP_7))
        position = 6;
    if (action->isAction(MAP_8))
        position = 7;
    if (action->isAction(MAP_9))
        position = 8;

    if (action->isAction(PUSH_UP) || action->isAction(PUSH_LEFT))
    {
        if (--position < 0)
            position = 8;
    }
    if (action->isAction(PUSH_DOWN) || action->isAction(PUSH_RIGHT))
    {
        if (++position > 8)
            position = 0;
    }

    if (old != position)
    {
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void MapOcarina::loop()
{
    if (!started)
        return;
    if (teleport && !AudioManager::getInstance()->isPlaying(2))
    {
        MainController::getInstance()->getGameController()->hideMap();

        switch (position)
        {
        case 0:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 13 * 16 + 8, 32 * 16, S, true, true);
            break;
        case 1:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 21 * 16 + 8, 14 * 16, S, true, true);
            break;
        case 2:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 25 * 16 + 8, 70 * 16, S, true, true);
            break;
        case 3:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 41 * 16 + 8, 38 * 16, S, true, true);
            break;
        case 4:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 39 * 16, 42 * 16, S, true, true);
            break;
        case 5:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 39 * 16, 55 * 16, S, true, true);
            break;
        case 6:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 65 * 16, 44 * 16, S, true, true);
            break;
        case 7:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(10, 24 * 16 + 8, 44 * 16, S, true, true);
            break;
        case 8:
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 41 * 16 + 8, 13 * 16, S, true, true);
            break;
        default:
            return;
        }
        MainController::getInstance()->getGameController()->getTeleportController()->loop();
        int i = position;
        MainController::getInstance()->getGameController()->setStep(GAME_MAP);
        position = i;
        started = false;
        teleport = false;
    }
}

void MapOcarina::draw()
{
    WindowManager::getInstance()->draw(imageMap, 0, 0, 320, 240, 0, 0);

    if (position == 0)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 12 - 7, 29 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('1', 12 - 4, 29 - 10, 0);
    }

    if (position == 1)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 161 - 7, 13 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('2', 161 - 4, 13 - 10, 0);
    }

    if (position == 2)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 165 - 7, 63 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('3', 165 - 4, 63 - 10, 0);
    }

    if (position == 3)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 37 - 7, 115 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('4', 37 - 4, 115 - 10, 0);
    }

    if (position == 4)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 177 - 7, 172 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('5', 177 - 4, 172 - 10, 0);
    }

    if (position == 5)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 284 - 7, 130 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('6', 284 - 4, 130 - 10, 0);
    }

    if (position == 6)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 58 - 7, 227 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('7', 58 - 4, 227 - 10, 0);
    }

    if (position == 7)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 93 - 7, 227 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('8', 93 - 4, 227 - 10, 0);
    }

    if (position == 8)
    {
        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 286 - 7, 199 - 8);
    }
    else
    {
        TextManager::getInstance()->drawLetter('9', 286 - 4, 199 - 10, 0);
    }
}

void MapOcarina::launch()
{
    offsetSkin = ConfigurationManager::getInstance()->getSkin() * 15;
    position = 0;
    started = true;
    teleport = false;
}
