/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"
#include "../../keys/Action.h"

#include "../../content/types/Ennemi.h"


class Monsters {
    public :
        Monsters();
        ~Monsters();

        void init();

        void handleActions(Action* action);
        void draw();

    private :

        void initPage();

        void cadre(int x, int y, int w, int h, int type);

        int getNextPageFrom(int page);
        int getPreviousPageFrom(int page);
        bool isPageEmpty(int page);

        int page;

        WImage* image;

        Text* texts[6];
        Ennemi* ennemis[NB_MONSTERS];
};

#endif  // Monsters.h
