#include "MainMenu.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"
#include "../../../config/ConfigurationManager.h"

MainMenu::MainMenu() : line(0), column(0), load(false), confirm(false), subLine(0), skin(0) {

    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    status = ResourceManager::getInstance()->loadImage("data/images/status/status.png", true);
    fairy = ResourceManager::getInstance()->loadImage("data/images/menus/fee.png", true);
    stuff = ResourceManager::getInstance()->loadImage("data/images/status/stuff.png", true);
    inventaire = ResourceManager::getInstance()->loadImage("data/images/status/inventaire.png", true);

    for (int i = 0; i < 3; i++) {
        saves[i] = new Save(i + 1);
    }
    for (int i = 0; i < 12; i++) {
        texts[i] = 0;
    }
}

MainMenu::~MainMenu() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    ResourceManager::getInstance()->free(status);
    ResourceManager::getInstance()->free(fairy);
    ResourceManager::getInstance()->free(stuff);
    ResourceManager::getInstance()->free(inventaire);

    for (int i = 0; i < 3; i++) {
        delete saves[i];
    }
    for (int i = 0; i < 12; i++) {
        delete texts[i];
    }
}

void MainMenu::init() {

    for (int i = 0; i < 12; i++) {
        delete texts[i];
    }

    texts[0] = TextManager::getInstance()->getText(1);
    texts[1] = new Text("1.");
    texts[2] = new Text("2.");
    texts[3] = new Text("3.");
    texts[4] = TextManager::getInstance()->getText(2);
    texts[5] = TextManager::getInstance()->getText(3);
    texts[6] = TextManager::getInstance()->getText(4);
    texts[7] = TextManager::getInstance()->getText(5);
    texts[8] = TextManager::getInstance()->getText(6);
    texts[9] = TextManager::getInstance()->getText(7);
    texts[10] = TextManager::getInstance()->getText(8);
    texts[11] = TextManager::getInstance()->getText(9);

    skin = ConfigurationManager::getInstance()->getSkin();

    AudioManager::getInstance()->playMusic(1);

    load = false;
    confirm = false;
}

void MainMenu::handleEvents(Event* event) {
    if (event->isPushed(kReturn) || event->isPushed(kSpace)) {

        if (line == 3) {

            if (column == 0) {
                MainController::getInstance()->getMenuController()->setStep(MENU_OPTIONS);
            } else {
                MainController::getInstance()->getMenuController()->setStep(MENU_RECORDS);
            }
            AudioManager::getInstance()->playSound(TS_MENU1);

        } else {

            if (confirm) {

                if (subLine == 0) {
                    saves[line]->erase();
                    init();
                    load = false;
                }
                confirm = false;
                AudioManager::getInstance()->playSound(TS_MENU2);

            } else if (load) {

                if (subLine == 0) {
                    AudioManager::getInstance()->playSound(TS_MENU1);
                    AudioManager::getInstance()->stopMusic();
                    MainController::getInstance()->getGameController()->setSave(saves[line]);
                    MainController::getInstance()->setStep(GAME);
                } else if (subLine == 1) {
                    confirm = true;
                    AudioManager::getInstance()->playSound(TS_MENU1);
                } else if (subLine == 2) {
                    load = false;
                    AudioManager::getInstance()->playSound(TS_MENU2);
                }

            } else {
                if (saves[line]->isLoaded()) {
                    load = true;
                    subLine = 0;
                } else {
                    AudioManager::getInstance()->stopMusic();
                    MainController::getInstance()->getGameController()->setSave(saves[line]);
                    MainController::getInstance()->setStep(OPENING);
                }
                AudioManager::getInstance()->playSound(TS_MENU1);
            }
        }
        return;
    }

    if (event->isPushed(kUp)) {
        if (confirm) {
            subLine--;
            if (subLine < 0) subLine = 1;
        } else if (load) {
            subLine--;
            if (subLine < 0) subLine = 2;
        } else {
            line--;
            if (line < 0) line = 3;
            column = 0;
        }
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kDown)) {
        if (confirm) {
            subLine++;
            if (subLine > 1) subLine = 0;
        } else if (load) {
            subLine++;
            if (subLine > 2) subLine = 0;
        } else {
            line++;
            if (line > 3) line = 0;
            column = 0;
        }
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (!load && !confirm && event->isPushed(kLeft) && line == 3) {
        column--;
        if (column < 0) column = 1;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (!load && !confirm && event->isPushed(kRight) && line == 3) {
        column++;
        if (column > 1) column = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void MainMenu::drawCadre(int x, int y, int w, int h) {
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

void MainMenu::drawTitle() {
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

void MainMenu::drawSaves() {
    // saves
    for (int i = 0; i < 3; i++) {
        Save* save = saves[i];
        if (save->isLoaded()) {
            // life
            for(int j = 0; j < save->getMaxLife()/2; j++) {

                int x = 0;
                int l = save->getLife() - (j * 2);
                if (l > 1) x = 141;
                if (l == 1) x = 149;
                if (l < 1) x = 157;

                WindowManager::getInstance()->draw(status, x, 9, 7, 7,
                                                   64 - 8 + ((j % 10) * 8) + 8,
                                                   57 + 8 * ((int)(j / 10)) + i * 48);
            }

            for (int j = 0; j < NB_GRAALS; j++) {
                WindowManager::getInstance()->draw(stuff, save->getGraals(j) ? 0 : 17, 48, 16, 16,
                                                   176+8-16-16-4 + ((16+2)*j),
                                                   56 + i * 48);
            }

            if (save->getEpee()) {
                WindowManager::getInstance()->draw(stuff, (save->getEpee() - 1) * 16, 16, 16, 16, 280 - 48 + 8, 56 + i * 48);
            }

            if (save->getEquipment(MASQUE)) {
                WindowManager::getInstance()->draw(inventaire, 16, 136, 16, 16, 260, 56 + i * 48);
            } else if (save->getEquipment(MASQUE_VIDE)) {
                WindowManager::getInstance()->draw(inventaire, 0, 136, 16, 16, 260 + 8, 56 + i * 48);
            }

            if (save->getEquipment(TRIFORCE)) {
                WindowManager::getInstance()->draw(stuff, 34, 48, 17, 16, 280, 56 + i * 48);
            }
        }
    }
}

void MainMenu::drawPage() {
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
    drawCadre(168, 192, 136, 32);

    texts[1]->display(44, 56);
    texts[2]->display(44, 104);
    texts[3]->display(44, 152);

    // options
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[4]->getLength() * letterSize;
    texts[4]->display(16 + (136 - size) / 2, 200);

    // records
    size = texts[5]->getLength() * letterSize;
    texts[5]->display(168 + (136 - size) / 2, 200);

    drawSaves();
}

void MainMenu::drawLoad() {
    int letterSize = TextManager::getInstance()->getWSpace();
    drawCadre(104, 84, 112, 72);
    // load
    int size = texts[6]->getLength() * letterSize;
    texts[6]->display(104 + (112 - size) / 2, 9 + 84);

    // erase
    size = texts[7]->getLength() * letterSize;
    texts[7]->display(104 + (112 - size) / 2, 29 + 84);

    // cancel
    size = texts[8]->getLength() * letterSize;
    texts[8]->display(104 + (112 - size) / 2, 49 + 84);
}

void MainMenu::drawConfirm() {
    int letterSize = TextManager::getInstance()->getWSpace();
    drawCadre(104, 84, 112, 72);
    // delete
    int size = texts[9]->getLength() * letterSize;
    texts[9]->display(104 + (112 - size) / 2, 9 + 84);

    // yes
    size = texts[10]->getLength() * letterSize;
    texts[10]->display(104 + (112 - size) / 2, 29 + 84);

    // no
    size = texts[11]->getLength() * letterSize;
    texts[11]->display(104 + (112 - size) / 2, 49 + 84);
}

void MainMenu::draw() {
    drawPage();

    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21, 26 + 152 * column, 53 + 48 * line);

    if (load) {
        drawLoad();
        WindowManager::getInstance()->draw(fairy, 0, 0, 16, 16, 112, 93 + 20 * subLine);
    }
    if (confirm) {
        drawConfirm();
        WindowManager::getInstance()->draw(fairy, 0, 0, 16, 16, 112, 113 + 20 * subLine);
    }
}
