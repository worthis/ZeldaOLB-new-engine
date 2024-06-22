#include "WMusic.h"

WMusic::WMusic(string filename) {
    name = filename;
    music = FMUSIC_LoadSong(name.c_str());
}

WMusic::~WMusic() {
    FMUSIC_FreeSong(music);
}

FMUSIC_MODULE* WMusic::getMusic() {
    return music;
}
