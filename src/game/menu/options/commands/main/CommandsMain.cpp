#include "CommandsMain.h"

#include "../../../../MainController.h"
#include "../../../../../engine/window/WindowManager.h"
#include "../../../../../engine/resources/ResourceManager.h"
#include "../../../../../engine/audio/AudioManager.h"
#include "../../../../../engine/texts/TextManager.h"
#include "../../../../../config/ConfigurationManager.h"

CommandsMain::CommandsMain() : line(3), warning(false), skin(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    for (int i = 0; i < 8; i++) {
        texts[i] = 0;
    }
}

CommandsMain::~CommandsMain() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    for (int i = 0; i < 8; i++) {
        delete texts[i];
    }
}

void CommandsMain::init() {
    for (int i = 0; i < 8; i++) {
        delete texts[i];
    }
    texts[0] = TextManager::getInstance()->getText(11);
    texts[1] = TextManager::getInstance()->getText(23);
    texts[2] = TextManager::getInstance()->getText(24);
    texts[3] = TextManager::getInstance()->getText(13);
    texts[4] = TextManager::getInstance()->getText(25);
    texts[5] = TextManager::getInstance()->getText(54);
    texts[6] = TextManager::getInstance()->getText(55);
    texts[7] = TextManager::getInstance()->getText(56);

    warning = false;

    skin = ConfigurationManager::getInstance()->getSkin();
}

void CommandsMain::handleEvents(Event* event) {

    if (event->isPushed(kReturn) || event->isPushed(kSpace)) {
        if (warning) {
            warning = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        } else {
            switch (line) {
                case 0:
                    MainController::getInstance()->getMenuController()->getOptionsController()->getOptionsCommandsController()->setStep(COMMANDS_KEYBOARD);
                    AudioManager::getInstance()->playSound(TS_MENU1);
                    break;
                case 1:
                    if (WindowManager::getInstance()->nbJoysticks()) {
                        MainController::getInstance()->getMenuController()->getOptionsController()->getOptionsCommandsController()->setStep(COMMANDS_JOYSTICK);
                        AudioManager::getInstance()->playSound(TS_MENU1);
                    } else {
                        warning = true;
                        AudioManager::getInstance()->playSound(TS_MENU1);
                    }
                    break;
                case 2:
                    KeyBinder::getInstance()->setQwerty(!KeyBinder::getInstance()->isQwerty());
                    AudioManager::getInstance()->playSound(TS_MENU3);
                    break;
                case 3:
                    MainController::getInstance()->getMenuController()->getOptionsController()->setStep(OPTIONS_MAIN);
                    KeyBinder::getInstance()->save();
                    AudioManager::getInstance()->playSound(TS_MENU2);
                    break;
                default: break;
            }
        }
        return;
    }

    if (event->isPushed(kUp) && !warning) {
        line--;
        if (line < 0) line = 3;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kDown) && !warning) {
        line++;
        if (line > 3) line = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if ((event->isPushed(kLeft) || event->isPushed(kRight)) && line == 2) {
        KeyBinder::getInstance()->setQwerty(!KeyBinder::getInstance()->isQwerty());
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void CommandsMain::draw() {
    drawPage();
    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21, 26, 53 + 48 * line);
    if (warning) {
        drawWarning();
    }
}

void CommandsMain::drawWarning() {
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[4]->getLength() * letterSize;
    int blocs = ((size + 15) / 16) + 1;

    drawCadre((320 - (blocs * 16))/2, 120 - 16, blocs * 16, 32);
    texts[4]->display((320 - size) / 2, 120 - 8);
}

void CommandsMain::drawPage() {
    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 20; i++) {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    drawTitle();

    drawCadre(16, 48, 288, 32);
    drawCadre(16, 96, 288, 32);
    drawCadre(16, 144, 288, 32);
    drawCadre(16, 192, 136, 32);

    int letterSize = TextManager::getInstance()->getWSpace();

    texts[5]->display(44, 152);
    int size = texts[KeyBinder::getInstance()->isQwerty() ? 7 : 6]->getLength() * letterSize;
    texts[KeyBinder::getInstance()->isQwerty() ? 7 : 6]->display(290 - size, 152);

    size = texts[1]->getLength() * letterSize;
    texts[1]->display((320 - size) / 2, 56);

    size = texts[2]->getLength() * letterSize;
    texts[2]->display((320 - size) / 2, 104);

    size = texts[3]->getLength() * letterSize;
    texts[3]->display(16 + (136 - size) / 2, 200);
}

void CommandsMain::drawTitle() {
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

void CommandsMain::drawCadre(int x, int y, int w, int h) {

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
