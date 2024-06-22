#include "AnimationInGame.h"

#include "../../../game/MainController.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"

// #include "../objects/Pnj.h"

AnimationInGame::AnimationInGame() : id(0), anim(0), running(false)
{
    image = ResourceManager::getInstance()->loadImage("data/images/intro/opening.png");
    oniLink = 0;
}

AnimationInGame::~AnimationInGame()
{
    ResourceManager::getInstance()->free(image);
    delete oniLink;
}

void AnimationInGame::testAnim()
{

    if (running)
    {
        return;
    }

    Avancement avancement = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAvancement();

    link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    switch (avancement)
    {
    case AV_START:
        startAnim(1);
        break;
    case AV_INTRO_OK:
        startAnim(8);
        break;
    case AV_TUTO_OK:
        if (map->getId() == 1)
        {
            startAnim(2);
        }
        break;
    case AV_ONI_LINK_FREE:
        if (map->getId() < 15)
        {
            MainController::getInstance()->getGameController()->displayText(346);
        }
        break;
    case AV_GANON_VU:
        if (map->getId() < 15)
        {
            MainController::getInstance()->getGameController()->displayText(359);
        }
        break;
    default:
        break;
    }
}

void AnimationInGame::startAnim(int i)
{
    id = i;

    link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    camera = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCamera();

    lmap = false;
    lcamera = false;
    llink = false;

    Save *save;

    switch (id)
    {
    case 1:
        AudioManager::getInstance()->stopMusic();
        MainController::getInstance()->getGameController()->displayText(89);
        break;
    case 2:
        MainController::getInstance()->getGameController()->displayText(174);
        lmap = true;
        break;
    case 3:
        AudioManager::getInstance()->playMusic(28);
        delete oniLink;
        save = new Save(-1);
        save->setOniLink(true);
        save->setBouclier(link->getBouclier());
        save->setDirection(S);
        oniLink = new Link(save, MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMetronome());
        delete save;
        break;
    case 4:
        AudioManager::getInstance()->stopMusic();
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        break;
    case 6:
        AudioManager::getInstance()->playMusic(28);
        break;
    case 7:
        AudioManager::getInstance()->stopMusic();
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        break;
    default:
        break;
    }

    running = true;
    anim = 0;
}

void AnimationInGame::loop()
{
    if (!running)
    {
        return;
    }
    switch (id)
    {
    case 1:
        if (anim == 0)
        {
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            circularTransition.start(9 * 16 + 8, 4 * 16 + 8);
        }
        else if (anim == 160 && circularTransition.isWaiting())
        {
            circularTransition.restart(9 * 16 + 8, 4 * 16 + 8);
            anim++;
        }
        else if (circularTransition.isAchieved())
        {
            MainController::getInstance()->getGameController()->displayText(92);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setAvancement(AV_INTRO_OK);
            AudioManager::getInstance()->playMusic(21);
            running = false;
        }
        else if (circularTransition.isRunning())
        {
            circularTransition.loop();
        }
        if (anim != 160)
        {
            anim++;
        }
        break;
    case 3:
        if (anim != 48)
        {
            anim++;
            link->setX(link->getX() + 1);
            if (anim == 48)
            {
                MainController::getInstance()->getGameController()->displayText(343);
            }
        }
        break;
    case 4:
        anim++;
        if (anim == 160)
        {
            AudioManager::getInstance()->playMusic(20);
            MainController::getInstance()->getGameController()->displayText(316);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setAvancement(AV_ONI_LINK_FREE);
            delete oniLink;
            oniLink = 0;
            running = false;
        }
        break;
    case 5:
        MainController::getInstance()->getGameController()->displayText(349);
        running = false;
        break;
    case 6:
        if (link->getStatus()->isOniLink())
        {
            MainController::getInstance()->getGameController()->displayText(357);
        }
        else
        {
            MainController::getInstance()->getGameController()->displayText(351);
        }
        running = false;
        break;
    case 7:
        anim++;
        if (anim == 160)
        {
            AudioManager::getInstance()->playMusic(33);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setAvancement(AV_GANON_VU);
            running = false;
        }
        break;
    case 8:
        MainController::getInstance()->getGameController()->displayText(367);
        running = false;
        break;
    }
}

void AnimationInGame::draw()
{
    if (!running)
    {
        return;
    }

    switch (id)
    {
    case 1:
        if (circularTransition.isRunning() && anim > 160)
        {
            circularTransition.draw();
        }
        else
        {
            WindowManager::getInstance()->draw(image, 0, 0, 320, 240, 0, 0);
        }
        break;
    case 3:
        oniLink->drawForMenu(link->getX() - anim * 2 - map->getBounds()->getX(), link->getY() - map->getBounds()->getY());
        break;
    case 4:
        oniLink->drawForMenu(link->getX() - 96 - map->getBounds()->getX(), link->getY() - map->getBounds()->getY());
        break;
    default:
        break;
    }
}

void AnimationInGame::drawAfterHud()
{
    if (!running)
    {
        return;
    }

    switch (id)
    {
    case 1:
        if (!circularTransition.isRunning() || anim <= 160)
        {
            WindowManager::getInstance()->draw(image, 0, 0, 320, 100, 0, 0);
        }
        break;
    default:
        break;
    }
}

int AnimationInGame::getSpecialMusicId()
{
    if (!running)
    {
        return 0;
    }

    switch (id)
    {
    // case 1 : return 2;
    default:
        return 0;
    }
}

bool AnimationInGame::isRunning()
{
    return running;
}

bool AnimationInGame::loopMap()
{
    return !running || lmap;
}

bool AnimationInGame::loopCamera()
{
    return !running || lcamera;
}

bool AnimationInGame::loopLink()
{
    return !running || llink;
}

void AnimationInGame::stop()
{
    running = false;
}
