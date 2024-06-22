/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"

#include "../../keys/Action.h"

class Credits
{
public:
    Credits();
    ~Credits();

    void init();

    void handleActions(Action *action);
    void loop();
    void draw();

private:
    bool over;
    int step;
    int anim;

    Text *texts[19];
    WImage *images[7];
};

#endif // Credits.h
