/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSCOMMANDSCONTROLLER_H__
#define __OPTIONSCOMMANDSCONTROLLER_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"

#include "../../../../engine/renderer/SimpleTransition.h"

#include "main/CommandsMainController.h"
#include "keyboard/CommandsKeyboardController.h"
#include "joystick/CommandsJoystickController.h"

enum CommandsStep {COMMANDS_MAIN, COMMANDS_KEYBOARD, COMMANDS_JOYSTICK};

class OptionsCommandsController {
    public :
        OptionsCommandsController();
        ~OptionsCommandsController();

        void launch();

        void handleEvents(Event* event);
        void loop();
        void draw();

        void setStep(CommandsStep newStep);

        void setInternalStep(CommandsStep newStep); // set step without transition

    private :

        CommandsStep step;
        CommandsStep nextStep;

        SimpleTransition transition;

        CommandsMainController main;
        CommandsKeyboardController keyboard;
        CommandsJoystickController joystick;
};

#endif  // OptionsCommandsController.h

