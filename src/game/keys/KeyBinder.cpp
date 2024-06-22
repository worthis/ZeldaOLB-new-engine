#include "KeyBinder.h"

#include "../../engine/texts/TextManager.h"

#include "../MainController.h"

KeyBinder KeyBinder::instance=KeyBinder();

KeyBinder::KeyBinder() : qwerty(false), haveToSave(false) {
    restoreDefault();
}

KeyBinder::~KeyBinder() {
}

KeyBinder* KeyBinder::getInstance() {
    return &instance;
}

void KeyBinder::restoreDefault() {
    // default values
    for (int i = 0; i < NB_BINDABLE; i++) {
        map[i] = getDefaultKey((BindableType)i);
    }
}

Keys KeyBinder::getDefaultKey(BindableType type) {
    switch (type) {
        case BT_OPTIONS: return kEscape;
        case BT_INVENTAIRE: return kReturn;
        case BT_CARTE: return kP;
        case BT_MONSTERS: return kO;
        case BT_ACTION: return kSpace;
        case BT_EPEE: return kZ;
        case BT_OBJET: return kX;
        case BT_COURSE: return kShift;
        case BT_UP: return kUp;
        case BT_DOWN: return kDown;
        case BT_LEFT: return kLeft;
        case BT_RIGHT: return kRight;
        case BT_CAMERA: return kCtrl;
        case BT_TELEPORT: return kT;
        default: return kUp;
    }
}

void KeyBinder::init(string filename) {
    file = filename;
    haveToSave = false;

    ifstream f(file.c_str(), ios::in | ios::binary);
    if(f.is_open()) {
        f.read((char *)&qwerty,sizeof(bool));
        for (int i = 0; i < NB_BINDABLE; i++) {
            f.read((char *)&map[i],sizeof(int));
        }
        f.close();
    }
}

void KeyBinder::save() {
    if (!haveToSave) {
        return;
    }
    ofstream f(file.c_str(), ios::out | ios::binary);
    f.write((char *)&qwerty,sizeof(bool));
    for (int i = 0; i < NB_BINDABLE; i++) {
        f.write((char *)&map[i],sizeof(int));
    }
    f.close();
    haveToSave = false;
}

Keys KeyBinder::getKey(BindableType type) {
    return map[type];
}

void KeyBinder::setKey(BindableType type, Keys key) {
    if (map[type] != key) {
        haveToSave = true;
        map[type] = key;
    }
}

bool KeyBinder::isQwerty() {
    return qwerty;
}

void KeyBinder::setQwerty(bool b) {
    if (qwerty != b) {
        haveToSave = true;
        qwerty = b;
    }
}

Text* KeyBinder::getTextForType(BindableType type, int color) {
    return getTextForKey(getKey(type), color);
}

Text* KeyBinder::getTextForKey(Keys key, int color) {
    ostringstream os;
    if (color > 0) {
        os << "[c=" << color << "]";
    }

    Text* tmp = 0;

    switch (key) {
        case kA : os << (qwerty ? "A" : "Q"); break;
        case kZ : os << (qwerty ? "Z" : "W"); break;
        case kE : os << "E"; break;
        case kR : os << "R"; break;
        case kT : os << "T"; break;
        case kY : os << "Y"; break;
        case kU : os << "U"; break;
        case kI : os << "I"; break;
        case kO : os << "O"; break;
        case kP : os << "P"; break;
        case kQ : os << (qwerty ? "Q" : "A"); break;
        case kS : os << "S"; break;
        case kD : os << "D"; break;
        case kF : os << "F"; break;
        case kG : os << "G"; break;
        case kH : os << "H"; break;
        case kJ : os << "J"; break;
        case kK : os << "K"; break;
        case kL : os << "L"; break;
        case kM : os << (qwerty ? "M" : ","); break;
        case kW : os << (qwerty ? "W" : "Z"); break;
        case kX : os << "X"; break;
        case kC : os << "C"; break;
        case kV : os << "V"; break;
        case kB : os << "B"; break;
        case kN : os << "N"; break;
        case kComma : os << (qwerty ? "," : ";"); break;
        case kSemicol : os << (qwerty ? ";" : "M"); break;
        case kEscape : tmp = TextManager::getInstance()->getText(43); break;
        case kTab : tmp = TextManager::getInstance()->getText(44); break;
        case kShift : tmp = TextManager::getInstance()->getText(45); break;
        case kCtrl : os << "CTRL"; break;
        case kAlt : os << "ALT"; break;
        case kSpace : tmp = TextManager::getInstance()->getText(46); break;
        case kReturn : tmp = TextManager::getInstance()->getText(47); break;
        case k0 : os << "0"; break;
        case k1 : os << "1"; break;
        case k2 : os << "2"; break;
        case k3 : os << "3"; break;
        case k4 : os << "4"; break;
        case k5 : os << "5"; break;
        case k6 : os << "6"; break;
        case k7 : os << "7"; break;
        case k8 : os << "8"; break;
        case k9 : os << "9"; break;
        case kUp : tmp = TextManager::getInstance()->getText(48); break;
        case kDown : tmp = TextManager::getInstance()->getText(49); break;
        case kLeft : tmp = TextManager::getInstance()->getText(50); break;
        case kRight : tmp = TextManager::getInstance()->getText(51); break;
        case kF1 : os << "F1"; break;
        default : os << "?"; break;
    }

    if (tmp != 0) {
        os << tmp->getText();
        delete tmp;
    }


    return new Text(os.str());
}

Action* KeyBinder::getActionForGame(Event* event) {

    action.setAction(UP, event->isDown(map[BT_UP]));
    action.setAction(DOWN, event->isDown(map[BT_DOWN]));
    action.setAction(LEFT, event->isDown(map[BT_LEFT]));
    action.setAction(RIGHT, event->isDown(map[BT_RIGHT]));

    action.setAction(PUSH_UP, event->isPushed(map[BT_UP]));
    action.setAction(PUSH_DOWN, event->isPushed(map[BT_DOWN]));
    action.setAction(PUSH_LEFT, event->isPushed(map[BT_LEFT]));
    action.setAction(PUSH_RIGHT, event->isPushed(map[BT_RIGHT]));

    action.setAction(RUN, event->isDown(map[BT_COURSE]));

    if (event->isPushed(map[BT_EPEE])) {
        action.setAction(HIT, true);
    } else {
        action.setAction(HIT, false);
        action.setAction(LOAD, event->isDown(map[BT_EPEE]));
    }

    action.setAction(OBJECT, event->isPushed(map[BT_OBJET]));
    action.setAction(ACTION, event->isPushed(map[BT_ACTION]));

    action.setAction(DISPLAY_MAP, event->isPushed(map[BT_CARTE]));

    action.setAction(MONSTERS, event->isPushed(map[BT_MONSTERS]));
    action.setAction(INVENTAIRE, event->isPushed(map[BT_INVENTAIRE]));
    action.setAction(QUIT_GAME, event->isPushed(map[BT_OPTIONS]));

    action.setAction(TELEPORT, event->isPushed(map[BT_TELEPORT]));

    action.setAction(CAMERA, event->isPushed(map[BT_CAMERA]) || event->isDown(map[BT_CAMERA]));

    action.setAction(AIDE, event->isPushed(kF1));

    action.setAction(MAP_1, event->isPushed(k1));
    action.setAction(MAP_2, event->isPushed(k2));
    action.setAction(MAP_3, event->isPushed(k3));
    action.setAction(MAP_4, event->isPushed(k4));
    action.setAction(MAP_5, event->isPushed(k5));
    action.setAction(MAP_6, event->isPushed(k6));
    action.setAction(MAP_7, event->isPushed(k7));
    action.setAction(MAP_8, event->isPushed(k8));
    action.setAction(MAP_9, event->isPushed(k9));

    return &action;
}

void KeyBinder::forceToSave() {
    haveToSave = true;
}
