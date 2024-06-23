/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CONFIGURATIONMANAGER_H__
#define __CONFIGURATIONMANAGER_H__

#include "../engine/common/Common.h"

#include "AudioHelper.h"
#include "TextHelper.h"

class ConfigurationManager
{
public:
    static ConfigurationManager *getInstance();

    void init(string filename, string keys, string joystick);

    void initTexts();

    void save();

    bool isFrench();
    bool isRussian();
    string getSkinName();

    int getVolume();
    int getVolson();
    int getLang();
    int getSkin();
    bool isFull();

    void setVolume(int v);
    void setVolson(int v);
    void setLang(int l);
    void setSkin(int s);
    void setFull(bool f);

    void close();

private:
    ConfigurationManager();
    ~ConfigurationManager();
    static ConfigurationManager instance;

    bool haveToSave;
    string file;
    int volume;
    int volson;
    int lang;
    int skin;
    bool full;

    AudioHelper *audio;
    TextHelper *text;
};

#endif // ConfigurationManager.h
