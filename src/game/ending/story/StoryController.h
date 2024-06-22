/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __STORYCONTROLLER_H__
#define __STORYCONTROLLER_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "StoryTextArea.h"

class StoryController
{
public:
    StoryController();
    ~StoryController();

    void launch();

    void handleActions(Action *action);
    void loop();
    void draw();

private:
    StoryTextArea story;
};

#endif // StoryController.h
