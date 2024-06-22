/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WSOUND_H__
#define __WSOUND_H__

#include <FMOD/fmod.h>

#include "../common/Common.h"
#include "WResource.h"

class WSound : public WResource
{
public:
    WSound(string filename);
    ~WSound();
    FSOUND_SAMPLE *getSound();

private:
    FSOUND_SAMPLE *sound;
};

#endif // WSound.h
