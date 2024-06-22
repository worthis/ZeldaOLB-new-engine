#include "Scene.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../config/ConfigurationManager.h"
#include "../../MainController.h"

Scene::Scene() : step(SCENE_MAIN), save(0), map(0), link(0), hud(0), avancement(AV_START)
{
    metronome = new Metronome(120, ANIM_REFRESH);
    metronome->reset();

    filterForest = ResourceManager::getInstance()->loadImage("data/images/tileset/foret.png");

    ostringstream os;
    for (int i = 0; i < 3; i++)
    {
        os << (i + 1);
        string filenameRain = "data/images/tileset/pluie" + os.str() + ".png";
        filterRain[i] = ResourceManager::getInstance()->loadImage(filenameRain, true);
        string filenameSky = "data/images/tileset/fond" + os.str() + ".png";
        filterSky[i] = ResourceManager::getInstance()->loadImage(filenameSky);
        os.str("");
    }
    planeAndUfo = ResourceManager::getInstance()->loadImage("data/images/tileset/ciel.png", true);
    lightning = ResourceManager::getInstance()->loadImage("data/images/tileset/eclair.png", true);

    displayPlane = false;
    displayUfo = false;
    displayLightning1 = false;
    displayLightning2 = false;
}

Scene::~Scene()
{
    delete metronome;
    delete map;
    delete link;
    delete hud;

    ResourceManager::getInstance()->free(filterForest);
    for (int i = 0; i < 3; i++)
    {
        ResourceManager::getInstance()->free(filterRain[i]);
        ResourceManager::getInstance()->free(filterSky[i]);
    }
}

void Scene::init(Save *sv)
{
    save = sv;

    delete map;
    delete link;
    delete hud;

    avancement = sv->getAvancement();

    for (int j = 0; j < COFFRES_MAX_SIZE; j++)
    {
        for (int i = 0; i < NB_COFFRES; i++)
        {
            coffres[i][j] = sv->getCoffre(i, j);
        }
    }
    coffres[0][15] = 0; // reset asile

    for (int j = 0; j < MAX_ROOMS_Y; j++)
    {
        for (int i = 0; i < MAX_ROOMS_X; i++)
        {
            for (int d = 0; d < NB_DONJON; d++)
            {
                rooms[d][i][j] = sv->getRooms(d, i, j);
            }
        }
    }

    for (int i = 0; i < NB_MONSTERS; i++)
    {
        monsters[i] = sv->getMonsters(i);
    }

    link = new Link(save, metronome);
    hud = new Hud(link->getStatus(), link->getInventory(), ConfigurationManager::getInstance()->isFrench());

    map = new Map(save->getMap(), metronome);
    map->load();

    animation.testAnim();
    map->launch();

    if (map->getId() == 26 && map->getEtage() == -2)
    {
        MainController::getInstance()->getGameController()->displayText(358);
    }
    else if (map->getId() < 15 && avancement == AV_ONI_LINK_FREE)
    {
        MainController::getInstance()->getGameController()->displayText(346);
    }
    else if (map->getId() == 18 && link->getEpee() > 1)
    {
        MainController::getInstance()->getGameController()->displayText(132);
    }
    else if (map->getId() >= 15 && map->getId() < 23)
    {
        MainController::getInstance()->getGameController()->displayText(124 + map->getId() - 15);
    }
    else if (map->getId() >= 23 && map->getId() < 29)
    {
        MainController::getInstance()->getGameController()->displayText(133 + map->getId() - 23);
    }

    // open door if needed
    if (map->getId() < 15)
    {
        int x = link->getX();
        int y = link->getY();
        if (map->getSol(x, y + 8 - 1) == 468 || map->getSol(x, y + 8 - 1) == 789 || map->getSol(x, y + 8 - 1) == 790)
        {
            map->ouvrePorteMaison(x, y);
        }
        if (map->getSol(x, y + 8 - 1) == 1362)
        {
            map->ouvrePorte(x / 16, y / 16, 0);
        }
        if (map->getSol(x, y + 8 - 1) == 1363)
        {
            map->ouvrePorte((x - 16) / 16, y / 16, 0);
        }
    }
    link->startNewMap();

    fixCameraBounds();
}

void Scene::fixCameraBounds()
{
    BoundingBox *bounds = map->getBounds();
    camera.setBounds(bounds->getX(), bounds->getY(), bounds->getW(), bounds->getH());

    int bx = link->getX() + link->getW() / 2 - 160;
    if (bx < 0)
        bx = 0;
    if (bx + 320 > bounds->getX() + bounds->getW())
        bx = bounds->getX() + bounds->getW() - 320;
    int by = link->getY() + link->getH() / 2 - 116;
    if (by < 0)
        by = 0;
    if (by + 240 > bounds->getY() + bounds->getH())
        by = bounds->getY() + bounds->getH() - 240;
    camera.setBox(bx, by, 320, 240);
}

void Scene::saveData()
{

    save->setMap(map->getId());
    save->setAvancement(avancement);
    for (int j = 0; j < COFFRES_MAX_SIZE; j++)
    {
        for (int i = 0; i < NB_COFFRES; i++)
        {
            save->setCoffre(i, j, coffres[i][j]);
        }
    }

    for (int j = 0; j < MAX_ROOMS_Y; j++)
    {
        for (int i = 0; i < MAX_ROOMS_X; i++)
        {
            for (int d = 0; d < NB_DONJON; d++)
            {
                save->setRooms(d, i, j, rooms[d][i][j]);
            }
        }
    }

    for (int i = 0; i < NB_MONSTERS; i++)
    {
        save->setMonsters(i, monsters[i]);
    }

    link->saveData(save);
}

void Scene::handleActions(Action *action)
{
    switch (step)
    {
    case SCENE_MAIN:

        if (animation.isRunning())
        {
            break;
        }

        if (link->getStatus()->getVirtualLife() > 0 && action->isAction(INVENTAIRE))
        {
            MainController::getInstance()->getGameController()->setStep(GAME_MENU);
            return;
        }
        if (link->getStatus()->getVirtualLife() > 0 && action->isAction(DISPLAY_MAP) && map->getId() < 29)
        {
            if (map->getId() >= 15 || link->getInventory()->hasObject(CARTE))
            {
                MainController::getInstance()->getGameController()->displayMap(map->getId());
                AudioManager::getInstance()->playSound(TS_MENU1);
                return;
            }
        }
        if (link->getStatus()->getVirtualLife() > 0 && action->isAction(AIDE))
        {
            MainController::getInstance()->getGameController()->setStep(GAME_HELP);
            AudioManager::getInstance()->playSound(TS_MENU1);
            return;
        }
        if (link->getStatus()->getVirtualLife() > 0 && action->isAction(MONSTERS) && link->getInventory()->hasObject(ENCYCLOPEDIE))
        {
            MainController::getInstance()->getGameController()->setStep(GAME_MONSTERS);
            AudioManager::getInstance()->playSound(TS_MENU1);
            return;
        }

        boxOnLink = !action->isAction(CAMERA);
        if (!boxOnLink)
        {
            camera.handleAction(action, link->getX() + link->getW() / 2, link->getY() + link->getH() / 2 + 4);
            action->reset();
        }
        link->handleAction(action);

        break;
    default:
        break;
    }
}

void Scene::loop()
{

    switch (step)
    {
    case SCENE_MAIN:
        animation.loop();
        metronome->loop();
        if (animation.loopMap())
        {
            // armee ganon
            if (map->getId() == 9 && avancement == AV_ARMEE_UP)
            {
                hud->setBossLife(map->nbEnnemis(), 20);
            }
            // plane and ufo
            if (map->getId() == 14 || map->getId() == 25 || map->getId() == 28)
            {
                if (!displayPlane && !displayUfo)
                {
                    int tmp = (int)((float)rand() / RAND_MAX * 36000);
                    if (tmp == 42)
                    {
                        displayUfo = true;
                        planeX = -19;
                    }
                    else if (tmp < 4)
                    {
                        displayPlane = true;
                        planeX = -31;
                    }
                }
                else
                {
                    planeX++;
                    if (planeX >= 320)
                    {
                        displayUfo = false;
                        displayPlane = false;
                    }
                }
            }
            // lightning
            if (map->getId() == 28)
            {
                if (displayLightning1)
                {
                    lightning1Duration++;
                    if (lightning1Duration >= 12)
                    {
                        displayLightning1 = false;
                    }
                }
                if (displayLightning2)
                {
                    lightning2Duration++;
                    if (lightning2Duration >= 12)
                    {
                        displayLightning2 = false;
                    }
                }
                if (!displayLightning1 || !displayLightning2)
                {
                    int tmp = (int)((float)rand() / RAND_MAX * 90);
                    if (tmp == 7 && !displayLightning1)
                    {
                        lightning1X = (int)((float)rand() / RAND_MAX * 288);
                        if (!displayLightning2 || lightning1X + 32 < lightning2X || lightning1X > lightning2X + 32)
                        {
                            displayLightning1 = true;
                            lightning1Duration = 0;
                        }
                    }
                    if (tmp == 12 && !displayLightning2)
                    {
                        lightning2X = (int)((float)rand() / RAND_MAX * 288);
                        if (!displayLightning1 || lightning2X + 32 < lightning1X || lightning2X > lightning1X + 32)
                        {
                            displayLightning2 = true;
                            lightning2Duration = 0;
                        }
                    }
                }
            }
            map->loop();
        }
        if (animation.loopLink())
            link->loop();

        if (link->hasMoved())
        {
            map->testAnim(link->getX(), link->getY(), link->getDirection());
        }

        if (animation.loopCamera())
        {
            if (!camera.isManuel())
            {
                if (boxOnLink)
                {
                    camera.moveTo(link->getX() + link->getW() / 2, link->getY() + link->getH() / 2 + 4, 4);
                }
            }
            camera.loop();
        }
        hud->loop();

        if (!animation.isRunning())
            testTransition();
        break;
    case SCENE_TRANSITION_LIVE:
        transition.loop();
        if (transition.isWaiting())
        {
            link->revit();
            fixCameraBounds();
            camera.loop();
            hud->loop();
            hud->reset();
            BoundingBox *box = camera.getBoundingBox();
            transition.restart(link->getX() + 8 - box->getX(), link->getY() + 16 - box->getY());
        }
        else if (transition.isAchieved())
        {
            transition.reset();
            step = SCENE_MAIN;
        }
        break;
    case SCENE_ONLY_LINK:
        link->loop();

        camera.setPosition(link->getX() + link->getW() / 2, link->getY() + link->getH() / 2 + 4);
        camera.loop();
        hud->loop();
        break;
    default:
        break;
    }
}

void Scene::draw()
{

    BoundingBox *box = camera.getBoundingBox();

    List toDraw;
    toDraw.add((Listable *)link);

    if (map->getId() == 14 || map->getId() == 25)
    {
        if (avancement < AV_ARMEE_DOWN)
        {
            WindowManager::getInstance()->draw(filterSky[0], 0, 0, 320, 240, 0, 0);
        }
        else
        {
            WindowManager::getInstance()->draw(filterSky[1], 0, 0, 320, 240, 0, 0);
        }
    }
    if (map->getId() == 28)
    {
        WindowManager::getInstance()->draw(filterSky[2], 0, 0, 320, 240, 0, 0);
        if (displayLightning1)
        {
            WindowManager::getInstance()->draw(lightning, 32 * (lightning1Duration / 4), 0, 32, 64, lightning1X, 0);
        }
        if (displayLightning2)
        {
            WindowManager::getInstance()->draw(lightning, 32 * (lightning2Duration / 4), 64, 32, 64, lightning2X, 0);
        }
    }
    if (map->getId() == 14 || map->getId() == 25 || map->getId() == 28)
    {
        if (displayPlane)
        {
            WindowManager::getInstance()->draw(planeAndUfo, 31 * (metronome->getValue() % 2), 11, 31, 13, planeX, 32);
        }
        else if (displayUfo)
        {
            WindowManager::getInstance()->draw(planeAndUfo, 19 * (metronome->getValue() % 4), 0, 19, 11, planeX, 32);
        }
    }

    map->draw(&toDraw, box);

    // forest effect
    if (map->getId() == 1)
    {
        WindowManager::getInstance()->draw(filterForest, (box->getX() / 2) % 256, (box->getY() / 2) % 256, 320, 240, 0, 0);
    }
    else if ((map->getId() == 7 || map->getId() == 8) && avancement >= AV_ZELDA_CHEZ_PIT && avancement < AV_FILLE_MAIRE_SAUVEE)
    {
        WindowManager::getInstance()->draw(filterRain[metronome->getValue() % 3], 0, 0, 320, 240, 0, 0);
    }

    animation.draw();

    if (step == SCENE_TRANSITION_LIVE)
    {
        transition.draw();
    }

    hud->draw();

    animation.drawAfterHud();
}

bool Scene::checkCollisions(BoundingBox *box, Collisionable *object, bool checkEnnemis, bool ignoreNotIdle, bool withAvoid, bool onlyBox,
                            bool checkObjects, int safeX, int safeY, int safeW, int safeH, bool checkDanger)
{
    return map->checkCollisions(box, object, checkEnnemis, ignoreNotIdle, withAvoid, onlyBox, checkObjects, safeX, safeY, safeW, safeH, checkDanger);
}
bool Scene::checkCollisionsWithLink(BoundingBox *box)
{
    return !box->intersect(link->getBoundingBox());
}

Map *Scene::getMap()
{
    return map;
}

Link *Scene::getLink()
{
    return link;
}

Metronome *Scene::getMetronome()
{
    return metronome;
}

Camera *Scene::getCamera()
{
    return &camera;
}

Hud *Scene::getHud()
{
    return hud;
}

AnimationInGame *Scene::getAnimationInGame()
{
    return &animation;
}

Avancement Scene::getAvancement()
{
    return avancement;
}

void Scene::setAvancement(Avancement av)
{
    avancement = av;
}

bool Scene::testDegatOnLink(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect)
{
    if (box->intersect(link->getBoundingBox()))
    {
        return link->underAttack(dir, force, type, effect);
    }
    return false;
}

bool Scene::testDegat(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis)
{
    return map->testDegat(box, dir, force, type, effect, onEnnemis);
}

void Scene::testTransition()
{
    if (map->testTransition(link->getX(), link->getY()))
    {
        MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_MAP);
    }
    else if (map->testTeleport(link->getX(), link->getY()))
    {
        MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
    }
    else if (map->testInnerTransition(link->getX(), link->getY()))
    {
        MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_ROOM);
    }
}

void Scene::setStep(SceneStep s)
{
    step = s;
    if (step == SCENE_TRANSITION_LIVE)
    {
        BoundingBox *box = camera.getBoundingBox();
        transition.start(link->getX() + 8 - box->getX(), link->getY() + 16 - box->getY());
    }
}

void Scene::setMap(Map *mp)
{
    delete map;
    map = mp;

    camera.setBounds(0, 0, map->getW(), map->getH());

    int bx = link->getX() + link->getW() / 2 - 160;
    if (bx < 0)
        bx = 0;
    if (bx + 320 > map->getW())
        bx = map->getW() - 320;
    int by = link->getY() + link->getH() / 2 - 120;
    if (by < 0)
        by = 0;
    if (by + 240 > map->getH())
        by = map->getH() - 240;
    camera.setBox(bx, by, 320, 240);
}

bool Scene::permuteBlocs(int step)
{
    // 0 = orange up - blue down
    map->permuteBlocs(step);

    if (checkCollisions(link->getBoundingBox(), (Collisionable *)link, false, false, false, false, false))
    {
        return true;
    }
    else
    {
        map->permuteBlocs(step == 0 ? 1 : 0);
        return false;
    }
}

int Scene::getCoffre(int i, int j)
{
    return coffres[i][j];
}

void Scene::setCoffre(int i, int j, int val)
{
    coffres[i][j] = val;
}

int Scene::getRooms(int d, int i, int j)
{
    return rooms[d][i][j];
}

void Scene::setRooms(int d, int i, int j, int value)
{
    rooms[d][i][j] = value;
}

int Scene::getMonsters(int i)
{
    return monsters[i];
}

void Scene::setMonsters(int i, int val)
{
    monsters[i] = val;
}

int Scene::getTotalMonsters()
{
    int total = 0;
    for (int i = 0; i < NB_MONSTERS; i++)
    {
        total += monsters[i];
    }
    return total;
}

int Scene::getMonstersSolde()
{
    int alreadyPaid = coffres[0][14];
    return getTotalMonsters() * 30 - alreadyPaid;
}

void Scene::payForMonsters()
{
    int maxPayable = link->getStatus()->getMaxRupees() - link->getStatus()->getVirtualRupees();
    int solde = getMonstersSolde();
    int amount = (solde > maxPayable) ? maxPayable : solde;
    coffres[0][14] = coffres[0][14] + amount;
    link->getStatus()->updateRupees(amount);
}
