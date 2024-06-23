/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WMUSIC_H__
#define __WMUSIC_H__

#include <SDL/SDL_mixer.h>

#include "../common/Common.h"
#include "WResource.h"

class WMusic : public WResource
{
public:
    WMusic(string filename);
    ~WMusic();
    Mix_Music *getMusic();

private:
    Mix_Music *music;
};

#endif // WMusic.h
