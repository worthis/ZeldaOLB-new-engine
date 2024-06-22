/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __JOYSTICKBINDER_H__
#define __JOYSTICKBINDER_H__

#include "../../engine/common/Common.h"
#include "../../engine/window/Event.h"
#include "../../engine/texts/Text.h"

#include "KeyBinder.h"

class JoystickBinder
{
public:
    static JoystickBinder *getInstance();

    void init(string filename);

    void save();

    void restoreDefault();

    void addMenuEventsForJoystick(Event *event);

    void addGameEventsForJoystick(Event *event);

    bool isJoystickInUsage(Event *event);

    void setKey(BindableType type, Keys key);

    Keys getKey(BindableType type);
    Keys getDefaultKey(BindableType type);

    Text *getTextForType(BindableType type, int color = 0);
    Text *getTextForKey(Keys key, int color = 0);

    void forceToSave();

private:
    JoystickBinder();
    ~JoystickBinder();
    static JoystickBinder instance;

    bool rush;
    bool haveToSave;
    string file;

    Keys map[BT_UP];
};

#endif // JoystickBinder.h
