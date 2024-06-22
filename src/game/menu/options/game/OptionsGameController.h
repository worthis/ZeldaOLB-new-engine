/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSGAMECONTROLLER_H__
#define __OPTIONSGAMECONTROLLER_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"

#include "OptionsGame.h"

class OptionsGameController {
    public :
        OptionsGameController();
        ~OptionsGameController();

        void launch();

        void handleEvents(Event* event);
        void draw();

    private :

        OptionsGame menu;
};

#endif  // OptionsGameController.h
