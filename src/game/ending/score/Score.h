/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SCORE_H__
#define __SCORE_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"

#include "../../keys/Action.h"

class Score {
    public :
        Score();
        ~Score();

        void init();

        void handleActions(Action* action);
        void draw();

    private :

        Text* texts[12];

        WImage* fond;
};

#endif  // Score.h
