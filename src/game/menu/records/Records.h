/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __RECORDS_H__
#define __RECORDS_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"

class Records {
    public :
        Records();
        ~Records();

        void init();

        void handleEvents(Event* event);
        void draw();

    private :

        void drawPage();
        void drawTitle();
        void drawFull();
        void drawUltime();
        void drawRush();
        void drawConfirm();

        void drawCadre(int x, int y, int w, int h);

        bool fullROTH;
        bool rushROTH;
        bool ultimeROTH;
        bool fullOLB;
        bool rushOLB;
        bool ultimeOLB;

        int line;
        int column;

        bool helpFull;
        bool helpRush;
        bool helpUltime;
        bool confirm;

        int subLine;

        Text* texts[23];

        WImage* image;
        WImage* link;
        WImage* fairy;
        WImage* rangs;
        int skin;
};

#endif  // Records.h
