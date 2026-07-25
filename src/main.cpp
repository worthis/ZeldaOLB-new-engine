/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "engine/window/WindowManager.h"
#include "engine/audio/AudioManager.h"

#include "config/ConfigurationManager.h"

#include "game/MainController.h"

// --- FIX для Nintendo Switch: предотвращение конфликта имен Event ---
#ifdef __SWITCH__
    #define Event libnx_Event
    #include <switch.h>
    #undef Event
#endif
// --------------------------------------------------------------------

int main(int argc, char **argv)
{
    if (argc && argv)
        ; // pour �viter un warning.....

    #ifdef __SWITCH__
        // Инициализация RomFS для чтения файлов из папки data
        romfsInit();
    #endif

    std::srand(std::time(NULL));

    WindowManager *windowManager = WindowManager::getInstance();
    if (windowManager->init() < 0)
    {
        exit(-1);
    }

    ConfigurationManager *configurationManager = ConfigurationManager::getInstance();
    configurationManager->init("config/system.dat", "config/keys.dat", "config/joystick.dat");

    if (windowManager->createWindow("Oni Link Begins", "data/images/logos/graal.ico", configurationManager->isFull()) < 0)
    {
        exit(-1);
    }

    configurationManager->initTexts();

    MainController *controller = MainController::getInstance();

    controller->init();

    controller->setInternalStep(LOGO);

    Event *event;

    while (windowManager->isOpened())
    {
        event = windowManager->getEvent();
        controller->control(event);
        configurationManager->save();

        if (event->isPushed(QUIT) || event->isPushed(kEscape) || event->isPushed(QUIT_FORCED))
        {
            windowManager->close();
            continue;
        }

        windowManager->display();
    }

    controller->close();

    configurationManager->setFull(windowManager->isFullScreen());
    configurationManager->save();
    configurationManager->close();
    AudioManager::getInstance()->close();

    windowManager->exit();

#ifdef __SWITCH__
    romfsExit();
#endif

    return 0;
}
