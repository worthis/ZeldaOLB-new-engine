#include "Menu.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

Menu::Menu() : i(0), j(0), step(MENU_OFF), anim(0), link(0)
{
    imageMenu = ResourceManager::getInstance()->loadImage("data/images/status/bord.png", true);
    imageCoeur = ResourceManager::getInstance()->loadImage("data/images/status/coeur.png", true);
    imageChiffres = ResourceManager::getInstance()->loadImage("data/images/status/chiffres.png", true);
    imageStuff = ResourceManager::getInstance()->loadImage("data/images/status/stuff.png");
    imageStatus = ResourceManager::getInstance()->loadImage("data/images/status/status.png", true);
    metronome = new Metronome(2, ANIM_REFRESH * 3);
    metronome->reset();
    for (int i = 0; i < 13; i++)
    {
        texts[i] = 0;
    }
    magie = false;
    oniLink = false;
    oniLinkable = false;
}

Menu::~Menu()
{
    ResourceManager::getInstance()->free(imageMenu);
    ResourceManager::getInstance()->free(imageCoeur);
    ResourceManager::getInstance()->free(imageChiffres);
    ResourceManager::getInstance()->free(imageStuff);
    ResourceManager::getInstance()->free(imageStatus);
    delete metronome;
    for (int i = 0; i < 13; i++)
    {
        delete texts[i];
    }
}

void Menu::init()
{
    for (int ii = 0; ii < 8; ii++)
    {
        delete texts[ii];
        texts[ii] = TextManager::getInstance()->getText(139 + ii);
    }

    initFromSelectedStuff();
    step = MENU_OFF;
    anim = 0;
}

void Menu::handleActions(Action *action)
{
    if (action->isAction(INVENTAIRE))
    {
        stop();
        return;
    }
    if (!link->isAbleToChangeStuff() || step != MENU_ON)
    {
        return;
    }

    bool hasMoved = false;
    if (action->isAction(PUSH_UP))
    {
        if (--j < 0)
            j = 3;
        hasMoved = true;
    }
    if (action->isAction(PUSH_DOWN))
    {
        if (++j > 3)
            j = 0;
        hasMoved = true;
    }
    if (action->isAction(PUSH_LEFT))
    {
        if (--i < 0)
            i = 2;
        hasMoved = true;
    }
    if (action->isAction(PUSH_RIGHT))
    {
        if (++i > 2)
            i = 0;
        hasMoved = true;
    }

    if (hasMoved)
    {
        metronome->reset();
        updateSelectedStuff();
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void Menu::loop()
{
    if (step == MENU_START)
    {
        if (++anim == 8)
        {
            step = MENU_ON;
            metronome->reset();
        }
    }
    else if (step == MENU_END)
    {
        if (--anim == 0)
        {
            step = MENU_OFF;
            MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        }
    }
    metronome->loop();
}

void Menu::draw()
{
    int df = 200 - anim * 25;
    drawObjects(df);
    drawHearts(df);
    drawLink(df);
    drawGraals(df);
    drawStatus(df);
}

void Menu::drawObjects(int df)
{

    drawCadre(16 - df, 16, 16 * 7, 16 * 9);

    if (link->getInventory()->hasObject(ARC_FEE))
    {
        link->getInventory()->draw(ARC_FEE, 32 - df, 32);
    }
    else if (link->getInventory()->hasObject(ARC))
    {
        link->getInventory()->draw(ARC, 32 - df, 32);
    }

    if (link->getInventory()->hasObject(GRAPPIN))
    {
        link->getInventory()->draw(GRAPPIN, 64 - df, 32);
    }

    if (link->getInventory()->hasObject(BOMBES) && link->getStatus()->getBombs())
    {
        link->getInventory()->draw(BOMBES, 96 - df, 32);
    }

    if (link->getInventory()->hasObject(BAGUETTE_FEU))
    {
        link->getInventory()->draw(BAGUETTE_FEU, 32 - df, 64);
    }

    if (link->getInventory()->hasObject(BAGUETTE_GLACE))
    {
        link->getInventory()->draw(BAGUETTE_GLACE, 64 - df, 64);
    }

    if (link->getInventory()->hasObject(LANTERNE))
    {
        link->getInventory()->draw(LANTERNE, 96 - df, 64);
    }

    if (link->getInventory()->hasObject(MARTEAU))
    {
        link->getInventory()->draw(MARTEAU, 32 - df, 96);
    }

    if (link->getInventory()->hasObject(OCARINA))
    {
        link->getInventory()->draw(OCARINA, 64 - df, 96);
    }

    if (link->getInventory()->hasObject(MASQUE))
    {
        link->getInventory()->draw(MASQUE, 96 - df, 96);
    }
    else if (link->getInventory()->hasObject(MASQUE_VIDE))
    {
        link->getInventory()->draw(MASQUE_VIDE, 96 - df, 96);
    }

    if (link->getInventory()->hasObject(FLACON_1))
    {
        link->getInventory()->draw(FLACON_1, 32 - df, 128);
    }

    if (link->getInventory()->hasObject(FLACON_2))
    {
        link->getInventory()->draw(FLACON_2, 64 - df, 128);
    }

    if (link->getInventory()->hasObject(FLACON_3))
    {
        link->getInventory()->draw(FLACON_3, 96 - df, 128);
    }

    if (df == 0 && !metronome->getValue())
    {
        if (link->isAbleToChangeStuff())
        {
            WindowManager::getInstance()->draw(imageMenu, 51, 3, 26, 26, 32 - 5 + i * 32, 32 - 5 + j * 32);
        }
        else
        {
            WindowManager::getInstance()->draw(imageMenu, 83, 3, 26, 26, 32 - 5 + i * 32, 32 - 5 + j * 32);
        }
    }
}

void Menu::drawHearts(int df)
{
    drawCadre(16 * 16, 16 * 11 + df, 16 * 3, 16 * 3);
    WindowManager::getInstance()->draw(imageCoeur, link->getInventory()->nbQuartCoeur() * 16, 0, 16, 16, 16 * 17, 16 * 12 + df);
}

void Menu::drawLink(int df)
{
    drawCadre(16 - df, 16 * 11, 16 * 3, 16 * 3);
    link->drawForMenu(32 - df, 186);
}

void Menu::drawGraals(int df)
{
    drawCadre(16 * 5, 16 * 11 + df, 16 * 10, 16 * 3);

    texts[0]->display(84, 180 + df);

    for (int i = 0; i < NB_GRAALS; i++)
    {
        WindowManager::getInstance()->draw(imageStuff,
                                           link->getInventory()->hasGraal(i) ? 0 : 17, 48, 16, 16,
                                           94 + (i * 29), 198 + df);
    }
}

void Menu::drawStatus(int df)
{
    int letterSize = TextManager::getInstance()->getWSpace();

    drawCadre(16 * 9 + df, 16, 16 * 10, 16 * 9);

    // status
    texts[1]->display(148 + df, 20);

    int dstY = 36;
    if (!magie || !oniLinkable)
    {
        dstY += 8;
    }

    // life
    texts[2]->display(148 + df, dstY);
    int size = texts[2]->getLength() * letterSize;
    texts[8]->display(148 + df + size + letterSize, dstY);
    dstY += 16;

    // magic
    if (magie)
    {
        texts[3]->display(148 + df, dstY);
        size = texts[3]->getLength() * letterSize;
        texts[9]->display(148 + df + size + letterSize, dstY);
        dstY += 16;
    }

    // onilink
    if (oniLinkable)
    {
        texts[4]->display(148 + df, dstY);
        size = texts[4]->getLength() * letterSize;
        texts[10]->display(148 + df + size + letterSize, dstY);
        dstY += 16;
    }

    // force
    texts[5]->display(148 + df, dstY);
    size = texts[5]->getLength() * letterSize;
    texts[11]->display(148 + df + size + letterSize, dstY);
    dstY += 16;

    // defense
    texts[6]->display(148 + df, dstY);
    size = texts[6]->getLength() * letterSize;
    texts[12]->display(148 + df + size + letterSize, dstY);
    dstY += 16;

    // time
    texts[7]->display(148 + df, dstY);
    size = texts[7]->getLength() * letterSize;
    ostringstream oss;
    int time = MainController::getInstance()->getGameController()->getTime();
    int hours = time / 3600;
    int minutes = (time - hours * 3600) / 60;
    int seconds = time % 60;
    if (hours < 10)
        oss << "0";
    oss << hours << ":";
    if (minutes < 10)
        oss << "0";
    oss << minutes << ":";
    if (seconds < 10)
        oss << "0";
    oss << seconds;
    Text *txt = new Text(oss.str());
    txt->display(148 + df + size + letterSize, dstY);
    delete txt;

    // sword
    int srcX = 0;
    if (link->getEpee())
    {
        srcX = (link->getEpee() - 1) * 16;
        if (oniLink)
        {
            if (oniLinkable)
            {
                srcX = 80;
            }
            else
            {
                srcX = 96;
            }
        }
        WindowManager::getInstance()->draw(imageStuff, srcX, 16, 16, 16, 156 + df, 136);
    }

    // shield
    if (link->getBouclier())
    {
        srcX = (link->getBouclier() - 1) * 16;
        if (oniLink)
        {
            if (oniLinkable)
            {
                srcX = 48;
            }
            else
            {
                srcX = 64;
            }
        }
        WindowManager::getInstance()->draw(imageStuff, srcX, 32, 16, 16, 176 + df, 136);
    }

    // tunique
    srcX = (link->getTunique() - 1) * 16;
    if (oniLink)
    {
        srcX = 48;
    }
    WindowManager::getInstance()->draw(imageStuff, srcX, 0, 16, 16, 196 + df, 136);

    // bottes
    if (link->getInventory()->hasObject(BOTTES))
    {
        WindowManager::getInstance()->draw(imageStuff, 64, 0, 16, 16, 216 + df, 136);
    }

    // gants
    if (link->getInventory()->hasObject(GANTS_2))
    {
        link->getInventory()->draw(GANTS_2, 236 + df, 136);
    }
    else if (link->getInventory()->hasObject(GANTS))
    {
        link->getInventory()->draw(GANTS, 236 + df, 136);
    }

    // palmes
    if (link->getInventory()->hasObject(PALMES))
    {
        link->getInventory()->draw(PALMES, 256 + df, 136);
    }

    // bombes
    if (link->getInventory()->hasObject(BOMBES))
    {
        WindowManager::getInstance()->draw(imageStuff, 80, 0, 16, 16, 276 + df, 136);
    }
}

void Menu::drawCadre(int x, int y, int w, int h)
{
    WindowManager::getInstance()->draw(imageMenu, 0, 0, 16, 16, x, y);
    WindowManager::getInstance()->draw(imageMenu, 32, 0, 16, 16, x + w - 16, y);
    WindowManager::getInstance()->draw(imageMenu, 0, 32, 16, 16, x, y + h - 16);
    WindowManager::getInstance()->draw(imageMenu, 32, 32, 16, 16, x + w - 16, y + h - 16);

    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        WindowManager::getInstance()->draw(imageMenu, 16, 0, 16, 16, i, y);
        WindowManager::getInstance()->draw(imageMenu, 16, 32, 16, 16, i, y + h - 16);
    }

    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        WindowManager::getInstance()->draw(imageMenu, 0, 16, 16, 16, x, j);
        WindowManager::getInstance()->draw(imageMenu, 32, 16, 16, 16, x + w - 16, j);
    }

    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        for (int j = y + 16; j < y + h - 16; j += 16)
        {
            WindowManager::getInstance()->draw(imageMenu, 16, 16, 16, 16, i, j);
        }
    }
}

void Menu::drawNombre(int val, int x, int y, int nb, bool green)
{
    int val2;
    int srcX;
    int srcY;
    int dstX = x;

    // si on commence par les centaines
    if (nb >= 3)
    {
        val2 = val / 100;
        srcX = (val2 % 5) * 8;
        srcY = ((int)(val2 / 5)) * 8;
        if (green)
            srcY += 16;
        WindowManager::getInstance()->draw(imageChiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    // les dizaines
    if (nb >= 2)
    {
        val2 = (val % 100) / 10;
        srcX = (val2 % 5) * 8;
        srcY = ((int)(val2 / 5)) * 8;
        if (green)
            srcY += 16;
        WindowManager::getInstance()->draw(imageChiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    // unit�es
    val2 = val % 10;
    srcX = (val2 % 5) * 8;
    srcY = ((int)(val2 / 5)) * 8;
    if (green)
        srcY += 16;
    WindowManager::getInstance()->draw(imageChiffres, srcX, srcY, 8, 8, dstX, y);
}

void Menu::start()
{
    if (step == MENU_OFF)
    {
        link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
        AudioManager::getInstance()->playSound(TS_MENU1);
        step = MENU_START;
        anim = 0;

        for (int i = 8; i < 13; i++)
        {
            delete texts[i];
            texts[i] = 0;
        }
        ostringstream oss;
        int vie = link->getStatus()->getLife();
        int vieMax = link->getStatus()->getMaxLife();
        if (vie < 10)
            oss << "0";
        oss << vie << "/";
        if (vieMax < 10)
            oss << "0";
        oss << vieMax;
        texts[8] = new Text(oss.str());

        oss.str("");
        int magic = link->getStatus()->getMagic();
        int magicMax = link->getStatus()->getMaxMagic();
        magie = magicMax;
        if (magie)
        {
            if (magic < 10)
                oss << "0";
            oss << magic << "/";
            if (magicMax < 10)
                oss << "0";
            oss << magicMax;
            texts[9] = new Text(oss.str());
        }

        oss.str("");
        oniLink = link->getStatus()->isOniLink();
        oniLinkable = link->getStatus()->isOniLinkable();
        if (oniLinkable)
        {
            int oniValue = link->getStatus()->getValueOni();
            int oniMax = link->getStatus()->getMaxOni();
            if (oniValue < 10)
                oss << "0";
            oss << oniValue << "/";
            if (oniMax < 10)
                oss << "0";
            oss << oniMax;
            texts[10] = new Text(oss.str());
        }

        oss.str("");
        oss << link->getForce();
        texts[11] = new Text(oss.str());

        oss.str("");
        oss << link->getDefense();
        texts[12] = new Text(oss.str());
    }
}

void Menu::stop()
{
    if (step == MENU_START || step == MENU_ON)
    {
        AudioManager::getInstance()->playSound(TS_MENU2);
        step = MENU_END;
    }
}

void Menu::initFromSelectedStuff()
{
    Equipment current = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getCurrent();
    int tmp = 0;
    switch (current)
    {
    case ARC:
    case ARC_FEE:
        tmp = 0;
        break;
    case GRAPPIN:
        tmp = 1;
        break;
    case BOMBES:
        tmp = 2;
        break;
    case BAGUETTE_FEU:
        tmp = 3;
        break;
    case BAGUETTE_GLACE:
        tmp = 4;
        break;
    case LANTERNE:
        tmp = 5;
        break;
    case MARTEAU:
        tmp = 6;
        break;
    case OCARINA:
        tmp = 7;
        break;
    case MASQUE_VIDE:
    case MASQUE:
        tmp = 8;
        break;
    case FLACON_1:
        tmp = 9;
        break;
    case FLACON_2:
        tmp = 10;
        break;
    case FLACON_3:
        tmp = 11;
        break;
    default:
        tmp = 0;
    }
    i = tmp % 3;
    j = tmp / 3;
}

Equipment Menu::getSelectedStuff()
{
    int tmp = i + j * 3;
    switch (tmp)
    {
    case 0:
        if (link->getInventory()->hasObject(ARC_FEE))
            return ARC_FEE;
        return ARC;
    case 1:
        return GRAPPIN;
    case 2:
        return BOMBES;
    case 3:
        return BAGUETTE_FEU;
    case 4:
        return BAGUETTE_GLACE;
    case 5:
        return LANTERNE;
    case 6:
        return MARTEAU;
    case 7:
        return OCARINA;
    case 8:
        if (link->getInventory()->hasObject(MASQUE))
            return MASQUE;
        return MASQUE_VIDE;
    case 9:
        return FLACON_1;
    case 10:
        return FLACON_2;
    case 11:
        return FLACON_3;
    }
    return ARC;
}

void Menu::updateSelectedStuff()
{
    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->setCurrent(getSelectedStuff());
}
