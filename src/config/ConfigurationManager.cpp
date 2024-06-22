#include "ConfigurationManager.h"

#include "../engine/audio/AudioManager.h"
#include "../engine/texts/TextManager.h"

#include "../game/keys/KeyBinder.h"
#include "../game/keys/JoystickBinder.h"

ConfigurationManager ConfigurationManager::instance=ConfigurationManager();

ConfigurationManager::ConfigurationManager() : haveToSave(false), file(""),
    volume(64), volson(64), lang(0), skin(1), full(true), audio(0), text(0) {
}

ConfigurationManager::~ConfigurationManager() {
}

ConfigurationManager* ConfigurationManager::getInstance() {
    return &instance;
}

void ConfigurationManager::init(string filename, string keys, string joystick) {

    KeyBinder::getInstance()->init(keys);
    JoystickBinder::getInstance()->init(joystick);

    file = filename;
    haveToSave = false;

    ifstream f(file.c_str(), ios::in | ios::binary);
    if(f.is_open()) {
        f.read((char *)&volume,sizeof(int));
        f.read((char *)&volson,sizeof(int));
        f.read((char *)&lang,sizeof(int));
        f.read((char *)&skin,sizeof(int));
        f.read((char *)&full,sizeof(bool));
        f.close();
    }

    if (skin > 1) skin = 1;
    if (lang > 2) lang = 0;
    if (volume > 128) volume = 64;
    if (volson > 128) volson = 64;
    if (full > 1) full = 1;

    audio = new AudioHelper();

    AudioManager::getInstance()->init();
    AudioManager::getInstance()->setConfiguration(audio);
    AudioManager::getInstance()->setVolumeMusic(volume);
    AudioManager::getInstance()->setVolumeSound(volson);
}

void ConfigurationManager::initTexts() {
    text = new TextHelper();
    text->setLanguage(lang);

    TextManager::getInstance()->setConfiguration(text);
}

void ConfigurationManager::close() {
    delete audio;
    delete text;
}

void ConfigurationManager::save() {
    if (!haveToSave) {
        return;
    }
    ofstream f(file.c_str(), ios::out | ios::binary);
    f.write((char *)&volume,sizeof(int));
    f.write((char *)&volson,sizeof(int));
    f.write((char *)&lang,sizeof(int));
    f.write((char *)&skin,sizeof(int));
    f.write((char *)&full,sizeof(bool));
    f.close();
    haveToSave = false;
}

bool ConfigurationManager::isFrench() {
    return lang == 0;
}

string ConfigurationManager::getSkinName() {
    switch (skin) {
        case 0 : return "Original";
        case 1 : return "Blond";
        default : return "Blond";
    }
}

int ConfigurationManager::getVolume() {return volume;}
int ConfigurationManager::getVolson() {return volson;}
int ConfigurationManager::getLang() {return lang;}
int ConfigurationManager::getSkin() {return skin;}
bool ConfigurationManager::isFull() {return full;}

void ConfigurationManager::setVolume(int v) {
    if (volume != v) {
        volume = v;
        haveToSave = true;
        AudioManager::getInstance()->setVolumeMusic(volume);
    }
}

void ConfigurationManager::setVolson(int v) {
    if (volson != v) {
        volson = v;
        haveToSave = true;
        AudioManager::getInstance()->setVolumeSound(volson);
    }
}

void ConfigurationManager::setLang(int l) {
    lang = l;
    text->setLanguage(lang);
    TextManager::getInstance()->reloadTexts();
    haveToSave = true;
}

void ConfigurationManager::setSkin(int s) {
    skin = s;
    haveToSave = true;
}

void ConfigurationManager::setFull(bool f) {
    if (full != f) {
        full = f;
        haveToSave = true;
    }
}
