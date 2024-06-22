/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SCORECONTROLLER_H__
#define __SCORECONTROLLER_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "Score.h"

class ScoreController {
    public :
        ScoreController();
        ~ScoreController();

        void launch();

        void handleActions(Action* action);
        void loop();
        void draw();

    private :
        Score score;
};

#endif  // ScoreController.h
