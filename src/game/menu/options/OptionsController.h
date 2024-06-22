/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSCONTROLLER_H__
#define __OPTIONSCONTROLLER_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "../../../engine/renderer/SimpleTransition.h"

#include "main/OptionsMainController.h"
#include "game/OptionsGameController.h"
#include "audio/OptionsAudioController.h"
#include "commands/OptionsCommandsController.h"

enum OptionsStep {OPTIONS_MAIN, OPTIONS_GAME, OPTIONS_AUDIO, OPTIONS_COMMANDS};

class OptionsController {
    public :
        OptionsController();
        ~OptionsController();

        void launch();

        void handleEvents(Event* event);
        void loop();
        void draw();

        void setStep(OptionsStep newStep);

        void setInternalStep(OptionsStep newStep); // set step without transition

        OptionsCommandsController* getOptionsCommandsController();

    private :

        OptionsStep step;
        OptionsStep nextStep;

        SimpleTransition transition;

        OptionsMainController main;
        OptionsGameController game;
        OptionsAudioController audio;
        OptionsCommandsController commands;
};

#endif  // OptionsController.h

