/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __FINAL_H__
#define __FINAL_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/util/time/Chrono.h"

#include "../../keys/Action.h"

class Final {
    public :
        Final();
        ~Final();

        void init();

        void handleActions(Action* action);
        void loop();
        void draw();

    private :

        int anim;
        int animMax;
        int vanim;

        Chrono chrono;

        WImage* images[30];
};

#endif  // Final.h
