/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __LOGOCONTROLLER_H__
#define __LOGOCONTROLLER_H__

#include "../../engine/common/Common.h"
#include "../../engine/window/Event.h"

#include "Logo.h"

class LogoController {
    public :
        LogoController();
        ~LogoController();

        void launch();

        void handleEvents(Event* event);
        void loop();
        void draw();

    private :

        Logo logo;
};

#endif  // LogoController.h
