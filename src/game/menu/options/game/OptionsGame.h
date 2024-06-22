/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSGAME_H__
#define __OPTIONSGAME_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"
#include "../../../../engine/resources/WImage.h"
#include "../../../../engine/texts/Text.h"

class OptionsGame
{
public:
    OptionsGame();
    ~OptionsGame();

    void init();

    void handleEvents(Event *event);
    void draw();

private:
    void initTexts();

    void drawPage();
    void drawTitle();

    void drawCadre(int x, int y, int w, int h);

    int line;

    Text *texts[9];

    WImage *image;
    WImage *link;
    int skin;
};

#endif // OptionsGame.h
