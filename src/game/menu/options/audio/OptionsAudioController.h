/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __OPTIONSAUDIOCONTROLLER_H__
#define __OPTIONSAUDIOCONTROLLER_H__

#include "../../../../engine/common/Common.h"
#include "../../../../engine/window/Event.h"

#include "OptionsAudio.h"

class OptionsAudioController {
    public :
        OptionsAudioController();
        ~OptionsAudioController();

        void launch();

        void handleEvents(Event* event);
        void draw();

    private :

        OptionsAudio audio;
};

#endif  // OptionsAudioController.h
