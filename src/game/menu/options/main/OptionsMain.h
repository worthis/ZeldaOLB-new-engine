/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSMAIN_H__
#define __OPTIONSMAIN_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"
#include "../../../../engine/resources/WImage.h"
#include "../../../../engine/texts/Text.h"

class OptionsMain {
    public :
        OptionsMain();
        ~OptionsMain();

        void init();

        void handleEvents(Event* event);
        void draw();

    private :

        void drawPage();
        void drawTitle();

        void drawCadre(int x, int y, int w, int h);

        int line;

        Text* texts[5];

        WImage* image;
        WImage* link;
        int skin;
};

#endif  // OptionsMain.h
