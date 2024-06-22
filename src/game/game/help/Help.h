/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __HELP_H__
#define __HELP_H__

#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"
#include "../../keys/Action.h"

class Help
{
public:
    Help();
    ~Help();

    void init();

    void handleActions(Action *action);
    void draw();

private:
    void cadre(int x, int y, int w, int h);

    int page;

    WImage *image;

    Text *texts[26];
};

#endif // Help.h
