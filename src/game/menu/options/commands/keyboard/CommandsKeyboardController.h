/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __COMMANDSKEYBOARDCONTROLLER_H__
#define __COMMANDSKEYBOARDCONTROLLER_H__

#include "../../../../../engine/common/Common.h"
#include "../../../../../engine/window/Event.h"

#include "CommandsKeyboard.h"

class CommandsKeyboardController {
    public :
        CommandsKeyboardController();
        ~CommandsKeyboardController();

        void launch();

        void handleEvents(Event* event);
        void draw();

    private :

        CommandsKeyboard menu;
};

#endif  // CommandsKeyboardController.h
