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

int main(int argc, char** argv) {
    if (argc && argv); //pour éviter un warning.....

    std::srand(std::time(NULL));

    WindowManager* windowManager = WindowManager::getInstance();
    if (windowManager->init() < 0) {
        exit(-1);
    }

    ConfigurationManager* configurationManager = ConfigurationManager::getInstance();
    configurationManager->init("config/system.dat", "config/keys.dat", "config/joystick.dat");

    if (windowManager->createWindow("Oni Link Begins", "data/images/logos/graal.ico", configurationManager->isFull()) < 0) {
        exit(-1);
    }

    configurationManager->initTexts();

    MainController* controller = MainController::getInstance();

    controller->init();

    controller->setInternalStep(LOGO);

    // TODO: to remove : -----------------------------------------
    //controller->getGameController()->setSave(new Save(0));
    //controller->setInternalStep(GAME);
    //------------------------------------------------------------

    Event* event;

    while(windowManager->isOpened()) {

        event = windowManager->getEvent();

        controller->control(event);

        if (event->isPushed(QUIT) || event->isPushed(kEscape) || event->isPushed(QUIT_FORCED)) {

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

    return 0;
}
