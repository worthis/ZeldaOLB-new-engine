/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CREDITSCONTROLLER_H__
#define __CREDITSCONTROLLER_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "Credits.h"

class CreditsController {
    public :
        CreditsController();
        ~CreditsController();

        void launch();

        void handleActions(Action* action);
        void loop();
        void draw();

    private :
        Credits credits;
};

#endif  // CreditsController.h
