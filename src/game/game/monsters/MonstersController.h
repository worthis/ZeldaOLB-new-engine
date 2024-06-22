/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MONSTERSCONTROLLER_H__
#define __MONSTERSCONTROLLER_H__

#include "../../../engine/common/Common.h"

#include "Monsters.h"

class MonstersController
{
public:
    MonstersController();
    ~MonstersController();

    void launch();

    void handleActions(Action *action);
    void loop();
    void draw();

private:
    Monsters monsters;
};

#endif // MonstersController.h
