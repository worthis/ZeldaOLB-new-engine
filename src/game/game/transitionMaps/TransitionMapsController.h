/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRANSITIONMAPSCONTROLLER_H__
#define __TRANSITIONMAPSCONTROLLER_H__

#include "../../../engine/common/Common.h"

#include "TransitionMaps.h"

class TransitionMapsController {
    public :
        TransitionMapsController();
        ~TransitionMapsController();

        void launch();

        void loop();
        void draw();

    private :

        TransitionMaps transitionMaps;
};

#endif  // TransitionMapsController.h
