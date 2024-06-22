/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __COMMANDSMAIN_H__
#define __COMMANDSMAIN_H__

#include "../../../../../engine/common/Common.h"
#include "../../../../../engine/window/Event.h"
#include "../../../../../engine/resources/WImage.h"
#include "../../../../../engine/texts/Text.h"

class CommandsMain
{
public:
    CommandsMain();
    ~CommandsMain();

    void init();

    void handleEvents(Event *event);
    void draw();

private:
    void drawPage();
    void drawTitle();
    void drawWarning();

    void drawCadre(int x, int y, int w, int h);

    int line;
    bool warning;

    Text *texts[8];

    WImage *image;
    WImage *link;
    int skin;
};

#endif // CommandsMain.h
