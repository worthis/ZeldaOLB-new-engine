#include "WSound.h"

WSound::WSound(string filename)
{
    name = filename;
    sound = Mix_LoadWAV(FSOUND_FREE, name.c_str(), 0, 0, 0);
}

WSound::~WSound()
{
    Mix_FreeChunk(sound);
}

Mix_Chunk *WSound::getSound()
{
    return sound;
}
