/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __COMMANDSMAINCONTROLLER_H__
#define __COMMANDSMAINCONTROLLER_H__

#include "../../../../../engine/common/Common.h"
#include "../../../../../engine/window/Event.h"

#include "CommandsMain.h"

class CommandsMainController
{
public:
    CommandsMainController();
    ~CommandsMainController();

    void launch();

    void handleEvents(Event *event);
    void draw();

private:
    CommandsMain menu;
};

#endif // CommandsMainController.h
