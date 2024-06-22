/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __RECORDSCONTROLLER_H__
#define __RECORDSCONTROLLER_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "Records.h"

class RecordsController
{
public:
    RecordsController();
    ~RecordsController();

    void launch();

    void handleEvents(Event *event);
    void draw();

private:
    Records menu;
};

#endif // RecordsController.h
