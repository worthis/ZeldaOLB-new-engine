/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __COMMANDSJOYSTICK_H__
#define __COMMANDSJOYSTICK_H__

#include "../../../../../engine/common/Common.h"
#include "../../../../../engine/window/Event.h"
#include "../../../../../engine/resources/WImage.h"
#include "../../../../../engine/texts/Text.h"
#include "../../../../keys/JoystickBinder.h"

class CommandsJoystick {
    public :
        CommandsJoystick();
        ~CommandsJoystick();

        void init();

        void handleEvents(Event* event);
        void draw();

    private :

        void updateSelectedKey(Keys key);
        BindableType getBindableTypeForLineAndPage(int l, int p);
        BindableType getBindableTypeForId(int i);
        void reloadTextsForKeys();

        void drawPage();
        void drawTitle();
        void drawConfirm();

        void drawCadre(int x, int y, int w, int h);

        int line;
        int column;
        int page;
        bool edit;
        bool confirm;
        int subline;

        Text* texts[26];

        WImage* image;
        WImage* link;
        WImage* fairy;
        int skin;
};

#endif  // CommandsJoystick.h
