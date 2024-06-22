#include "WSound.h"

WSound::WSound(string filename)
{
    name = filename;
    sound = FSOUND_Sample_Load(FSOUND_FREE, name.c_str(), 0, 0, 0);
}

WSound::~WSound()
{
    FSOUND_Sample_Free(sound);
}

FSOUND_SAMPLE *WSound::getSound()
{
    return sound;
}
