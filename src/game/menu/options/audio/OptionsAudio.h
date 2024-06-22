/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSAUDIO_H__
#define __OPTIONSAUDIO_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"
#include "../../../../engine/resources/WImage.h"
#include "../../../../engine/texts/Text.h"

class OptionsAudio {
    public :
        OptionsAudio();
        ~OptionsAudio();

        void init();

        void handleEvents(Event* event);
        void draw();

    private :

        void drawPage();
        void drawTitle();

        void drawCadre(int x, int y, int w, int h);

        int line;

        int volume;
        int volson;

        Text* texts[4];

        WImage* image;
        WImage* link;
        WImage* niveau;
        int skin;
};

#endif  // OptionsAudio.h
