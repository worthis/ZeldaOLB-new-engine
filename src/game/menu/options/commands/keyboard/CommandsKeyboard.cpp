#include "CommandsKeyboard.h"

#include "../../../../MainController.h"
#include "../../../../../engine/window/WindowManager.h"
#include "../../../../../engine/resources/ResourceManager.h"
#include "../../../../../engine/audio/AudioManager.h"
#include "../../../../../engine/texts/TextManager.h"
#include "../../../../../config/ConfigurationManager.h"

CommandsKeyboard::CommandsKeyboard() : line(7), column(0), page(0), edit(false), confirm(false), subline(1), skin(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    fairy = ResourceManager::getInstance()->loadImage("data/images/menus/fee.png");
    for (int i = 0; i < 37; i++) {
        texts[i] = 0;
    }
}

CommandsKeyboard::~CommandsKeyboard() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    ResourceManager::getInstance()->free(fairy);
    for (int i = 0; i < 37; i++) {
        delete texts[i];
    }
}

void CommandsKeyboard::init() {
    for (int i = 0; i < 23; i++) {
        delete texts[i];
    }
    TextManager* tm = TextManager::getInstance();
    texts[0] = tm->getText(23);
    texts[1] = tm->getText(13);
    texts[2] = tm->getText(58);
    texts[3] = tm->getText(59);
    texts[4] = tm->getText(60);
    texts[5] = tm->getText(28);
    texts[6] = tm->getText(29);
    texts[7] = tm->getText(30);
    texts[8] = tm->getText(31);
    texts[9] = tm->getText(32);
    texts[10] = tm->getText(33);
    texts[11] = tm->getText(34);
    texts[12] = tm->getText(35);
    texts[13] = tm->getText(36);
    texts[14] = tm->getText(37);
    texts[15] = tm->getText(38);
    texts[16] = tm->getText(39);
    texts[17] = tm->getText(57);
    texts[18] = tm->getText(40);
    texts[19] = tm->getText(41);
    texts[20] = tm->getText(42);
    texts[21] = tm->getText(52);
    texts[22] = tm->getText(53);

    reloadTextsForKeys();

    page = 0;
    edit = false;
    confirm = false;
    subline = 1;

    skin = ConfigurationManager::getInstance()->getSkin();
}

void CommandsKeyboard::reloadTextsForKeys() {
    KeyBinder* kb = KeyBinder::getInstance();
    for (int i = 23; i < 37; i++) {
        delete texts[i];
        texts[i] = kb->getTextForType(getBindableTypeForId(i - 23));
    }
}

BindableType CommandsKeyboard::getBindableTypeForLineAndPage(int l, int p) {
    return getBindableTypeForId(l - 1 + p * 6);
}

BindableType CommandsKeyboard::getBindableTypeForId(int i) {
    switch (i) {
        case 0 : return BT_UP;
        case 1 : return BT_DOWN;
        case 2 : return BT_LEFT;
        case 3 : return BT_RIGHT;
        case 4 : return BT_COURSE;
        case 5 : return BT_EPEE;
        case 6 : return BT_OBJET;
        case 7 : return BT_ACTION;
        case 8 : return BT_INVENTAIRE;
        case 9 : return BT_TELEPORT;
        case 10 : return BT_CARTE;
        case 11 : return BT_MONSTERS;
        case 12 : return BT_CAMERA;
        case 13 : return BT_OPTIONS;
        default : return BT_UP;
    }
}

void CommandsKeyboard::updateSelectedKey(Keys key) {
    KeyBinder* kb = KeyBinder::getInstance();

    BindableType selectedType = getBindableTypeForLineAndPage(line, page);
    Keys currentValue = kb->getKey(selectedType);

    if (currentValue == key) return;

    //switch keys if needed
    for (int i = 0; i < 14; i++) {
        BindableType type = getBindableTypeForId(i);
        if (kb->getKey(type) == key) {
            kb->setKey(type, currentValue);
            break;
        }
    }

    kb->setKey(selectedType, key);

    reloadTextsForKeys();
}

void CommandsKeyboard::handleEvents(Event* event) {
    if (edit) {
        for (int i = 0; i < kF1; i++) {
            if (event->isPushed((Keys)i)) {
                // ignore joystick events
                if ((i == kReturn && (event->isPushed(jStart) || event->isPushed(jA) || event->isPushed(jB)))
                    || (i == kUp && (event->isPushed(jUp) || event->isPushed(jLUp)))
                    || (i == kDown && (event->isPushed(jDown) || event->isPushed(jLDown)))
                    || (i == kLeft && (event->isPushed(jLeft) || event->isPushed(jLLeft)))
                    || (i == kRight && (event->isPushed(jRight) || event->isPushed(jLRight)))) {
                    continue;
                }
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
                KeyBinder::getInstance()->restoreDefault();
                KeyBinder::getInstance()->forceToSave();
                reloadTextsForKeys();
            }
            subline = 1;
            confirm = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        } else if (line == 0) {
            page++;
            if (page > 2) page = 0;
            AudioManager::getInstance()->playSound(TS_MENU3);
        } else if (line == 7 && column == 0) {
            MainController::getInstance()->getMenuController()->getOptionsController()->getOptionsCommandsController()->setStep(COMMANDS_MAIN);
            AudioManager::getInstance()->playSound(TS_MENU2);
            KeyBinder::getInstance()->save();
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
        if (line == 6 && page == 2) line = 2;
        AudioManager::getInstance()->playSound(TS_MENU3);
        column = 0;
    }
    if (event->isPushed(kDown)) {
        line++;
        if (line > 7) line = 0;
        if (line == 3 && page == 2) line = 7;
        AudioManager::getInstance()->playSound(TS_MENU3);
        column = 0;
    }
    if (event->isPushed(kLeft) && line == 0) {
        page--;
        if (page < 0) page = 2;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kRight) && line == 0) {
        page++;
        if (page > 2) page = 0;
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

void CommandsKeyboard::draw() {
    drawPage();
    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21,
                                       26 + 152 * column + (edit ? 252 : 0),
                                       53 + 16 * line + (line == 7 ? 32 : 0));
    if (confirm) {
        drawConfirm();
        WindowManager::getInstance()->draw(fairy, 0, 0, 16, 16, 112, 113 + 20 * subline);
    }
}

void CommandsKeyboard::drawConfirm() {//104, 84
    drawCadre(104, 84, 112, 72);

    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[20]->getLength() * letterSize;
    texts[20]->display(104 + (112 - size) / 2, 84 + 9);

    // yes
    size = texts[21]->getLength() * letterSize;
    texts[21]->display(104 + (112 - size) / 2, 84 + 29);

    // no
    size = texts[22]->getLength() * letterSize;
    texts[22]->display(104 + (112 - size) / 2, 84 + 49);
}

void CommandsKeyboard::drawPage() {
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
        if (page < 2 || i < 2) {
            texts[5 + i + page * 6]->display(44, 72 + 16 * i);
            size = texts[23 + i + page * 6]->getLength() * letterSize;
            texts[23 + i + page * 6]->display(272 - size, 72 + 16 * i);
        }
    }

    // back
    size = texts[1]->getLength() * letterSize;
    texts[1]->display(16 + (136 - size) / 2, 200);

    // default
    size = texts[19]->getLength() * letterSize;
    texts[19]->display(168 + (136 - size) / 2, 200);
}

void CommandsKeyboard::drawTitle() {
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

void CommandsKeyboard::drawCadre(int x, int y, int w, int h) {

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
