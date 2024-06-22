/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"

#include "../../Save.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    void init();

    void handleEvents(Event *event);
    void draw();

private:
    void drawPage();
    void drawTitle();
    void drawSaves();
    void drawLoad();
    void drawConfirm();

    void drawCadre(int x, int y, int w, int h);

    int line;
    int column;

    bool load;
    bool confirm;

    int subLine;

    Text *texts[12];

    WImage *image;
    WImage *link;
    WImage *status;
    WImage *fairy;
    WImage *stuff;
    WImage *inventaire;

    int skin;

    Save *saves[3];
};

#endif // MainMenu.h
