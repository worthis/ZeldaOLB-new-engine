/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __KEYBINDER_H__
#define __KEYBINDER_H__

#include "../../engine/common/Common.h"
#include "../../engine/window/Event.h"
#include "../../engine/texts/Text.h"

#include "Action.h"

enum BindableType
{
    BT_OPTIONS,    // Escape
    BT_INVENTAIRE, // Return
    BT_CARTE,      // P
    BT_MONSTERS,   // M
    BT_ACTION,     // Space
    BT_EPEE,       // W
    BT_OBJET,      // X
    BT_COURSE,     // Shift / Caps lock
    BT_TELEPORT,   // T en OniLink en donjon
    BT_UP,
    BT_DOWN,
    BT_LEFT,
    BT_RIGHT,
    BT_CAMERA,
    NB_BINDABLE
};

class KeyBinder
{
public:
    static KeyBinder *getInstance();

    void init(string filename);

    void save();

    void restoreDefault();

    Action *getActionForGame(Event *event);

    Keys getKey(BindableType type);
    Keys getDefaultKey(BindableType type);

    void setKey(BindableType type, Keys key);

    bool isQwerty();

    void setQwerty(bool b);

    Text *getTextForType(BindableType type, int color = 0);
    Text *getTextForKey(Keys key, int color = 0);

    void forceToSave();

private:
    KeyBinder();
    ~KeyBinder();
    static KeyBinder instance;

    bool qwerty;

    bool haveToSave;
    string file;

    Action action;
    Keys map[NB_BINDABLE];
};

#endif // KeyBinder.h
