/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __COMMANDSJOYSTICKCONTROLLER_H__
#define __COMMANDSJOYSTICKCONTROLLER_H__

#include "../../../../../engine/common/Common.h"
#include "../../../../../engine/window/Event.h"

#include "CommandsJoystick.h"

class CommandsJoystickController {
    public :
        CommandsJoystickController();
        ~CommandsJoystickController();

        void launch();

        void handleEvents(Event* event);
        void draw();

    private :

        CommandsJoystick menu;
};

#endif  // CommandsJoystickController.h
