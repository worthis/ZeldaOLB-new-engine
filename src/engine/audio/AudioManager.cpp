#include "AudioManager.h"

AudioManager AudioManager::instance=AudioManager();

AudioManager::AudioManager() : current(0), music(0), volumeMusic(128), volumeSound(128),
    config(0), previous_volume(0), previous_volson(0), playing(false) {
    SOUND = true;
    previousMusic = -1;
}

AudioManager::~AudioManager() {

}

AudioManager* AudioManager::getInstance() {
    return &instance;
}

void AudioManager::init() {
    SOUND = FSOUND_Init(44100, 32, 0);
    if (SOUND) {
        previous_volson = FSOUND_GetSFXMasterVolume();
    }
}

void AudioManager::close() {
    if (SOUND) {
        if (current != 0) {
            FMUSIC_StopSong(current->getMusic());
            FMUSIC_SetMasterVolume(current->getMusic(), previous_volume);
            delete current;
        }
        FSOUND_SetSFXMasterVolume(previous_volson);
        FSOUND_Close();
    }
}

void AudioManager::setConfiguration(AudioConfiguration* conf) {
    if (SOUND) {
        config = conf;
        config->loadSounds();
    }
}

int AudioManager::getVolumeMusic() {
    return volumeMusic / 2;
}

int AudioManager::getVolumeSound() {
    return volumeSound / 2;
}

void AudioManager::setVolumeMusic(int v) {
    volumeMusic = v * 2;
    if (current != 0) {
        if (previous_volume == -1) {
            previous_volume = FMUSIC_GetMasterVolume(current->getMusic());
        }
        FMUSIC_SetMasterVolume(current->getMusic(), volumeMusic);
    }
}

void AudioManager::setVolumeSound(int v) {
    volumeSound = v * 2;
    if (SOUND) FSOUND_SetSFXMasterVolume(volumeSound);
}

void AudioManager::playMusic(int i) {
    if (SOUND) {
        if (music != i || !playing) {
            music = i;
            if (current != 0) {
                FMUSIC_StopSong(current->getMusic());
                delete current;
            }
            current = new WMusic(config->getMusicName(i));
            if (previous_volume == -1) {
                previous_volume = FMUSIC_GetMasterVolume(current->getMusic());
            }
            FMUSIC_SetMasterVolume(current->getMusic(), volumeMusic);
            FMUSIC_SetLooping(current->getMusic(), 1);
            FMUSIC_PlaySong(current->getMusic());
            playing = true;
        }
    }
}

void AudioManager::stopMusic() {
    if (SOUND) {
        previousMusic = music;
        FMUSIC_StopSong(current->getMusic());
        playing = false;
    }
}

void AudioManager::replayMusic() {
    if (previousMusic != -1) {
        playMusic(previousMusic);
    }
}

void AudioManager::setPreviousMusic(int m) {
    previousMusic = m;
}

void AudioManager::playSound(int i, int chl) {
    if (chl == -1) {
        chl = FSOUND_FREE;
    }
    if (SOUND) {
        FSOUND_PlaySound(chl, config->getSound(i)->getSound());
    }
}

int AudioManager::isPlaying(int chl) {
    if (SOUND) {
        return FSOUND_IsPlaying(chl);
    }
    return 0;
}

void AudioManager::stopSound(int chl) {
    if (SOUND) {
        FSOUND_StopSound(chl);
    }
}
