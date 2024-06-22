/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MENU_H__
#define __MENU_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/util/time/Metronome.h"
#include "../../../engine/texts/Text.h"

#include "../../content/CommonGame.h"

#include "../../keys/Action.h"

#include "../../content/link/Link.h"

enum GameMenuStep {MENU_START, MENU_ON, MENU_END, MENU_OFF};

class Menu {
    public :
        Menu();
        ~Menu();

        void init();

        void handleActions(Action* action);
        void loop();
        void draw();

        void start();
        void stop();

        Equipment getSelectedStuff();

    private :

        void drawObjects(int df);

        void drawHearts(int df);

        void drawLink(int df);

        void drawGraals(int df);

        void drawStatus(int df);

        void drawCadre(int x, int y, int w, int h);

        void drawNombre(int val, int x, int y, int nb, bool green);

        void initFromSelectedStuff();

        void updateSelectedStuff();

        int i;
        int j;

        GameMenuStep step;
        int anim;

        WImage* imageMenu;
        WImage* imageCoeur;
        WImage* imageChiffres;
        WImage* imageStuff;
        WImage* imageStatus;

        Metronome* metronome;

        Link* link;

        Text* texts[13];

        bool magie;
        bool oniLink;
        bool oniLinkable;
};

#endif  // Menu.h
