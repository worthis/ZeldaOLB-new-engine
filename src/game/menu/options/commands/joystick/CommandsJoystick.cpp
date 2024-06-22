#include "CommandsJoystick.h"

#include "../../../../MainController.h"
#include "../../../../../engine/window/WindowManager.h"
#include "../../../../../engine/resources/ResourceManager.h"
#include "../../../../../engine/audio/AudioManager.h"
#include "../../../../../engine/texts/TextManager.h"
#include "../../../../../config/ConfigurationManager.h"

CommandsJoystick::CommandsJoystick() : line(7), column(0), page(0), edit(false), confirm(false), subline(1), skin(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    fairy = ResourceManager::getInstance()->loadImage("data/images/menus/fee.png");
    for (int i = 0; i < 26; i++) {
        texts[i] = 0;
    }
}

CommandsJoystick::~CommandsJoystick() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    ResourceManager::getInstance()->free(fairy);
    for (int i = 0; i < 26; i++) {
        delete texts[i];
    }
}

void CommandsJoystick::init() {
    for (int i = 0; i < 17; i++) {
        delete texts[i];
    }
    TextManager* tm = TextManager::getInstance();
    texts[0] = tm->getText(24);
    texts[1] = tm->getText(13);
    texts[2] = tm->getText(26);
    texts[3] = tm->getText(27);
    texts[4] = tm->getText(32);
    texts[5] = tm->getText(33);
    texts[6] = tm->getText(34);
    texts[7] = tm->getText(35);
    texts[8] = tm->getText(36);
    texts[9] = tm->getText(37);
    texts[10] = tm->getText(38);
    texts[11] = tm->getText(39);
    texts[12] = tm->getText(40);
    texts[13] = tm->getText(41);
    texts[14] = tm->getText(42);
    texts[15] = tm->getText(52);
    texts[16] = tm->getText(53);

    reloadTextsForKeys();

    page = 0;
    edit = false;
    confirm = false;
    subline = 1;

    skin = ConfigurationManager::getInstance()->getSkin();
}

void CommandsJoystick::reloadTextsForKeys() {
    JoystickBinder* jb = JoystickBinder::getInstance();
    for (int i = 17; i < 26; i++) {
        delete texts[i];
        texts[i] = jb->getTextForType(getBindableTypeForId(i - 17));
    }
}

BindableType CommandsJoystick::getBindableTypeForLineAndPage(int l, int p) {
    return getBindableTypeForId(l - 1 + p * 6);
}

BindableType CommandsJoystick::getBindableTypeForId(int i) {
    switch (i) {
        case 0 : return BT_COURSE;
        case 1 : return BT_EPEE;
        case 2 : return BT_OBJET;
        case 3 : return BT_ACTION;
        case 4 : return BT_INVENTAIRE;
        case 5 : return BT_TELEPORT;
        case 6 : return BT_CARTE;
        case 7 : return BT_MONSTERS;
        case 8 : return BT_OPTIONS;
        default : return BT_UP;
    }
}

void CommandsJoystick::updateSelectedKey(Keys key) {
    JoystickBinder* jb = JoystickBinder::getInstance();

    BindableType selectedType = getBindableTypeForLineAndPage(line, page);
    Keys currentValue = jb->getKey(selectedType);

    if (currentValue == key) return;

    //switch keys if needed
    for (int i = 0; i < 9; i++) {
        BindableType type = getBindableTypeForId(i);
        if (jb->getKey(type) == key) {
            jb->setKey(type, currentValue);
            break;
        }
    }

    jb->setKey(selectedType, key);

    reloadTextsForKeys();
}

void CommandsJoystick::handleEvents(Event* event) {
    if (edit) {
        for (int i = jSelect; i < NB_KEYS; i++) {
            if (event->isPushed((Keys)i)) {
                updateSelectedKey((Keys)i);
                edit = false;
                AudioManager::getInstance()->playSound(TS_MENU3);

                // hack to avoid to quit the game
                event->setEvent(kEscape, false);
                return;
            }
        }
        return;
    }
    // hack to avoid to quit the game
    if (line > 0 && line < 7) {
        event->setEvent(kEscape, false);
    }

    if (event->isPushed(kReturn) || event->isPushed(kSpace)) {
        if (confirm) {
            if (subline == 0) {
                JoystickBinder::getInstance()->restoreDefault();
                JoystickBinder::getInstance()->forceToSave();
                reloadTextsForKeys();
            }
            subline = 1;
            confirm = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        } else if (line == 0) {
            page++;
            if (page > 1) page = 0;
            AudioManager::getInstance()->playSound(TS_MENU3);
        } else if (line == 7 && column == 0) {
            MainController::getInstance()->getMenuController()->getOptionsController()->getOptionsCommandsController()->setStep(COMMANDS_MAIN);
            AudioManager::getInstance()->playSound(TS_MENU2);
            JoystickBinder::getInstance()->save();
        } else if (line == 7 && column == 1) {
            confirm = true;
            AudioManager::getInstance()->playSound(TS_MENU1);
        } else {
            edit = true;
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
        return;
    }

    if (confirm) {
        if (event->isPushed(kUp) || event->isPushed(kDown)) {
            subline = (subline + 1) % 2;
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
        return;
    }

    if (event->isPushed(kUp)) {
        line--;
        if (line < 0) line = 7;
        if (line == 6 && page == 1) line = 3;
        AudioManager::getInstance()->playSound(TS_MENU3);
        column = 0;
    }
    if (event->isPushed(kDown)) {
        line++;
        if (line > 7) line = 0;
        if (line == 4 && page == 1) line = 7;
        AudioManager::getInstance()->playSound(TS_MENU3);
        column = 0;
    }
    if (event->isPushed(kLeft) && line == 0) {
        page--;
        if (page < 0) page = 1;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kRight) && line == 0) {
        page++;
        if (page > 1) page = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kLeft) && line == 7) {
        column--;
        if (column < 0) column = 1;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kRight) && line == 7) {
        column++;
        if (column > 1) column = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void CommandsJoystick::draw() {
    drawPage();
    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21,
                                       26 + 152 * column + (edit ? 252 : 0),
                                       53 + 16 * line + (line == 7 ? 32 : 0));
    if (confirm) {
        drawConfirm();
        WindowManager::getInstance()->draw(fairy, 0, 0, 16, 16, 112, 113 + 20 * subline);
    }
}

void CommandsJoystick::drawConfirm() {//104, 84
    drawCadre(104, 84, 112, 72);

    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[14]->getLength() * letterSize;
    texts[14]->display(104 + (112 - size) / 2, 84 + 9);

    // yes
    size = texts[15]->getLength() * letterSize;
    texts[15]->display(104 + (112 - size) / 2, 84 + 29);

    // no
    size = texts[16]->getLength() * letterSize;
    texts[16]->display(104 + (112 - size) / 2, 84 + 49);
}

void CommandsJoystick::drawPage() {
    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 20; i++) {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    drawTitle();

    drawCadre(16, 48, 288, 128);

    drawCadre(16, 192, 136, 32);
    drawCadre(168, 192, 136, 32);


    texts[2 + page]->display(44, 56);

    int letterSize = TextManager::getInstance()->getWSpace();
    int size;

    for (int i = 0; i < 6; i++) {
        if (page == 0 || i < 3) {
            texts[4 + i + page * 6]->display(44, 72 + 16 * i);
            size = texts[17 + i + page * 6]->getLength() * letterSize;
            texts[17 + i + page * 6]->display(272 - size, 72 + 16 * i);
        }
    }

    // back
    size = texts[1]->getLength() * letterSize;
    texts[1]->display(16 + (136 - size) / 2, 200);

    // default
    size = texts[13]->getLength() * letterSize;
    texts[13]->display(168 + (136 - size) / 2, 200);
}

void CommandsJoystick::drawTitle() {
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[0]->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++) {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    texts[0]->display(32 + 8 + ((blocs * 16) - size) / 2, 16);
}

void CommandsJoystick::drawCadre(int x, int y, int w, int h) {

    // center
    for (int j = y + 16; j < y + h - 16; j += 16) {
        for (int i = x + 16; i < x + w - 16; i += 16) {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    //top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16) {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    //left and right
    for (int j = y + 16; j < y + h - 16; j += 16) {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    //top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    //top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    //bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    //bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);
}
