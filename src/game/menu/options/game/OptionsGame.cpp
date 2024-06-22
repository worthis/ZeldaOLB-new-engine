#include "OptionsGame.h"

#include "../../../MainController.h"
#include "../../../../engine/window/WindowManager.h"
#include "../../../../engine/resources/ResourceManager.h"
#include "../../../../engine/audio/AudioManager.h"
#include "../../../../engine/texts/TextManager.h"
#include "../../../../config/ConfigurationManager.h"

OptionsGame::OptionsGame() : line(3), skin(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    for (int i = 0; i < 9; i++) {
        texts[i] = 0;
    }
}

OptionsGame::~OptionsGame() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    for (int i = 0; i < 9; i++) {
        delete texts[i];
    }
}

void OptionsGame::init() {
    initTexts();
    skin = ConfigurationManager::getInstance()->getSkin();
}

void OptionsGame::initTexts() {
    for (int i = 0; i < 9; i++) {
        delete texts[i];
    }
    texts[0] = TextManager::getInstance()->getText(10);
    texts[1] = TextManager::getInstance()->getText(14);
    texts[2] = TextManager::getInstance()->getText(15);
    texts[3] = TextManager::getInstance()->getText(16);
    texts[4] = TextManager::getInstance()->getText(17);
    texts[5] = TextManager::getInstance()->getText(18);
    texts[6] = TextManager::getInstance()->getText(19);
    texts[7] = TextManager::getInstance()->getText(20);
    texts[8] = TextManager::getInstance()->getText(13);
}

void OptionsGame::handleEvents(Event* event) {

    if ((event->isPushed(kReturn) || event->isPushed(kSpace)) && line == 3) {
        MainController::getInstance()->getMenuController()->getOptionsController()->setStep(OPTIONS_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    if (event->isPushed(kUp)) {
        line--;
        if (line < 0) line = 3;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kDown)) {
        line++;
        if (line > 3) line = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kLeft)) {
        if (line == 0) {
            AudioManager::getInstance()->playSound(TS_MENU3);
            bool isFull = WindowManager::getInstance()->isFullScreen();
            WindowManager::getInstance()->setFullScreen(!isFull);
        } else if (line == 1) {
            int language = ConfigurationManager::getInstance()->getLang();
            language--;
            if (language < 0) language = 2;
            ConfigurationManager::getInstance()->setLang(language);
            AudioManager::getInstance()->playSound(TS_MENU3);
            initTexts();
        } else if (line == 2) {
            skin--;
            if (skin < 0) skin = 1;
            ConfigurationManager::getInstance()->setSkin(skin);
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
    }
    if (event->isPushed(kRight)) {
        if (line == 0) {
            AudioManager::getInstance()->playSound(TS_MENU3);
            bool isFull = WindowManager::getInstance()->isFullScreen();
            WindowManager::getInstance()->setFullScreen(!isFull);
        } else if (line == 1) {
            int language = ConfigurationManager::getInstance()->getLang();
            language++;
            if (language > 2) language = 0;
            ConfigurationManager::getInstance()->setLang(language);
            AudioManager::getInstance()->playSound(TS_MENU3);
            initTexts();
        } else if (line == 2) {
            skin++;
            if (skin > 1) skin = 0;
            ConfigurationManager::getInstance()->setSkin(skin);
            AudioManager::getInstance()->playSound(TS_MENU3);
        }
    }
}

void OptionsGame::draw() {
    drawPage();
    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21, 26, 53 + 48 * line);
}

void OptionsGame::drawPage() {
    int letterSize = TextManager::getInstance()->getWSpace();

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

    texts[1]->display(44, 56);
    int size = texts[WindowManager::getInstance()->isFullScreen() ? 2 : 3]->getLength() * letterSize;
    texts[WindowManager::getInstance()->isFullScreen() ? 2 : 3]->display(290 - size, 56);

    texts[4]->display(44, 104);

    texts[5]->display(44, 152);
    size = texts[6 + skin]->getLength() * letterSize;
    texts[6 + skin]->display(290 - size, 152);

    size = texts[8]->getLength() * letterSize;
    texts[8]->display(16 + (136 - size) / 2, 200);
}

void OptionsGame::drawTitle() {
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

void OptionsGame::drawCadre(int x, int y, int w, int h) {

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
