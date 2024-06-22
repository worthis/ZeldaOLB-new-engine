/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSMAINCONTROLLER_H__
#define __OPTIONSMAINCONTROLLER_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"

#include "OptionsMain.h"

class OptionsMainController {
    public :
        OptionsMainController();
        ~OptionsMainController();

        void launch();

        void handleEvents(Event* event);
        void draw();

    private :

        OptionsMain menu;
};

#endif  // OptionsMainController.h
