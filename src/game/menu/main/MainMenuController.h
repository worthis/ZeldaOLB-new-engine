/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MAINMENUCONTROLLER_H__
#define __MAINMENUCONTROLLER_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "MainMenu.h"

class MainMenuController {
    public :
        MainMenuController();
        ~MainMenuController();

        void launch();

        void handleEvents(Event* event);
        void draw();

    private :

        MainMenu menu;
};

#endif  // MainMenuController.h
