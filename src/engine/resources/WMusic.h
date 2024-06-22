/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WMUSIC_H__
#define __WMUSIC_H__

#include <FMOD/fmod.h>

#include "../common/Common.h"
#include "WResource.h"

class WMusic : public WResource
{
public:
    WMusic(string filename);
    ~WMusic();
    FMUSIC_MODULE *getMusic();

private:
    FMUSIC_MODULE *music;
};

#endif // WMusic.h
