#include "Map.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

#include "../helper/MapHelper.h"
#include "../helper/ProjectileHelper.h"

#include "../types/Poussable.h"

#include "../effects/Feuilles.h"
#include "../effects/Debris.h"
#include "../effects/FumeeBlanche.h"
#include "../effects/Plouf.h"
#include "../objects/Interrupteur.h"
#include "../objects/Pnj.h"
#include "../objects/Interrupteur.h"
#include "../objects/InterrupteurStar.h"
#include "../objects/Coffre.h"
#include "../objects/Poule.h"
#include "../objects/Sphere.h"
#include "../objects/PiegeDemi.h"
#include "../objects/PiegeColere.h"
#include "../objects/PiegeLong.h"
#include "../objects/PiegePics.h"
#include "../objects/Barriere.h"
#include "../objects/Stele.h"
#include "../objects/Jarre.h"
#include "../objects/ObjBomb.h"
#include "../ennemis/Ennemi072.h"
#include "../ennemis/Ennemi075.h"

Map::Map(int level, Metronome *metronome) : metronome(metronome), map(level),
                                            w(0), h(0), music(0), stones(0), effects(0),
                                            ennemis(0), items(0), projectiles(0), objects(0), oldMetronomeValue(0)
{

    ostringstream os;
    for (int i = 0; i < NB_IMAGES; i++)
    {
        os << (i + 1);
        string filename = "data/images/tileset/image" + os.str() + ".png";
        images[i] = ResourceManager::getInstance()->loadImage(filename, true);
        os.str("");
    }

    initializer = new MapInitializer(this);
}

Map::~Map()
{
    for (int i = 0; i < NB_IMAGES; i++)
    {
        ResourceManager::getInstance()->free(images[i]);
    }
    delete effects;
    delete ennemis;
    delete items;
    delete projectiles;
    delete objects;
    delete initializer;
}

void Map::load()
{

    for (int j = 0; j < MAX_CASE_Y; j++)
    {
        for (int i = 0; i < MAX_CASE_X; i++)
        {
            sol[i][j] = -1;
            air[i][j] = -1;
            mur[i * 2][j * 2] = HERBE;
            mur[i * 2 + 1][j * 2] = HERBE;
            mur[i * 2][j * 2 + 1] = HERBE;
            mur[i * 2 + 1][j * 2 + 1] = HERBE;
        }
    }

    loadFromFile();

    bounds.setX(0);
    bounds.setY(0);
    bounds.setW(w);
    bounds.setH(h);

    delete effects;
    effects = new Quadtree();
    effects->setBox(0, 0, w, h);

    delete ennemis;
    ennemis = new Quadtree();
    ennemis->setBox(0, 0, w, h);

    delete items;
    items = new Quadtree();
    items->setBox(0, 0, w, h);

    delete projectiles;
    projectiles = new Quadtree();
    projectiles->setBox(0, 0, w, h);

    delete objects;
    objects = new Quadtree();
    objects->setBox(0, 0, w, h);

    init();
}

void Map::loadFromFile()
{
    ostringstream oss;
    oss << map;
    string result = "data/maps/map" + oss.str() + ".dat";
    ifstream file(result.c_str());

    file >> w;
    file >> h;
    file >> music;

    for (int i = 0; i < w / 16; i++)
    {
        for (int j = 0; j < h / 16; j++)
        {
            file >> sol[i][j];
            file >> mur[i * 2][j * 2];
            file >> mur[i * 2 + 1][j * 2];
            file >> mur[i * 2][j * 2 + 1];
            file >> mur[i * 2 + 1][j * 2 + 1];
        }
    }

    int cpt = 0;
    int a;
    int b;

    file >> cpt;
    for (int i = 0; i < cpt; i++)
    {
        file >> a;
        file >> b;
        file >> air[a][b];
    }

    file.close();
}

int Map::getW()
{
    return w;
}

int Map::getH()
{
    return h;
}

int Map::getId()
{
    return map;
}

void Map::launch()
{

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    scene->getHud()->reset();

    if (scene->getAvancement() != AV_START)
    {
        Link *link = scene->getLink();

        int musicToPlay = music;

        int special = scene->getAnimationInGame()->getSpecialMusicId();

        if (special > 0)
        {
            musicToPlay = special;
        }

        if (link->getStatus()->getLife() <= 0)
        {
            musicToPlay = 3;
        }
        else if (map == 9 && scene->getAvancement() == AV_ARMEE_UP)
        {
            musicToPlay = 18;
        }
        else if (map == 55 && scene->getAvancement() < AV_FILLE_MAIRE_SAUVEE)
        {
            musicToPlay = 45;
        }

        AudioManager::getInstance()->playMusic(musicToPlay);
    }

    if (map == 7)
    {
        scene->setCoffre(0, 15, 0); // reset asile
    }

    launchRoom();
}

void Map::launchRoom()
{
    if (map >= 15)
    { // indoor only
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();

        bounds.setX(320 * (link->getX() / 320));
        bounds.setY(240 * (link->getY() / 240));
        bounds.setW(320);
        bounds.setH(240);

        // handle big rooms
        switch (map)
        {
        case 15:
            if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(19);
            }
            if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && link->getInventory()->hasCoeur(0))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 3 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() == 240 * 3)
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && (bounds.getY() == 240 * 2 || bounds.getY() == 240 * 3))
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 7 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 16:
            if ((bounds.getX() == 320 * 12 && bounds.getY() == 240 * 6) || (bounds.getX() == 320 * 13 && bounds.getY() == 240 * 4))
            {
                AudioManager::getInstance()->playMusic(21);
            }
            if (bounds.getX() == 320 * 12 && (bounds.getY() == 240 * 4 || bounds.getY() == 240 * 5) && link->getInventory()->hasCoeur(1))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 6);
                bounds.setY(240 * 2);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 13 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 11);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 3 && bounds.getY() == 0)
            {
                bounds.setX(320 * 2);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 3);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 320 * 5 || bounds.getX() == 320 * 10) && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setY(240 * 3);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 11 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 17:
            if (bounds.getX() == 0 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(19);
            }
            if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(2))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 2);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 2);
                bounds.setY(240 * 5);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 7 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 7);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 10);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 6 || bounds.getX() == 320 * 12) && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 4)
            {
                bounds.setY(240 * 2);
                bounds.setH(720);
                break;
            }
            break;
        case 18:
            if (bounds.getX() == 320 * 13 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(22);
            }
            if (bounds.getX() == 320 * 13 && bounds.getY() == 240 && link->getInventory()->hasCoeur(3))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() <= 320 * 2)
            {
                bounds.setX(0);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 6);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 9);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 12 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 11);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 14);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 3);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 7 && bounds.getX() <= 320 * 9 && bounds.getY() == 240 * 4)
            {
                bounds.setX(320 * 7);
                bounds.setW(960);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 12 && bounds.getY() == 240 * 4)
            {
                bounds.setX(320 * 11);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() >= 240 * 2)
            {
                bounds.setX(320 * 14);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 320 * 6 || bounds.getX() == 320 * 10 || bounds.getX() == 320 * 13) && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            break;
        case 19:
            if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(24);
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 && link->getInventory()->hasCoeur(4))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(0);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 3);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 7 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 7);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && (bounds.getY() == 0 || bounds.getY() >= 240 * 3))
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() == 240 * 4)
            {
                bounds.setX(320 * 3);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 4)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() == 0)
            {
                bounds.setX(320 * 8);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 20:
            if (bounds.getX() == 0 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(25);
            }
            if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(5))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 6);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 8);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() >= 240 * 4)
            {
                bounds.setX(320 * 8);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 12 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 11);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 12 && bounds.getY() >= 240 * 4)
            {
                bounds.setX(320 * 11);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 4 && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setY(240 * 3);
                bounds.setH(480);
                break;
            }
            break;
        case 21:
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(26);
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 && link->getInventory()->hasCoeur(6))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 6);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 10);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 13 && bounds.getX() <= 320 * 14 && bounds.getY() >= 240 * 2)
            {
                bounds.setX(320 * 13);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 3 && bounds.getY() >= 240 * 1 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setW(960);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() >= 240 * 2)
            {
                bounds.setX(320 * 10);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 13 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            break;
        case 22:
            if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(27);
            }
            if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && link->getInventory()->hasCoeur(7))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 4)
            {
                bounds.setX(320);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 4)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 8);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setX(320 * 9);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() == 240 * 5)
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 5)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240)
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() == 240 * 2)
            {
                bounds.setX(320 * 9);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 10);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 0 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 3 || bounds.getX() == 320 * 8 || bounds.getX() == 320 * 11) && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setY(240 * 3);
                bounds.setH(480);
                break;
            }
            break;
        case 23:
            if (bounds.getX() == 320 * 15 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(29);
                ouvrePorte(209, 43, 0);
                scene->getHud()->reset();
            }
            if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(29);
            }
            if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(8))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 12 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 11);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 3 || bounds.getX() == 320 * 7 || bounds.getX() == 320 * 10) && bounds.getY() >= 240 * 3)
            {
                bounds.setY(240 * 3);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 7 || bounds.getX() == 320 * 9) && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 24:
            if (bounds.getX() == 320 * 7 && bounds.getY() == 240 && scene->getCoffre(10, 2) == 2)
            {
                AudioManager::getInstance()->playMusic(30);
                ouvrePorte(49, 28, 0);
                scene->getHud()->reset();
            }
            if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(30);
            }
            if (bounds.getX() == 320 * 2 && bounds.getY() == 240 && link->getInventory()->hasCoeur(9))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() <= 320 && bounds.getY() <= 240)
            {
                bounds.setX(0);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 3)
            {
                bounds.setX(0);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 3);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 10);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() >= 240 * 3)
            {
                bounds.setX(320 * 10);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 13 && bounds.getY() >= 240 * 3)
            {
                bounds.setX(320 * 13);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 3);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() == 240 * 2)
            {
                bounds.setX(320 * 10);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 320 * 5 || bounds.getX() == 320 * 6 || bounds.getX() == 320 * 14) && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            break;
        case 25:
            if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 6)
            {
                AudioManager::getInstance()->playMusic(31);
            }
            if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 5 && link->getInventory()->hasCoeur(10))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() == 240 && !link->getInventory()->hasCoeur(10))
            {
                AudioManager::getInstance()->playMusic(32);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 6)
            {
                bounds.setX(320);
                bounds.setY(240 * 6);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 4);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 9);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() == 0)
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 3 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 2);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 0 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 7) && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setY(240 * 5);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 4 || bounds.getX() == 320 * 8 || bounds.getX() == 320 * 11) && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 26:
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && (bounds.getY() == 240 || bounds.getY() == 240 * 6))
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && (bounds.getY() == 240 || bounds.getY() == 240 * 2 || bounds.getY() == 240 * 6))
            {
                bounds.setX(320 * 4);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 27:
            if (bounds.getX() == 320 && bounds.getY() == 240 * 4)
            {
                AudioManager::getInstance()->playMusic(35);
            }
            if (bounds.getX() == 320 && bounds.getY() == 240 * 3 && link->getInventory()->hasCoeur(12))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() <= 240)
            {
                bounds.setX(320);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && (bounds.getY() == 240 || bounds.getY() == 240 * 4))
            {
                bounds.setX(320 * 3);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && (bounds.getY() == 240 * 2 || bounds.getY() == 240 * 6))
            {
                bounds.setX(320 * 4);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240 * 4)
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setY(240 * 6);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 5 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 28:
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 3 && bounds.getY() >= 240 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() == 240 * 8)
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() == 240 * 8)
            {
                bounds.setX(320 * 3);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 4) && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setY(240 * 6);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setY(240 * 5);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 6 || bounds.getX() == 320 * 8) && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 41:
            if (bounds.getX() >= 320 * 3)
            {
                bounds.setX(320 * 3);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
            }
            break;
        case 48:
            bounds.setX(0);
            bounds.setW(640);
            break;
        case 53:
            bounds.setY(0);
            bounds.setH(480);
            break;
        default:
            break;
        }

        if (map > 14 && map < 29)
        {
            for (int j = bounds.getY() / 240; j < (bounds.getY() + bounds.getH()) / 240; j++)
            {
                for (int i = bounds.getX() / 320; i < (bounds.getX() + bounds.getW()) / 320; i++)
                {
                    scene->setRooms(map - 15, i, j, 1);
                    if (bounds.getX() % 320 != 0)
                    {
                        scene->setRooms(map - 15, i + 1, j, 1);
                    }
                }
            }
        }

        testAnimRoom();
    }
}

void Map::resetRoom()
{
    if (map >= 15)
    {

        objects->resetNodes(&bounds);
        ennemis->resetNodes(&bounds);

        List toKill;
        effects->get(&bounds, &toKill);
        items->get(&bounds, &toKill);
        projectiles->get(&bounds, &toKill);

        toKill.iterateOnFirst();
        while (toKill.hasNext())
        {
            Node *n = (Node *)toKill.getNext();
            if (!n->isResetable())
            {
                n->killNode();
            }
        }
    }
}

BoundingBox *Map::getBounds()
{
    return &bounds;
}

void Map::reset()
{
    load();
    launch();
    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    testAnim(link->getX(), link->getY(), N, false); // BUG FIX: link bloqu� si il revit sur une porte de maison
}

void Map::init()
{
    initializer->init();
    if (map == 5)
    {
        stones = 0;
    }
}

void Map::activateInter(int x, int y, bool sound)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map)
    {
    case 15:
        if (x == 7 * 16 && y == 42 * 16)
        {
            scene->setCoffre(1, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 43, 0);
        }
        if (x == 27 * 16 && y == 12 * 16)
        {
            scene->setCoffre(1, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 13, 0);
        }
        if (x == 52 * 16 && y == 42 * 16)
        {
            scene->setCoffre(1, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 43, 0);
        }
        if (x == 95 * 16 && y == 27 * 16)
        {
            resetRandomJarre();
        }
        break;
    case 16:
        if (x == 5 * 16 && y == 3 * 16)
        {
            scene->setCoffre(2, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 13, 0);
        }
        if (x == 44 * 16 && y == 49 * 16)
        {
            scene->setCoffre(2, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 51, 1);
        }
        if (x == 91 * 16 && y == 21 * 16)
        {
            scene->setCoffre(2, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 13, 0);
        }
        if (x == 163 * 16 && y == 18 * 16)
        {
            scene->setCoffre(2, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(174, 22, 2);
        }
        if (x == 196 * 16 && y == 18 * 16)
        {
            scene->setCoffre(2, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(185, 22, 2);
        }
        if (x == 185 * 16 && y == 62 * 16)
        {
            scene->setCoffre(2, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 66, 1);
        }
        if (x == 196 * 16 && y == 69 * 16)
        {
            scene->setCoffre(2, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(194, 67, 2);
        }
        if (x == 207 * 16 && y == 25 * 16)
        {
            scene->setCoffre(2, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(204, 13, 0);
        }
        if (x == 223 * 16 && y == 3 * 16)
        {
            scene->setCoffre(2, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 2, 1);
        }
        if (x == 236 * 16 && y == 52 * 16)
        {
            scene->setCoffre(2, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 43, 0);
        }
        if (x == 256 * 16 && y == 11 * 16)
        {
            scene->setCoffre(2, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 10, 1);
        }
        if (x == 256 * 16 && y == 93 * 16)
        {
            scene->setCoffre(2, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 92, 1);
        }
        if (x == 269 * 16 && y == 38 * 16)
        {
            scene->setCoffre(2, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(269, 43, 0);
        }
        if (x == 287 * 16 && y == 11 * 16)
        {
            scene->setCoffre(2, 27, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 6, 1);
        }
        if (x == 292 * 16 && y == 18 * 16)
        {
            scene->setCoffre(2, 28, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 28, 0);
        }
        if (x == 296 * 16 && y == 33 * 16)
        {
            scene->setCoffre(2, 29, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 36, 1);
        }
        break;
    case 17:
        if (x == 146 * 16 && y == 66 * 16)
        {
            scene->setCoffre(3, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(154, 73, 0);
        }
        if (x == 172 * 16 && y == 27 * 16)
        {
            scene->setCoffre(3, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 21, 1);
        }
        if (x == 196 * 16 && y == 78 * 16)
        {
            scene->setCoffre(3, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 81, 1);
        }
        if (x == 207 * 16 && y == 71 * 16)
        {
            scene->setCoffre(3, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 73, 0);
        }
        if (x == 203 * 16 && y == 110 * 16)
        {
            scene->setCoffre(3, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 111, 1);
        }
        break;
    case 18:
        if (x == 143 * 16 && y == 56 * 16)
        {
            scene->setCoffre(4, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 58, 0);
        }
        if (x == 155 * 16 && y == 15 * 16)
        {
            scene->setCoffre(4, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 21, 1);
        }
        if (x == 174 * 16 && y == 56 * 16)
        {
            scene->setCoffre(4, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 58, 0);
        }
        if (x == 197 * 16 && y == 62 * 16)
        {
            scene->setCoffre(4, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 58, 0);
        }
        if (x == 203 * 16 && y == 71 * 16)
        {
            scene->setCoffre(4, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 66, 1);
        }
        if (x == 234 * 16 && y == 41 * 16)
        {
            scene->setCoffre(4, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 36, 1);
        }
        if (x == 234 * 16 && y == 48 * 16)
        {
            scene->setCoffre(4, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 51, 1);
        }
        if (x == 247 * 16 && y == 48 * 16)
        {
            scene->setCoffre(4, 27, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(258, 51, 1);
        }
        if (x == 265 * 16 && y == 11 * 16)
        {
            scene->setCoffre(4, 28, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(270, 7, 5);
        }
        if (x == 287 * 16 && y == 48 * 16)
        {
            scene->setCoffre(4, 29, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 51, 1);
        }
        if (x == 287 * 16 && y == 25 * 16)
        {
            scene->setCoffre(4, 30, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 28, 0);
        }
        if (x == 307 * 16 && y == 48 * 16)
        {
            scene->setCoffre(4, 31, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(309, 58, 0);
        }
        break;
    case 19:
        if (x == 7 * 16 && y == 41 * 16)
        {
            scene->setCoffre(5, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 43, 0);
        }
        if (x == 74 * 16 && y == 47 * 16)
        {
            scene->setCoffre(5, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 51, 1);
        }
        if (x == 116 * 16 && y == 67 * 16)
        {
            scene->setCoffre(5, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 58, 0);
        }
        if (x == 136 * 16 && y == 22 * 16)
        {
            scene->setCoffre(5, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 28, 0);
        }
        if (x == 143 * 16 && y == 7 * 16)
        {
            scene->setCoffre(5, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 13, 0);
        }
        if (x == 156 * 16 && y == 67 * 16)
        {
            scene->setCoffre(5, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 66, 1);
        }
        if (x == 194 * 16 && y == 38 * 16)
        {
            scene->setCoffre(5, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 36, 1);
        }
        break;
    case 21:
        if (x == 24 * 16 && y == 22 * 16)
        {
            scene->setCoffre(7, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 13, 0);
        }
        if (x == 23 * 16 && y == 56 * 16)
        {
            scene->setCoffre(7, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 51, 1);
        }
        if (x == 57 * 16 && y == 7 * 16)
        {
            scene->setCoffre(7, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 6, 1);
        }
        if (x == 96 * 16 && y == 26 * 16)
        {
            scene->setCoffre(7, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 28, 0);
        }
        if (x == 130 * 16 && y == 49 * 16)
        {
            scene->setCoffre(7, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 51, 1);
        }
        if (x == 176 * 16 && y == 7 * 16)
        {
            scene->setCoffre(7, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 13, 0);
        }
        if (x == 196 * 16 && y == 11 * 16)
        {
            scene->setCoffre(7, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 13, 0);
        }
        if (x == 230 * 16 && y == 25 * 16)
        {
            scene->setCoffre(7, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 28, 0);
        }
        if (x == 223 * 16 && y == 52 * 16)
        {
            scene->setCoffre(7, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 43, 0);
        }
        if (x == 272 * 16 && y == 26 * 16)
        {
            scene->setCoffre(7, 27, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 21, 1);
        }
        break;
    case 22:
        if (x == 16 * 16 && y == 80 * 16)
        {
            scene->setCoffre(8, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 73, 0);
        }
        if (x == 52 * 16 && y == 26 * 16)
        {
            scene->setCoffre(8, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 21, 1);
        }
        if (x == 166 * 16 && y == 27 * 16)
        {
            scene->setCoffre(8, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 28, 0);
        }
        if (x == 196 * 16 && y == 77 * 16)
        {
            scene->setCoffre(8, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 73, 0);
        }
        if (x == 217 * 16 && y == 42 * 16)
        {
            scene->setCoffre(8, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 43, 0);
        }
        break;
    case 23:
        if (x == 92 * 16 && y == 27 * 16)
        {
            scene->setCoffre(9, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 28, 0);
        }
        if (x == 150 * 16 && y == 51 * 16)
        {
            scene->setCoffre(9, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 51, 1);
        }
        if (x == 165 * 16 && y == 24 * 16)
        {
            scene->setCoffre(9, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 21, 1);
        }
        if (x == 212 * 16 && y == 7 * 16)
        {
            scene->setCoffre(9, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 6, 1);
        }
        if (x == 207 * 16 && y == 7 * 16)
        {
            scene->setCoffre(9, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(218, 6, 1);
        }
        break;
    case 24:
        if (x == 43 * 16 && y == 37 * 16)
        {
            scene->setCoffre(10, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 36, 1);
        }
        if (x == 83 * 16 && y == 67 * 16)
        {
            scene->setCoffre(10, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 58, 0);
        }
        if (x == 107 * 16 && y == 63 * 16)
        {
            scene->setCoffre(10, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 58, 0);
        }
        if (x == 124 * 16 && y == 47 * 16)
        {
            scene->setCoffre(10, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 51, 1);
        }
        if (x == 147 * 16 && y == 9 * 16)
        {
            scene->setCoffre(10, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 13, 0);
        }
        if (x == 164 * 16 && y == 72 * 16)
        {
            scene->setCoffre(10, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 66, 1);
        }
        if (x == 185 * 16 && y == 70 * 16)
        {
            scene->setCoffre(10, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 66, 1);
        }
        if (x == 233 * 16 && y == 13 * 16)
        {
            scene->setCoffre(10, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 6, 1);
        }
        if (x == 127 * 16 && y == 39 * 16)
        {
            scene->setCoffre(10, 28, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 43, 0);
        }
        break;
    case 25:
        if (x == 67 * 16 && y == 26 * 16)
        {
            scene->setCoffre(11, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 28, 0);
        }
        if (x == 77 * 16 && y == 85 * 16)
        {
            scene->setCoffre(11, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 88, 0);
        }
        if (x == 77 * 16 && y == 97 * 16)
        {
            scene->setCoffre(11, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 103, 0);
            ouvrePorte(58, 96, 1);
        }
        if (x == 96 * 16 && y == 97 * 16)
        {
            scene->setCoffre(11, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 88, 0);
        }
        if (x == 123 * 16 && y == 67 * 16)
        {
            scene->setCoffre(11, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 73, 0);
        }
        break;
    case 26:
        if (x == 16 * 16 && y == 67 * 16)
        {
            scene->setCoffre(12, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 58, 0);
        }
        if (x == 36 * 16 && y == 52 * 16)
        {
            scene->setCoffre(12, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 58, 0);
        }
        if (x == 55 * 16 && y == 85 * 16)
        {
            scene->setCoffre(12, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 88, 0);
        }
        if (x == 52 * 16 && y == 18 * 16)
        {
            scene->setCoffre(12, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 21, 1);
        }
        if (x == 63 * 16 && y == 22 * 16)
        {
            scene->setCoffre(12, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 28, 0);
        }
        if (x == 76 * 16 && y == 22 * 16)
        {
            scene->setCoffre(12, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 13, 0);
        }
        if (x == 87 * 16 && y == 26 * 16)
        {
            scene->setCoffre(12, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 21, 1);
        }
        if (x == 87 * 16 && y == 71 * 16)
        {
            scene->setCoffre(12, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 58, 0);
        }
        if (x == 96 * 16 && y == 82 * 16)
        {
            scene->setCoffre(12, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 88, 0);
        }
        if (x == 103 * 16 && y == 52 * 16)
        {
            scene->setCoffre(12, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 58, 0);
        }
        if (x == 112 * 16 && y == 26 * 16)
        {
            scene->setCoffre(12, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 21, 1);
        }
        if (x == 76 * 16 && y == 67 * 16)
        {
            scene->setCoffre(12, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 66, 1);
        }
        break;
    case 27:
        if (x == 26 * 16 && y == 71 * 16)
        {
            scene->setCoffre(13, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 73, 0);
        }
        if (x == 26 * 16 && y == 116 * 16)
        {
            scene->setCoffre(13, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 118, 0);
        }
        if (x == 43 * 16 && y == 71 * 16)
        {
            scene->setCoffre(13, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 66, 1);
        }
        if (x == 56 * 16 && y == 108 * 16)
        {
            scene->setCoffre(13, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 111, 1);
        }
        break;
    case 28:
        if (x == 72 * 16 && y == 69 * 16)
        {
            scene->setCoffre(14, 10, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 66, 1);
        }
        if (x == 69 * 16 && y == 146 * 16)
        {
            scene->setCoffre(14, 11, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 141, 1);
        }
        if (x == 163 * 16 && y == 55 * 16)
        {
            scene->setCoffre(14, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 51, 1);
        }
        break;
    }
}

bool Map::desactivateInter(int x, int y, bool sound)
{
    if (map == 15 && sol[84][17] == 1817 && sol[84][27] == 1817 && sol[95][17] == 1817)
    {
        if (sound)
            AudioManager::getInstance()->playSound(TS_PLOT);
        return true;
    }
    return false;
}

void Map::allumeTorche(int x, int y)
{ // 1811 -> 1812
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map)
    {
    case 18:
        if (((x == 185 || x == 193) && y == 17) || (x == 189 && y == 7) || (x == 196 && y == 25) || ((x == 200 || x == 208) && y == 16) || (x == 203 && y == 4) || (x == 212 && y == 23) || (x == 213 && y == 11))
        {
            if (sol[185][17] == 1812 && sol[189][7] == 1812 && sol[193][17] == 1812 && sol[196][25] == 1812 && sol[200][16] == 1812 && sol[203][4] == 1812 && sol[208][16] == 1812 && sol[212][23] == 1812 && sol[213][11] == 1812 && mur[189 * 2 + 1][28 * 2 + 1] == MUR)
            {
                scene->setCoffre(4, 35, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(189, 28, 0);
            }
        }
        if (((x == 226 || x == 253) && y == 13) || (x == 239 && (y == 5 || y == 21)))
        {
            if (sol[226][13] == 1812 && sol[239][5] == 1812 && sol[239][21] == 1812 && sol[253][13] == 1812 && mur[229 * 2 + 1][28 * 2 + 1] == MUR)
            {
                scene->setCoffre(4, 36, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(229, 28, 0);
            }
        }
        break;
    case 19:
        if (x == 43 && (y == 49 || y == 55))
        {
            if (sol[43][49] == 1812 && sol[43][55] == 1812 && mur[38 * 2 + 1][52 * 2] == MUR)
            {
                scene->setCoffre(5, 22, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 51, 1);
            }
        }
        if (x == 56 && (y == 49 || y == 55))
        {
            if (sol[56][49] == 1812 && sol[56][55] == 1812 && mur[58 * 2 + 1][52 * 2] == MUR)
            {
                scene->setCoffre(5, 23, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(58, 51, 1);
            }
        }
        if ((x == 165 || x == 174) && (y == 35 || y == 39 || y == 50 || y == 54))
        {
            if (sol[165][35] == 1812 && sol[165][39] == 1812 && sol[165][50] == 1812 && sol[165][54] == 1812 && sol[174][35] == 1812 && sol[174][39] == 1812 && sol[174][50] == 1812 && sol[174][54] == 1812 && mur[178 * 2 + 1][52 * 2] == MUR)
            {
                scene->setCoffre(5, 24, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(178, 51, 1);
            }
        }
        break;
    case 22:
        if ((x == 62 || x == 75) && (y == 49 || y == 55 || y == 64 || y == 70))
        {
            if (sol[62][49] == 1812 && sol[62][55] == 1812 && sol[62][64] == 1812 && sol[62][70] == 1812 && sol[75][49] == 1812 && sol[75][55] == 1812 && sol[75][64] == 1812 && sol[75][70] == 1812 && mur[58 * 2 + 1][52 * 2] == MUR)
            {
                scene->setCoffre(8, 24, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(58, 51, 1);
            }
        }
        break;
    case 23:
        if ((x == 22 && y == 32) || (x == 37 && y == 42))
        {
            if (sol[22][32] == 1812 && sol[37][42] == 1812 && mur[18 * 2 + 1][37 * 2] == MUR)
            {
                scene->setCoffre(9, 22, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(18, 36, 1);
            }
        }
        if ((x == 49 && y == 40) || (x == 50 && y == 40) || (x == 56 && y == 37))
        {
            if (sol[49][40] == 1812 && sol[50][40] == 1812 && sol[56][37] == 1812 && mur[38 * 2 + 1][37 * 2] == MUR)
            {
                scene->setCoffre(9, 23, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 36, 1);
            }
        }
        if ((x == 49 || x == 50) && y == 22)
        {
            if (sol[49][22] == 1812 && sol[50][22] == 1812 && mur[49 * 2 + 1][28 * 2 + 1] == MUR)
            {
                scene->setCoffre(9, 24, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 28, 0);
            }
        }
        if ((x == 103 || x == 116) && y == 37)
        {
            if (sol[103][37] == 1812 && sol[116][37] == 1812 && mur[109 * 2 + 1][43 * 2 + 1] == MUR)
            {
                scene->setCoffre(9, 25, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(109, 43, 0);
            }
        }
        if ((x == 189 || x == 190) && y == 72)
        {
            if (sol[189][72] == 1812 && sol[190][72] == 1812 && mur[178 * 2 + 1][67 * 2] == MUR)
            {
                scene->setCoffre(9, 26, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(178, 66, 1);
            }
        }
        break;
    case 24:
        if ((x == 27 || x == 32) && y == 32)
        {
            if (sol[27][32] == 1812 && sol[32][32] == 1812 && mur[29 * 2 + 1][28 * 2 + 1] == MUR)
            {
                scene->setCoffre(10, 26, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(29, 28, 0);
            }
        }
        if ((x == 247 || x == 252) && y == 32)
        {
            if (sol[247][32] == 1812 && sol[252][32] == 1812 && mur[249 * 2 + 1][28 * 2 + 1] == MUR)
            {
                scene->setCoffre(10, 29, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 28, 0);
            }
        }
        break;
    case 25:
        if ((x == 163 || x == 177) && (y == 74 || y == 79))
        {
            if (sol[163][74] == 1812 && sol[177][74] == 1812 && sol[163][79] == 1812 && sol[177][79] == 1812 && mur[178 * 2 + 1][67 * 2] == MUR)
            {
                scene->setCoffre(11, 25, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(178, 66, 1);
            }
        }
        break;
    }
}

void Map::eteintTorche(int x, int y)
{ // 1812 -> 1811
}

void Map::activateInterStar(int x, int y, bool sound)
{
    if (sound)
        AudioManager::getInstance()->playSound(TS_MAGIC);
    switch (map)
    {
    case 23:
        if (y == 3 * 16)
        {
            holeStar(245, 4, 10, 4);
            holeStar(104, 66, 2, 3);
            holeStar(109, 51, 2, 2);
            holeStar(169, 66, 2, 2);
            holeStar(186, 69, 8, 4);
            holeStar(249, 66, 2, 2);

            fullStar(126, 3, 8, 8);
            fullStar(148, 20, 4, 5);
            fullStar(186, 62, 8, 4);
        }
        if (y == 27 * 16)
        {
            fullStar(104, 66, 2, 3);
            fullStar(109, 51, 2, 2);
            fullStar(169, 66, 2, 2);
            fullStar(249, 66, 2, 2);
            fullStar(186, 69, 8, 4);
            fullStar(245, 4, 10, 4);

            holeStar(126, 3, 8, 8);
            holeStar(148, 20, 4, 5);
            holeStar(186, 62, 8, 4);
        }
        break;
    case 25:
        holeStar(31, 108, 3, 3);
        break;
    }
}

void Map::holeStar(int x, int y, int w, int h)
{
    int offset = map == 25 ? 375 : 0;
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (sol[i][j] == 3173)
            {
                setSol(i * 16, j * 16, 3173, TROU);
            }
        }
    }
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (mur[i * 2][j * 2] == TROU)
            {
                if (mur[(i - 1) * 2][(j - 1) * 2] == TROU && mur[i * 2][(j - 1) * 2] == TROU && mur[(i + 1) * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[(i - 1) * 2][(j + 1) * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU && mur[(i + 1) * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 2150);
                }
                else if (mur[i * 2][(j - 1) * 2] != TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 3162 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] != TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 3164 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] != TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 3165 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] != TROU)
                {
                    setSol(i * 16, j * 16, 3167 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] != TROU && mur[(i - 1) * 2][j * 2] != TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 3161 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] != TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] != TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 3163 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] != TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] != TROU)
                {
                    setSol(i * 16, j * 16, 3166 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] != TROU && mur[i * 2][(j + 1) * 2] != TROU)
                {
                    setSol(i * 16, j * 16, 3168 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    if (mur[(i + 1) * 2][(j + 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 3169 + offset);
                    if (mur[(i - 1) * 2][(j + 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 3170 + offset);
                    if (mur[(i + 1) * 2][(j - 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 3171 + offset);
                    if (mur[(i - 1) * 2][(j - 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 3172 + offset);
                }
            }
        }
    }
}

void Map::fullStar(int x, int y, int w, int h)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (mur[i * 2][j * 2] == TROU)
            {
                setSol(i * 16, j * 16, 3173, PIERRE);
            }
        }
    }
}

void Map::loop()
{
    effects->removeDeadNodes();
    ennemis->removeDeadNodes();
    items->removeDeadNodes();
    projectiles->removeDeadNodes();
    objects->removeDeadNodes();

    List toLoop;
    effects->get(&bounds, &toLoop);
    ennemis->get(&bounds, &toLoop);
    items->get(&bounds, &toLoop);
    projectiles->get(&bounds, &toLoop);
    objects->get(&bounds, &toLoop);

    toLoop.iterateOnFirst();
    while (toLoop.hasNext())
    {
        Loopable *l = (Loopable *)toLoop.getNext();
        l->loop();
    }

    // test tapis
    int metronomeValue = metronome->getValue();
    if (map == 25 && oldMetronomeValue != metronomeValue)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();
        // on link
        if (link->getAnimation() != CHUTE && link->getAnimation() != SOULEVE && link->getAnimation() != TOUCHE)
        {
            int val = getSol(link->getX() + 8, link->getY() + 16);
            int val1 = getSol(link->getX() + 2, link->getY() + 10);
            int val2 = getSol(link->getX() + 13, link->getY() + 10);
            int val3 = getSol(link->getX() + 2, link->getY() + 21);
            int val4 = getSol(link->getX() + 13, link->getY() + 21);
            if ((val1 == 3584 || val2 == 3584 || val3 == 3584 || val4 == 3584) && val != 3588 && val != 3592 && val != 3596)
            {
                link->pousseY(-1);
            }
            else if ((val1 == 3588 || val2 == 3588 || val3 == 3588 || val4 == 3588) && val != 3584 && val != 3592 && val != 3596)
            {
                link->pousseY(1);
            }
            else if ((val1 == 3592 || val2 == 3592 || val3 == 3592 || val4 == 3592) && val != 3584 && val != 3588 && val != 3596)
            {
                link->pousseX(-1);
            }
            else if ((val1 == 3596 || val2 == 3596 || val3 == 3596 || val4 == 3596) && val != 3584 && val != 3588 && val != 3592)
            {
                link->pousseX(1);
            }
        }
        // on ennemi72
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 7 && scene->getCoffre(11, 23) == 3)
        {
            List toMove;
            ennemis->get(&bounds, &toMove);
            toMove.iterateOnFirst();
            while (toMove.hasNext())
            {
                Ennemi072 *enn = dynamic_cast<Ennemi072 *>(toMove.getNext());
                if (enn != 0)
                {
                    int val = getSol(enn->getX() + 8, enn->getY() + 18);
                    int val1 = getSol(enn->getX() + 2, enn->getY() + 12);
                    int val2 = getSol(enn->getX() + 13, enn->getY() + 12);
                    int val3 = getSol(enn->getX() + 2, enn->getY() + 23);
                    int val4 = getSol(enn->getX() + 13, enn->getY() + 23);
                    if ((val1 == 3584 || val2 == 3584 || val3 == 3584 || val4 == 3584) && val != 3588 && val != 3592 && val != 3596)
                    {
                        enn->pousseY(-1);
                    }
                    else if ((val1 == 3588 || val2 == 3588 || val3 == 3588 || val4 == 3588) && val != 3584 && val != 3592 && val != 3596)
                    {
                        enn->pousseY(1);
                    }
                    else if ((val1 == 3592 || val2 == 3592 || val3 == 3592 || val4 == 3592) && val != 3584 && val != 3588 && val != 3596)
                    {
                        enn->pousseX(-1);
                    }
                    else if ((val1 == 3596 || val2 == 3596 || val3 == 3596 || val4 == 3596) && val != 3584 && val != 3588 && val != 3592)
                    {
                        enn->pousseX(1);
                    }
                }
            }
        }
        // on items
        List itemsToMove;
        items->get(&bounds, &itemsToMove);
        itemsToMove.iterateOnFirst();
        while (itemsToMove.hasNext())
        {
            Item *item = dynamic_cast<Item *>(itemsToMove.getNext());
            BoundingBox *itemBox = item->getBoundingBox();
            int val = getSol(itemBox->getX() + (itemBox->getW() / 2), itemBox->getY() + (itemBox->getH() / 2));
            int val1 = getSol(itemBox->getX() + 2, itemBox->getY() + 2);
            int val2 = getSol(itemBox->getX() + itemBox->getW() - 3, itemBox->getY() + 2);
            int val3 = getSol(itemBox->getX() + 2, itemBox->getY() + itemBox->getH() - 3);
            int val4 = getSol(itemBox->getX() + itemBox->getW() - 3, itemBox->getY() + itemBox->getH() - 3);
            if ((val1 == 3584 || val2 == 3584 || val3 == 3584 || val4 == 3584) && val != 3588 && val != 3592 && val != 3596)
            {
                item->pousseY(-2);
            }
            else if ((val1 == 3588 || val2 == 3588 || val3 == 3588 || val4 == 3588) && val != 3584 && val != 3592 && val != 3596)
            {
                item->pousseY(2);
            }
            else if ((val1 == 3592 || val2 == 3592 || val3 == 3592 || val4 == 3592) && val != 3584 && val != 3588 && val != 3596)
            {
                item->pousseX(-2);
            }
            else if ((val1 == 3596 || val2 == 3596 || val3 == 3596 || val4 == 3596) && val != 3584 && val != 3588 && val != 3592)
            {
                item->pousseX(2);
            }
        }
        // on objects
        List objectsToMove;
        objects->get(&bounds, &objectsToMove);
        objectsToMove.iterateOnFirst();
        while (objectsToMove.hasNext())
        {
            ObjBomb *bomb = dynamic_cast<ObjBomb *>(objectsToMove.getNext());
            if (bomb != 0)
            {
                int val = getSol(bomb->getX() + 8, bomb->getY() + 8);
                int val1 = getSol(bomb->getX() + 2, bomb->getY() + 2);
                int val2 = getSol(bomb->getX() + 13, bomb->getY() + 2);
                int val3 = getSol(bomb->getX() + 2, bomb->getY() + 13);
                int val4 = getSol(bomb->getX() + 13, bomb->getY() + 13);
                if ((val1 == 3584 || val2 == 3584 || val3 == 3584 || val4 == 3584) && val != 3588 && val != 3592 && val != 3596)
                {
                    bomb->pousseY(-2);
                }
                else if ((val1 == 3588 || val2 == 3588 || val3 == 3588 || val4 == 3588) && val != 3584 && val != 3592 && val != 3596)
                {
                    bomb->pousseY(2);
                }
                else if ((val1 == 3592 || val2 == 3592 || val3 == 3592 || val4 == 3592) && val != 3584 && val != 3588 && val != 3596)
                {
                    bomb->pousseX(-2);
                }
                else if ((val1 == 3596 || val2 == 3596 || val3 == 3596 || val4 == 3596) && val != 3584 && val != 3588 && val != 3592)
                {
                    bomb->pousseX(2);
                }
            }
        }
    }
    oldMetronomeValue = metronomeValue;
}

void Map::draw(List *toDraw, BoundingBox *box, int dstX, int dstY)
{

    int srcX = box->getX();
    int srcY = box->getY();
    int srcW = box->getW();
    int srcH = box->getH();

    drawSol(srcX, srcY, srcW, srcH, dstX, dstY);

    effects->get(box, toDraw);
    ennemis->get(box, toDraw);
    items->get(box, toDraw);
    projectiles->get(box, toDraw);
    objects->get(box, toDraw);

    if (toDraw != 0)
    {
        toDraw->iterateOnFirst();
        while (toDraw->hasNext())
        {
            Drawable *d = (Drawable *)toDraw->getNext();
            d->draw(srcX - dstX, srcY - dstY);
        }
    }

    drawAir(srcX, srcY, srcW, srcH, dstX, dstY);
}

void Map::drawSol(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY)
{

    int w = 0;
    int h = 0;
    int diffX = 0;
    int diffY = 0;

    for (int j = srcY; j < srcY + srcH; j += CASE)
    {
        for (int i = srcX; i < srcX + srcW; i += CASE)
        {

            diffX = (i % CASE);
            diffY = (j % CASE);

            int motif = getMotif(sol[i / CASE][j / CASE]);

            if (motif >= 0)
            {

                int im = motif / 1000;
                motif -= im * 1000;

                w = CASE - diffX;
                h = CASE - diffY;

                if (i + w > srcX + srcW)
                {
                    w = srcX + srcW - i;
                }
                if (j + h > srcY + srcH)
                {
                    h = srcY + srcH - j;
                }

                WindowManager::getInstance()->draw(
                    images[im],
                    (motif % 40) * CASE + diffX,
                    (motif / 40) * CASE + diffY, w, h,
                    dstX + i - srcX, dstY + j - srcY);
            }
            i -= diffX;
        }
        j -= diffY;
    }
}

void Map::drawAir(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY)
{

    int w = 0;
    int h = 0;
    int diffX = 0;
    int diffY = 0;

    for (int j = srcY; j < srcY + srcH; j += CASE)
    {
        for (int i = srcX; i < srcX + srcW; i += CASE)
        {

            diffX = (i % CASE);
            diffY = (j % CASE);

            int motif = getMotif(air[i / CASE][j / CASE]);

            if (motif >= 0)
            {

                int im = motif / 1000;
                motif -= im * 1000;

                w = CASE - diffX;
                h = CASE - diffY;

                if (i + w > srcX + srcW)
                {
                    w = srcX + srcW - i;
                }
                if (j + h > srcY + srcH)
                {
                    h = srcY + srcH - j;
                }

                WindowManager::getInstance()->draw(
                    images[im],
                    (motif % 40) * CASE + diffX, (motif / 40) * CASE + diffY, w, h,
                    dstX + i - srcX, dstY + j - srcY);
            }
            i -= diffX;
        }
        j -= diffY;
    }
}

int Map::getMotif(int value)
{
    int tmp = metronome->getValue();
    switch (value)
    {
    case 1: // fleurs
        switch (tmp % 4)
        {
        case 0:
            return 2;
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 1;
        }
        break;
    case 329:
    case 330:
    case 331:
    case 332:
    case 333:
    case 334:
    case 335:
    case 336:
        switch (tmp % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 8;
        case 2:
            return value + 8 * 2;
        case 3:
            return value + 8;
        }
        break;
    case 67:
    case 70:
    case 379:
    case 382:
    case 385:
    case 388:
    case 391:
    case 394:
    case 401:
    case 404:
    case 407:
    case 410:
    case 415:
    case 418:
        switch (tmp / 2 % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        }
        break;
    case 353:
    case 356:
    case 1812:
    case 2553:
        switch (tmp % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        case 3:
            return value + 1;
        }
        break;
    case 613:
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 3;
        case 2:
            return value + 5;
        }
        break;
    case 615:
        return value + 2 * (tmp % 3);
    case 1463:
    case 1471:
    case 1473: // clouds
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 25;
        case 2:
            return value + 26;
        }
        break;
    case 1466:
    case 1468:
    case 1470: // clouds
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 24;
        case 2:
            return value + 25;
        }
        break;
    case 1474:
    case 1476: // clouds
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 26;
        case 2:
            return value + 27;
        }
        break;
    case 1477: // clouds
        switch (tmp % 3)
        {
        case 0:
            return 1477;
        case 1:
            return 1504;
        case 2:
            return 1505;
        }
        break;
    case 1486: // clouds
        switch (tmp % 3)
        {
        case 0:
            return 1486;
        case 1:
            return 1506;
        case 2:
            return 1507;
        }
        break;
    case 1487: // clouds
        switch (tmp % 3)
        {
        case 0:
            return 1487;
        case 1:
            return 1508;
        case 2:
            return 1509;
        }
        break;
    case 2360: // pics
        switch (tmp % 6)
        {
        case 0:
            return 2360;
        case 1:
            return 2361;
        case 2:
            return 2362;
        case 3:
            return 2363;
        case 4:
            return 2362;
        case 5:
            return 2361;
        }
        break;
    case 2507:
    case 2508:
    case 2509:
    case 2510:
    case 2511:
    case 2512:
    case 2513:
    case 2514:
    case 2515:
    case 2516:
    case 2517:
    case 2518:
    case 2519:
        switch ((tmp / 2) % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 13;
        case 2:
            return value + 26;
        case 3:
            return value + 13;
        }
        break;
    case 2690:
    case 2691:
    case 2692:
    case 2693:
    case 2694:
    case 2695:
    case 2696:
    case 2697:
    case 2698:
    case 2699:
    case 2700:
    case 2701:
    case 2702:
        switch (tmp / 2 % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 13;
        case 2:
            return value + 26;
        }
        break;
    case 3548:
    case 3549:
    case 3550:
    case 3551:
    case 3552:
    case 3553:
    case 3554:
    case 3555:
    case 3556:
    case 3557:
    case 3558:
    case 3559:
        switch ((tmp / 2) % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 12;
        case 2:
            return value + 24;
        case 3:
            return value + 12;
        }
        break;
    case 3584:
    case 3588:
    case 3592:
    case 3596: // tapis roulant
        switch (tmp % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        case 3:
            return value + 3;
        }
        break;
    case 3601:
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        }
        break;
    default:
        break;
    }
    return value;
}

short Map::getMur(int x, int y)
{
    return mur[x / 8][y / 8];
}

short Map::getSol(int x, int y)
{
    return sol[x / CASE][y / CASE];
}

void Map::setSol(int x, int y, short s)
{
    int i = x / CASE;
    int j = y / CASE;
    sol[i][j] = s;
}

void Map::setSol(int x, int y, short s, Collision c)
{
    int i = x / CASE;
    int j = y / CASE;
    sol[i][j] = s;
    mur[i * 2][j * 2] = c;
    mur[i * 2 + 1][j * 2] = c;
    mur[i * 2][j * 2 + 1] = c;
    mur[i * 2 + 1][j * 2 + 1] = c;
}

void Map::setSol(int x, int y, int w, int h, short s, Collision c)
{
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            setSol(x + i * 16, y + j * 16, s, c);
        }
    }
}

void Map::setAir(int x, int y, short s)
{
    int i = x / CASE;
    int j = y / CASE;
    air[i][j] = s;
}

void Map::addEffect(Effect *effect)
{
    effects->add((Node *)effect);
}

void Map::addEnnemi(Ennemi *ennemi)
{
    ennemis->add((Node *)ennemi);
}

void Map::addItem(Item *item)
{
    items->add((Node *)item);
}

void Map::addProjectile(Projectile *projectile)
{
    projectiles->add((Node *)projectile);
}

void Map::addObject(Object *object)
{
    objects->add((Node *)object);
}

void Map::removeObject(Object *object)
{
    objects->remove((Node *)object);
}

bool Map::checkCollisions(BoundingBox *box, Collisionable *object, bool checkEnnemis, bool ignoreNotIdle, bool withAvoid, bool onlyBox, bool checkObjects,
                          int safeX, int safeY, int safeW, int safeH, bool checkDanger)
{

    if (box->getX() < bounds.getX() || box->getX() + box->getW() > bounds.getX() + bounds.getW() ||
        box->getY() < bounds.getY() || box->getY() + box->getH() > bounds.getY() + bounds.getH())
    {
        return false;
    }

    if (onlyBox)
    {

        for (int j = box->getY() - (box->getY() % 8); j < box->getY() + box->getH(); j += 8)
        {
            for (int i = box->getX() - (box->getX() % 8); i < box->getX() + box->getW(); i += 8)
            {
                Collision c = (Collision)getMur(i, j);
                if (c == GRAND_MUR)
                {
                    return false;
                }
            }
        }

        return true;
    }

    Link *lk = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();

    for (int j = box->getY() - (box->getY() % 8); j < box->getY() + box->getH(); j += 8)
    {
        for (int i = box->getX() - (box->getX() % 8); i < box->getX() + box->getW(); i += 8)
        {
            Collision c = (Collision)getMur(i, j);
            if (!object->isCollision(c) || (withAvoid && object->isToAvoid(c)))
            {
                if (c == DANGER && checkDanger)
                {
                    if ((Collisionable *)lk == object)
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                }
                return false;
            }
            else
            {
                if (c == DANGER_BAS && checkDanger)
                {
                    if ((Collisionable *)lk == object)
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                }
            }
        }
    }

    if (checkEnnemis)
    {
        List enn;
        ennemis->get(box, &enn);

        enn.iterateOnFirst();
        while (enn.hasNext())
        {
            Ennemi *e = (Ennemi *)enn.getNext();
            if (ignoreNotIdle && !e->isIdle())
                continue;
            if (e != object && e->getBoundingBox()->intersect(box))
            {
                return false;
            }
        }
    }

    if (checkObjects)
    {
        List obj;
        objects->get(box, &obj);
        obj.iterateOnFirst();
        while (obj.hasNext())
        {
            Object *o = (Object *)obj.getNext();

            if ((Collisionable *)lk == object)
            {
                PiegePics *pics = dynamic_cast<PiegePics *>(o);
                PiegeLong *plong = dynamic_cast<PiegeLong *>(o);
                Barriere *barriere = dynamic_cast<Barriere *>(o);
                if (pics != 0)
                {
                    Direction dir = N;
                    switch (lk->getDirection())
                    {
                    case N:
                        dir = S;
                        break;
                    case S:
                        dir = N;
                        break;
                    case W:
                        dir = E;
                        break;
                    case E:
                        dir = W;
                        break;
                    }
                    lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                }
                else if (plong != 0)
                {
                    lk->underAttack(plong->getDirection(), 1, TA_PHYSIC, TE_NORMAL);
                }
                else if (barriere != 0)
                {
                    lk->underAttack(S, 1, TA_PHYSIC, TE_ELECTRIC);
                }
            }

            if (o != object && o->getBoundingBox()->intersect(box))
            {
                BoundingBox safeBox;
                safeBox.setX(safeX);
                safeBox.setY(safeY);
                safeBox.setW(safeW);
                safeBox.setH(safeH);
                if (!o->getBoundingBox()->intersect(&safeBox))
                {
                    return false;
                }
            }
            if (o != object && o->getSecondBoundingBox() != 0 && o->getSecondBoundingBox()->intersect(box))
            {
                return false;
            }
        }
    }

    if ((Collisionable *)lk == object && testVillage(box, lk->getStatus()->isOniLink()))
    {
        MainController::getInstance()->getGameController()->displayText(292);
        return false;
    }

    return true;
}

bool Map::testDegat(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis)
{

    bool result = false;

    // on ennemi :
    if (onEnnemis)
    {
        List enn;
        ennemis->get(box, &enn);

        enn.iterateOnFirst();
        while (enn.hasNext())
        {
            Ennemi *e = (Ennemi *)enn.getNext();
            if (e->getBoundingBox()->intersect(box) && e->isHittable())
            {
                e->underAttack(dir, force, type, effect, box);
                result = true;
            }
        }
    }

    // on objects :

    List obj;
    objects->get(box, &obj);

    obj.iterateOnFirst();
    while (obj.hasNext())
    {
        Object *o = (Object *)obj.getNext();
        if (o->isAttackable() && o->getBoundingBox()->intersect(box))
        {
            o->underAttack(dir, force, type, effect);
            result = true;
        }
    }

    // on projectiles :

    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    if ((type == TA_SWORD || type == TA_SWORD_HOLD) && link->getEpee() >= 2)
    {
        List proj;
        projectiles->get(box, &proj);

        proj.iterateOnFirst();
        while (proj.hasNext())
        {
            Projectile *p = (Projectile *)proj.getNext();
            if (p->getBoundingBox()->intersect(box))
            {
                p->renvoie(dir);
                result = true;
            }
        }
    }

    // on map :

    int x0 = box->getX();
    int beginX = x0 - (x0 % CASE);
    int x1 = box->getX() + box->getW() - 1;
    int endX = x1 - (x1 % CASE);

    int y0 = box->getY();
    int beginY = y0 - (y0 % CASE);
    int y1 = box->getY() + box->getH() - 1;
    int endY = y1 - (y1 % CASE);

    if (beginX < 0)
        beginX = 0;
    if (beginY < 0)
        beginY = 0;
    if (endX > getW())
        endX = getW();
    if (endY > getH())
        endY = getH();

    for (int j = beginY; j <= endY; j += CASE)
    {
        for (int i = beginX; i <= endX; i += CASE)
        {

            int x = i / CASE;
            int y = j / CASE;
            int val = sol[x][y];

            if (type == TA_SWORD || effect == TE_FEU || type == TA_SWORD_HOLD)
            {
                if (val == 185 || val == 187 || val == 189 || val == 553)
                {
                    // buissons
                    Collision c;
                    TypeDons td;
                    int tb;
                    switch (val)
                    {
                    case 185:
                        c = HERBE;
                        td = TD_BUISSON_VERT;
                        tb = 0;
                        break;
                    case 187:
                        c = HERBE;
                        td = TD_BUISSON_ROSE;
                        tb = 1;
                        break;
                    case 189:
                        c = SABLE;
                        td = TD_BUISSON_OCRE;
                        tb = 2;
                        break;
                    case 553:
                        c = NEIGE;
                        td = TD_BUISSON_NEIGE;
                        tb = 3;
                        break;
                    default:
                        c = HERBE;
                        td = TD_BUISSON_VERT;
                        tb = 0;
                        break;
                    }

                    if (map == 1 && x == 53 && y == 33)
                    {
                        sol[x][y] = 1212;
                        mur[x * 2][y * 2] = TROU;
                        mur[(x * 2) + 1][y * 2] = TROU;
                        mur[x * 2][(y * 2) + 1] = TROU;
                        mur[(x * 2) + 1][(y * 2) + 1] = TROU;
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                    }
                    else if (map == 2 && x == 112 && y >= 31 && y <= 33)
                    {
                        sol[x][y] = 1212;
                        mur[x * 2][y * 2] = TROU;
                        mur[(x * 2) + 1][y * 2] = TROU;
                        mur[x * 2][(y * 2) + 1] = TROU;
                        mur[(x * 2) + 1][(y * 2) + 1] = TROU;
                    }
                    else
                    {
                        sol[x][y] = val + 1;
                        mur[x * 2][y * 2] = c;
                        mur[(x * 2) + 1][y * 2] = c;
                        mur[x * 2][(y * 2) + 1] = c;
                        mur[(x * 2) + 1][(y * 2) + 1] = c;

                        TypeItem t = MapHelper::getInstance()->getItemRandomizer(td)->selectType();
                        if (t != TI_NO_ITEM)
                        {
                            addItem(ItemHelper::getInstance()->createItem(t, i + 8, j + 8));
                        }
                    }

                    addEffect(new Feuilles(x * 16 + 8 - 14, y * 16 + 8 - 22 - 8, tb));
                    AudioManager::getInstance()->playSound(TS_BUISSON);

                    result = (type == TA_SWORD || type == TA_SWORD_HOLD);
                } /* else if (val == 2593) {
                     // rideaux
                     Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                     AudioManager::getInstance()->playSound(TS_SURPRISE);
                     scene->setCoffre(9, 14, 1);
                     ouvrePorte(69, 13, 4);
                 }*/
            }
            if (effect == TE_GLACE)
            {
                if ((getMur(i, j) == EAU || getMur(i, j) == EAU_PROF) && (getMur(i + 8, j) == EAU || getMur(i + 8, j) == EAU_PROF) && (getMur(i, j + 8) == EAU || getMur(i, j + 8) == EAU_PROF) && (getMur(i + 8, j + 8) == EAU || getMur(i + 8, j + 8) == EAU_PROF))
                {

                    sol[x][y] = 359;
                    mur[x * 2][y * 2] = GLACE;
                    mur[(x * 2) + 1][y * 2] = GLACE;
                    mur[x * 2][(y * 2) + 1] = GLACE;
                    mur[(x * 2) + 1][(y * 2) + 1] = GLACE;
                }
                switch (val)
                {
                case 67:
                    sol[x][y] = 73;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 70:
                    sol[x][y] = 74;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 313:
                    sol[x][y] = 360;
                    break;
                case 314:
                    sol[x][y] = 361;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 315:
                    sol[x][y] = 362;
                    break;
                case 316:
                    sol[x][y] = 363;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 318:
                    sol[x][y] = 364;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    break;
                case 319:
                    sol[x][y] = 365;
                    break;
                case 320:
                    sol[x][y] = 366;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    break;
                case 321:
                    sol[x][y] = 367;
                    break;
                case 322:
                    sol[x][y] = 368;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 323:
                    sol[x][y] = 369;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 324:
                    sol[x][y] = 370;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 325:
                    sol[x][y] = 371;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    break;
                case 391:
                    sol[x][y] = 421;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    break;
                case 401:
                    sol[x][y] = 422;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 407:
                    sol[x][y] = 423;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 415:
                    sol[x][y] = 424;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 1812:
                    sol[x][y] = 1811;
                    break; // torche
                default:
                    break;
                }
                if (val == 1812)
                    eteintTorche(x, y);
            }
            if (type == TA_EXPLO)
            {
                if (val == 173 || val == 174)
                { // plaine
                    // fissure
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    switch (map)
                    {
                    case 3:
                        scene->setCoffre(0, 2, 1);
                        ouvrePorte(10, 12, 0);
                        break;
                    case 5:
                        scene->setCoffre(0, 3, 1);
                        ouvrePorte(25, 68, 0);
                        break;
                    case 9:
                        scene->setCoffre(0, 6, 1);
                        ouvrePorte(39, 86, 0);
                        break;
                    }
                }
                else if (val == 480 || val == 481)
                { // eau prof
                    // fissure
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    switch (map)
                    {
                    case 6:
                        scene->setCoffre(0, 4, 1);
                        ouvrePorte(92, 31, 1);
                        break;
                    case 8:
                        scene->setCoffre(0, 5, 1);
                        ouvrePorte(21, 20, 1);
                        break;
                    case 10:
                        scene->setCoffre(0, 7, 1);
                        ouvrePorte(24, 38, 1);
                        break;
                    }
                }
                else if (val == 1134 || val == 1135)
                { // terre
                    // fissure
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 1, 1);
                    ouvrePorte(14, 29, 0);
                }
                else if (val == 1204 || val == 1205)
                { // herbe ocre
                    // fissure
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    if (x < 20)
                    {
                        scene->setCoffre(0, 8, 1);
                        ouvrePorte(16, 55, 1);
                    }
                    else
                    {
                        scene->setCoffre(0, 9, 1);
                        ouvrePorte(94, 34, 1);
                    }
                }
                else if (map > 14 && map < 29)
                {
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    // donjon
                    switch (map)
                    {
                    case 16:
                        if (val == 1946 || val == 1947 || val == 1948 || val == 1949)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 32, 1);
                            ouvrePorte(269, 73, 0);
                        }
                        else if (val == 1953 || val == 1954)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (x < 200)
                            {
                                scene->setCoffre(map - 14, 30, 1);
                                ouvrePorte(158, 81, 1);
                            }
                            else
                            {
                                scene->setCoffre(map - 14, 31, 1);
                                ouvrePorte(258, 66, 1);
                            }
                        }
                        break;
                    case 17:
                        if (val == 2084 || val == 2085)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 2 && bounds.getY() == 240)
                            {
                                scene->setCoffre(map - 14, 17, 1);
                                ouvrePorte(49, 43, 2);
                            }
                            else if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 5)
                            {
                                scene->setCoffre(map - 14, 19, 1);
                                ouvrePorte(89, 73, 2);
                            }
                            else if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 2)
                            {
                                scene->setCoffre(map - 14, 22, 1);
                                ouvrePorte(189, 43, 2);
                            }
                            else if (bounds.getX() == 320 * 11 && bounds.getY() == 240 * 7)
                            {
                                scene->setCoffre(map - 14, 23, 1);
                                ouvrePorte(229, 103, 2);
                            }
                        }
                        else if (val == 2086 || val == 2087)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 3)
                            {
                                scene->setCoffre(map - 14, 18, 1);
                                ouvrePorte(78, 51, 3);
                            }
                            else if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 7)
                            {
                                scene->setCoffre(map - 14, 21, 1);
                                ouvrePorte(158, 111, 3);
                            }
                        }
                        else if (val == 2163)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 20, 1);
                            ouvrePorte(89, 66, 4);
                        }
                        break;
                    case 18:
                        if (val == 2298 || val == 2299 || val == 2300 || val == 2301)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 12)
                            {
                                scene->setCoffre(map - 14, 33, 1);
                                ouvrePorte(249, 43, 2);
                            }
                            else if (bounds.getX() == 320 * 14)
                            {
                                scene->setCoffre(map - 14, 34, 1);
                                ouvrePorte(289, 58, 2);
                            }
                        }
                        else if (val == 2358)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 32, 1);
                            ouvrePorte(69, 21, 4);
                        }
                        break;
                    case 19:
                        if (val == 2483 || val == 2484)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 21, 1);
                            ouvrePorte(158, 21, 3);
                        }
                        break;
                    case 20:
                        if (val == 2556 || val == 2557)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 3)
                            {
                                scene->setCoffre(map - 14, 32, 1);
                                ouvrePorte(58, 51, 1);
                            }
                            else if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 4)
                            {
                                scene->setCoffre(map - 14, 33, 1);
                                ouvrePorte(58, 66, 1);
                            }
                            else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 3)
                            {
                                scene->setCoffre(map - 14, 34, 1);
                                ouvrePorte(118, 51, 1);
                            }
                            else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 4)
                            {
                                scene->setCoffre(map - 14, 35, 1);
                                ouvrePorte(118, 66, 1);
                            }
                        }
                        break;
                    case 22:
                        if (val == 2898 || val == 2899)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 0)
                            {
                                scene->setCoffre(map - 14, 21, 1);
                                ouvrePorte(9, 28, 2);
                            }
                            else if (bounds.getX() == 320 * 3)
                            {
                                scene->setCoffre(map - 14, 22, 1);
                                ouvrePorte(69, 28, 2);
                            }
                        }
                        else if (val == 2900 || val == 2901)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 23, 1);
                            ouvrePorte(98, 6, 3);
                        }
                        break;
                    case 23:
                        if (val == 3144 || val == 3145)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 4)
                            {
                                scene->setCoffre(map - 14, 17, 1);
                                ouvrePorte(98, 36, 3);
                            }
                            else if (bounds.getX() == 320 * 6)
                            {
                                scene->setCoffre(map - 14, 18, 1);
                                ouvrePorte(118, 36, 3);
                            }
                            else if (bounds.getY() == 240 * 3)
                            {
                                scene->setCoffre(map - 14, 20, 1);
                                ouvrePorte(238, 51, 3);
                            }
                            else if (bounds.getY() == 240 * 4)
                            {
                                scene->setCoffre(map - 14, 21, 1);
                                ouvrePorte(238, 66, 3);
                            }
                        }
                        else if (val == 3146)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 19, 1);
                            ouvrePorte(169, 7, 4);
                        }
                        break;
                    case 24:
                        if (val == 3299 || val == 3300)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 25, 1);
                            ouvrePorte(189, 13, 2);
                        }
                        else if (val == 3301 || val == 3302)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 24, 1);
                            ouvrePorte(178, 6, 3);
                        }
                        break;
                    case 25:
                        if (val == 3478 || val == 3479)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 2)
                            {
                                scene->setCoffre(map - 14, 20, 1);
                                ouvrePorte(49, 28, 2);
                            }
                            else if (bounds.getX() == 320 * 5)
                            {
                                scene->setCoffre(map - 14, 21, 1);
                                ouvrePorte(109, 13, 2);
                            }
                            else if (bounds.getX() == 320 * 6)
                            {
                                scene->setCoffre(map - 14, 22, 1);
                                ouvrePorte(129, 28, 2);
                            }
                        }
                        else if (val == 3480 || val == 3481)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 19, 1);
                            ouvrePorte(38, 21, 3);
                        }
                        break;
                    case 26:
                        if (val == 3754 || val == 3755)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 14, 26, 1);
                            ouvrePorte(78, 66, 3);
                        }
                        break;
                    case 27:
                        if (val == 4010 || val == 4011)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (bounds.getX() == 320 * 5)
                            {
                                scene->setCoffre(map - 14, 16, 1);
                                ouvrePorte(109, 58, 2);
                            }
                            else if (bounds.getX() == 320 * 6 && y < 67)
                            {
                                scene->setCoffre(map - 14, 17, 1);
                                ouvrePorte(149, 58, 2);
                            }
                            else if (bounds.getX() == 320 * 6 && y > 67)
                            {
                                scene->setCoffre(map - 14, 18, 1);
                                ouvrePorte(149, 73, 2);
                            }
                        }
                        break;
                    }
                }
            }
            if (type == TA_MARTEAU)
            {
                if (val == 311)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 312, HERBE);
                }
                else if (val == 705)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 706, SABLE);
                }
                else if (val == 905)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 906, HERBE);
                }
                else if (val == 2553)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 2552, PIERRE);
                }
            }
            if (effect == TE_FEU)
            {
                if (val == 1811)
                {
                    sol[x][y] = 1812;
                    allumeTorche(x, y);
                }
                else if (val == 3348 && map == 24)
                {
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    if (bounds.getX() == 320 * 2)
                    {
                        scene->setCoffre(map - 14, 22, 1);
                        ouvrePorte(49, 66, 4);
                        AudioManager::getInstance()->playSound(TS_PLOUF);
                        addEffect(new Plouf(49 * 16 + 8, 66 * 16 + 8));
                    }
                    else
                    {
                        scene->setCoffre(map - 14, 23, 1);
                        ouvrePorte(69, 6, 4);
                        AudioManager::getInstance()->playSound(TS_PLOUF);
                        addEffect(new Plouf(69 * 16 + 8, 6 * 16 + 8));
                    }
                }
            }
        }
    }
    return result;
}

bool Map::testGemmeForce(int x, int y)
{
    if (map == 5)
    {
        // stones
        if ((x == 131 && y == 32 && stones == 0) || (x == 130 && y == 37 && stones == 1) || (x == 129 && y == 42 && stones == 2) || (x == 132 && y == 52 && stones == 3) || (x == 128 && y == 56 && stones == 4) || (x == 118 && y == 53 && stones == 5) || (x == 113 && y == 54 && stones == 6) || (x == 108 && y == 55 && stones == 7))
        {
            stones++;
            return true;
        }
        if (x == 112 && y == 34 && stones == 8)
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            ouvrePorte(112, 34, 1);
            return true;
        }
    }
    return false;
}

void Map::persistJarres()
{
    List toList;
    objects->get(&bounds, &toList);

    int i = 0;

    toList.iterateOnFirst();
    while (toList.hasNext() && i < 3)
    {
        Jarre *jarre = dynamic_cast<Jarre *>(toList.getNext());
        if (jarre != 0)
        {
            jarres[i++] = jarre;
        }
    }
}

void Map::resetRandomJarre()
{
    int randomValue = ((int)rand()) % 3;
    Jarre *jarre = dynamic_cast<Jarre *>(jarres[randomValue]);
    if (jarre != 0)
    {
        jarre->reset();
        addEffect(new FumeeBlanche(jarre->getX() + 8, jarre->getY() + 8, 4));
        AudioManager::getInstance()->playSound(TS_CAPE_ON);
    }
}

void Map::pickUpItems(BoundingBox *box)
{
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Item *i = (Item *)toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isAlive())
        {
            i->action();
        }
    }
}

Item *Map::getItem(BoundingBox *box)
{
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Item *i = (Item *)toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isReady() && i->isAlive() && i->isPickable())
        {
            return i;
        }
    }
    return 0;
}

void Map::killItems(BoundingBox *box)
{
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Item *i = (Item *)toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isAlive())
        {
            i->killNode();
        }
    }
}

void Map::killEnnemis(BoundingBox *box)
{
    List toKill;
    ennemis->get(box, &toKill);

    toKill.iterateOnFirst();
    while (toKill.hasNext())
    {
        Ennemi *e = (Ennemi *)toKill.getNext();
        if (e->getBoundingBox()->intersect(box) && e->isAlive())
        {
            e->killNode();
        }
    }
}

Portable *Map::pickUpObject(BoundingBox *box)
{

    List toPickUp;
    objects->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Portable *p = dynamic_cast<Portable *>(toPickUp.getNext());
        if (p != 0 && p->isCarriable() && p->getHandableBox()->intersect(box))
        {
            return p;
        }
    }

    return 0;
}

void Map::pushObject(BoundingBox *box, Direction dir)
{
    List toPush;
    objects->get(box, &toPush);

    toPush.iterateOnFirst();
    while (toPush.hasNext())
    {
        Poussable *p = dynamic_cast<Poussable *>(toPush.getNext());
        if (p != 0)
        {
            p->pousse(dir);
            return;
        }
    }
}

bool Map::tryToTalk(BoundingBox *box, Direction dir)
{
    List toTalk;

    // try to interact with objects or npcs
    objects->get(box, &toTalk);

    toTalk.iterateOnFirst();
    while (toTalk.hasNext())
    {
        Object *p = dynamic_cast<Object *>(toTalk.getNext());
        if (p != 0 && p->action(dir))
        {
            return true;
        }
    }
    return false;
}

bool Map::testTransition(int x, int y)
{
    if (map > 14)
        return false;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (map == 1 && y <= 0 && scene->getAvancement() < AV_AUTORISATION_SORTIE)
    {
        Link *link = scene->getLink();
        link->setY(link->getY() + 4);
        link->setDirection(S);
        MainController::getInstance()->getGameController()->displayText(177);
        return false;
    }
    else if (map == 9 && scene->getAvancement() == AV_ARMEE_UP)
    {
        Link *link = scene->getLink();
        if (x <= 8 && ((y > 19 * 16 && y < 25 * 16) || y > 90 * 16))
        {
            link->setX(link->getX() + 4);
            link->setDirection(E);
            MainController::getInstance()->getGameController()->displayText(248);
            return false;
        }
        if (y <= 0)
        {
            link->setY(link->getY() + 4);
            link->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(248);
            return false;
        }
        if (x >= w - 24)
        {
            link->setX(link->getX() - 4);
            link->setDirection(W);
            MainController::getInstance()->getGameController()->displayText(248);
            return false;
        }
        if (y >= h - 32)
        {
            link->setY(link->getY() - 4);
            link->setDirection(N);
            MainController::getInstance()->getGameController()->displayText(248);
            return false;
        }
    }
    return ((x <= 8 && map != 5 && map != 11 && map != 12 && map != 13 && map != 14) ||
            (y <= 0 && map != 4 && map != 5 && map != 8 && map != 12 && map != 14) ||
            (x >= w - 24 && map != 1 && map != 2 && map != 3 && map != 5 && map != 14) ||
            (y >= h - 32 && map != 1 && map != 6 && map != 10 && map != 11 && map != 13));
}

bool Map::testInnerTransition(int x, int y)
{
    if (map < 15)
        return false;

    // labyrinth
    if (map == 26 && bounds.getX() >= 140 * 16 && bounds.getX() < 280 * 16)
    {
        bool fail = false;
        if (y <= bounds.getY())
        {
            fail = bounds.getY() == 0 || (bounds.getY() == 15 * 16 && bounds.getX() == 260 * 16) || (bounds.getY() == 30 * 16 && (bounds.getX() == 220 * 16 || bounds.getX() == 240 * 16)) || (bounds.getY() == 45 * 16 && bounds.getX() < 200 * 16) || (bounds.getY() == 60 * 16 && bounds.getX() > 200 * 16) || (bounds.getY() == 75 * 16 && (bounds.getX() == 160 * 16 || bounds.getX() == 180 * 16 || bounds.getX() == 240 * 16)) || (bounds.getY() == 90 * 16 && (bounds.getX() == 140 * 16 || bounds.getX() == 160 * 16 || bounds.getX() == 220 * 16));
        }
        else if (y >= bounds.getY() + bounds.getH() - 32)
        {
            fail = bounds.getY() == 90 * 16 || (bounds.getY() == 0 && bounds.getX() == 260 * 16) || (bounds.getY() == 15 * 16 && (bounds.getX() == 220 * 16 || bounds.getX() == 240 * 16)) || (bounds.getY() == 30 * 16 && bounds.getX() < 200 * 16) || (bounds.getY() == 45 * 16 && bounds.getX() > 200 * 16) || (bounds.getY() == 60 * 16 && (bounds.getX() == 160 * 16 || bounds.getX() == 180 * 16 || bounds.getX() == 240 * 16)) || (bounds.getY() == 75 * 16 && (bounds.getX() == 140 * 16 || bounds.getX() == 160 * 16 || bounds.getX() == 220 * 16));
        }
        else if (x <= bounds.getX() + 8)
        {
            fail = bounds.getX() == 140 * 16 || (bounds.getX() == 160 * 16 && (bounds.getY() == 0 || bounds.getY() == 30 * 16 || bounds.getY() == 60 * 16)) || (bounds.getX() == 180 * 16 && (bounds.getY() == 15 * 16 || bounds.getY() == 45 * 16)) || (bounds.getX() == 200 * 16 && bounds.getY() != 0 && bounds.getY() != 45 * 16) || (bounds.getX() == 220 * 16 && bounds.getY() != 45 * 16 && bounds.getY() != 90 * 16) || (bounds.getX() == 240 * 16 && (bounds.getY() == 15 * 16 || bounds.getY() == 45 * 16)) || (bounds.getX() == 260 * 16 && (bounds.getY() == 30 * 16 || bounds.getY() > 60 * 16));
        }
        else if (x >= bounds.getX() + bounds.getW() - 24)
        {
            fail = bounds.getX() == 260 * 16 || (bounds.getX() == 140 * 16 && (bounds.getY() == 0 || bounds.getY() == 30 * 16 || bounds.getY() == 60 * 16)) || (bounds.getX() == 160 * 16 && (bounds.getY() == 15 * 16 || bounds.getY() == 45 * 16)) || (bounds.getX() == 180 * 16 && bounds.getY() != 0 && bounds.getY() != 45 * 16) || (bounds.getX() == 200 * 16 && bounds.getY() != 45 * 16 && bounds.getY() != 90 * 16) || (bounds.getX() == 220 * 16 && (bounds.getY() == 15 * 16 || bounds.getY() == 45 * 16)) || (bounds.getX() == 240 * 16 && (bounds.getY() == 30 * 16 || bounds.getY() > 60 * 16));
        }
        if (fail)
        {
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, 69 * 16 + 8, 102 * 16, N, false, false, true);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            return false;
        }
    }

    return ((x <= bounds.getX() + 8 && bounds.getX() > 0) ||
            (y <= bounds.getY() && bounds.getY() > 0) ||
            (x >= bounds.getX() + bounds.getW() - 24 && bounds.getX() + bounds.getW() < w) ||
            (y >= bounds.getY() + bounds.getH() - 32 && bounds.getY() + bounds.getH() < h));
}

bool Map::testTeleport(int x, int y)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    switch (map)
    {
    case 1:
        if (y > 19 * 16 - 4 && scene->getAvancement() == AV_PIT_A_VOIR)
        {
            link->setY(link->getY() - 4);
            link->setDirection(N);
            MainController::getInstance()->getGameController()->displayText(176);
            return false;
        }
        if (x == 69 * 16 + 8 && y == 36 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, 49 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 12 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(29, 9 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        if (x == 9 * 16 + 8 && y == 7 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(30, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 53 * 16 + 8 && y == 38 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(31, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 41 * 16 + 8 && y == 11 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(44, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 2:
        if (x == 89 * 16 + 8 && y == 29 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(32, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 14 * 16 + 8 && y == 29 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(33, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 14 * 16 + 8 && y == 24 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(33, 9 * 16 + 8, 7 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 57 * 16 + 8 && y == 37 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(45, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 3:
        if (x == 72 * 16 + 8 && y == 14 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, 49 * 16 + 8, 102 * 16, N, false, true);
            return true;
        }
        if (x == 3 * 16 + 8 && y == 12 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(34, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 10 * 16 + 8 && y == 12 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(34, 29 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 8 * 16 + 8 && y == 4 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(34, 49 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 66 * 16 + 8 && y == 24 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(46, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 45 * 16 + 8 && y == 19 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(47, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 30 * 16 + 8 && y == 20 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(48, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 36 * 16 + 8 && y == 20 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(48, 29 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 16 * 16 + 8 && y == 38 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(49, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 22 * 16 + 8 && y == 38 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(49, 29 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 47 * 16 + 8 && y == 41 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(51, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 56 * 16 + 8 && y == 41 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(50, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 65 * 16 + 8 && y == 41 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(52, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 4:
        if (x == 35 * 16 + 8 && y == 19 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, 9 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        if (x == 35 * 16 + 8 && y == 29 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, 69 * 16 + 8, 117 * 16, N, false, true);
            return true;
        }
        if (x == 32 * 16 && y == 24 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, 29 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 && y == 24 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, 109 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        break;
    case 5:
        if ((x >= 21 * 16 && x <= 22 * 16) && y == 12 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, 9 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        if ((x >= 21 * 16 && x <= 22 * 16) && y == 18 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, 109 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        if (x == 25 * 16 + 8 && y == 68 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(39, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 14 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(41, 9 * 16 + 8, 27 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 42 * 16 + 8 && y == 72 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(40, 9 * 16 + 8, 7 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 53 * 16 + 8 && y == 70 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(40, 46 * 16 + 8, 7 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 176 * 16 + 8 && y == 70 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(71, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 6:
        if (x == 46 * 16 + 8 && y == 29 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, 49 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        if (x == 92 * 16 + 8 && y == 31 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(37, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 88 * 16 + 8 && y == 25 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(37, 5 * 16 + 8, 8 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        break;
    case 7:
        if (x == 19 * 16 + 8 && y == 16 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(53, 9 * 16 + 8, 16, S, false, true);
            return true;
        }
        if (x == 19 * 16 + 8 && y == 23 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(53, 9 * 16 + 8, 27 * 16, N, false, true);
            return true;
        }
        if (x == 34 * 16 + 8 && y == 20 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(54, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 38 * 16 + 8 && y == 6 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(55, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 44 * 16 + 8 && y == 6 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(55, 29 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 57 * 16 + 8 && y == 6 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(56, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 20 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(57, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 32 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(58, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 64 * 16 + 8 && y == 32 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(59, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 64 * 16 + 8 && y == 20 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(60, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 8:
        if ((x >= 26 * 16 && x <= 27 * 16) && y == 39 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, 169 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        if (x == 21 * 16 && y == 7 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, 39 * 16 + 8, 117 * 16, N, false, true);
            return true;
        }
        if (x == 21 * 16 + 8 && y == 20 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(38, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 26 * 16 + 8 && y == 16 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(38, 13 * 16 + 8, 8 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        break;
    case 9:
        if (x == 39 * 16 + 8 && y == 26 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, 119 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 86 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(35, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 10:
        if (x == 24 * 16 + 8 && y == 38 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(36, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 45 * 16 + 8 && y == 51 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(61, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 11:
        if (x == 8 * 16 && y == 49 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, 89 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        if (x == 40 * 16 + 8 && y == 17 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(62, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 51 * 16 + 8 && y == 31 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(63, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 30 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(64, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 65 * 16 + 8 && y == 21 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(65, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 13 * 16 + 8 && y == 21 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(66, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 12:
        if (x == 39 * 16 + 8 && y == 13 * 16 + 8 && (link->getEpee() < 5 || !link->getInventory()->hasObject(MASQUE_VIDE) || !link->getInventory()->hasObject(CHANT_3)))
        {
            link->setY(link->getY() + 4);
            link->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(348);
            return false;
        }
        if (x == 39 * 16 + 8 && y == 13 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, 69 * 16 + 8, 102 * 16, N, false, true);
            return true;
        }
        break;
    case 13:
        if (x == 26 * 16 + 8 && y == 23 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(67, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 38 * 16 + 8 && y == 28 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(68, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 55 * 16 + 8 && y == 26 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(69, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 48 * 16 + 8 && y == 33 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(70, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 14:
        if (x == 16 * 16 + 8 && y == 55 * 16 + 8 && scene->getAvancement() == AV_ARMEE_UP)
        {
            link->setY(link->getY() + 4);
            link->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(384);
            return false;
        }
        if (x == 60 * 16 && y == 33 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(19, 49 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        if (x == 20 * 16 + 8 && y == 18 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(24, 149 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        if (x == 136 * 16 + 8 && y == 3 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, 49 * 16 + 8, 147 * 16, N, false, true);
            return true;
        }
        if (x == 94 * 16 + 8 && y == 34 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(42, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 16 * 16 + 8 && y == 55 * 16 + 8)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(43, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 13 * 16 + 8 && y == 50 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(43, 4 * 16 + 8, 5 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        break;
    case 15:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 69 * 16 + 8, 37 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 6 * 16) || (x == 9 * 16 + 8 && y == 36 * 16) || (x == 9 * 16 + 8 && y == 51 * 16) || (x == 69 * 16 + 8 && y == 6 * 16) || (x == 69 * 16 + 8 && y == 36 * 16) || (x == 89 * 16 + 8 && y == 51 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 6 * 16) || (x == 109 * 16 + 8 && y == 36 * 16) || (x == 109 * 16 + 8 && y == 51 * 16) || (x == 169 * 16 + 8 && y == 6 * 16) || (x == 169 * 16 + 8 && y == 36 * 16) || (x == 189 * 16 + 8 && y == 51 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 16:
        if (y >= h - 32 && link->getStatus()->isOniLink())
        {
            link->setY(link->getY() - 4);
            link->setDirection(N);
            MainController::getInstance()->getGameController()->displayText(292);
            return false;
        }
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 72 * 16 + 8, 15 * 16 + 8, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 21 * 16) || (x == 49 * 16 + 8 && y == 66 * 16) || (x == 49 * 16 + 8 && y == 96 * 16) || (x == 109 * 16 + 8 && y == 66 * 16) || (x == 169 * 16 + 8 && y == 81 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 21 * 16) || (x == 149 * 16 + 8 && y == 66 * 16) || (x == 149 * 16 + 8 && y == 96 * 16) || (x == 209 * 16 + 8 && y == 66 * 16) || (x == 269 * 16 + 8 && y == 81 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 17:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 35 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        if (y >= 240 * 4 - 32 && bounds.getX() == 0)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 35 * 16 + 8, 20 * 16 + 8, S, false, true);
            return true;
        }
        if (y >= 240 * 6 - 32 && bounds.getX() == 320)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 32 * 16, 24 * 16 + 8, S, false, true);
            return true;
        }
        if (y >= 240 * 6 - 32 && bounds.getX() == 320 * 5)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 39 * 16, 24 * 16 + 8, S, false, true);
            return true;
        }
        // escaliers
        if (x == 9 * 16 + 8 && y == 51 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, x + 60 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 29 * 16 + 8 && y == 81 * 16) || (x == 49 * 16 + 8 && y == 66 * 16) || (x == 49 * 16 + 8 && y == 111 * 16) || (x == 69 * 16 + 8 && y == 66 * 16) || (x == 69 * 16 + 8 && y == 111 * 16) || (x == 89 * 16 + 8 && y == 81 * 16) || (x == 89 * 16 + 8 && y == 111 * 16) || (x == 109 * 16 + 8 && y == 81 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 69 * 16 + 8 && y == 51 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, x - 60 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 149 * 16 + 8 && y == 81 * 16) || (x == 169 * 16 + 8 && y == 66 * 16) || (x == 169 * 16 + 8 && y == 111 * 16) || (x == 189 * 16 + 8 && y == 66 * 16) || (x == 189 * 16 + 8 && y == 111 * 16) || (x == 209 * 16 + 8 && y == 81 * 16) || (x == 209 * 16 + 8 && y == 111 * 16) || (x == 229 * 16 + 8 && y == 81 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 18:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 26 * 16 + 8, 40 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 29 * 16 + 8 && y == 21 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x + 60 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 && y == 36 * 16) || (x == 109 * 16 + 8 && y == 51 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 169 * 16 + 8 && y == 51 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 89 * 16 + 8 && y == 21 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x - 60 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 169 * 16 + 8 && y == 36 * 16) || (x == 189 * 16 + 8 && y == 51 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 269 * 16 + 8 && y == 51 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 19:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 60 * 16, 34 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 49 * 16 + 8 && y == 36 * 16) || (x == 49 * 16 + 8 && y == 66 * 16) || (x == 69 * 16 + 8 && y == 66 * 16) || (x == 95 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(19, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 149 * 16 + 8 && y == 36 * 16) || (x == 149 * 16 + 8 && y == 66 * 16) || (x == 169 * 16 + 8 && y == 66 * 16) || (x == 195 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(19, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 20:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 8 * 16, 51 * 16 + 8, S, false, true);
            return true;
        }
        // escaliers
        if (x == 9 * 16 + 8 && y == 52 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 49 * 16 + 8 && y == 6 * 16) || (x == 69 * 16 + 8 && y == 81 * 16) || (x == 109 * 16 + 8 && y == 81 * 16) || (x == 129 * 16 + 8 && y == 6 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 89 * 16 + 8 && y == 52 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 169 * 16 + 8 && y == 6 * 16) || (x == 189 * 16 + 8 && y == 81 * 16) || (x == 229 * 16 + 8 && y == 81 * 16) || (x == 249 * 16 + 8 && y == 6 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 21:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 46 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 51 * 16) || (x == 49 * 16 + 8 && y == 51 * 16) || (x == 149 * 16 + 8 && y == 36 * 16) || (x == 189 * 16 + 8 && y == 6 * 16) || (x == 189 * 16 + 8 && y == 21 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 51 * 16) || (x == 149 * 16 + 8 && y == 51 * 16) || (x == 249 * 16 + 8 && y == 36 * 16) || (x == 289 * 16 + 8 && y == 6 * 16) || (x == 289 * 16 + 8 && y == 21 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 22:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 39 * 16 + 8, 27 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 81 * 16) || (x == 29 * 16 + 8 && y == 21 * 16) || (x == 69 * 16 + 8 && y == 36 * 16) || (x == 69 * 16 + 8 && y == 81 * 16) || (x == 89 * 16 + 8 && y == 36 * 16) || (x == 89 * 16 + 8 && y == 51 * 16) || (x == 89 * 16 + 8 && y == 66 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 51 * 16) || (x == 149 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 && y == 81 * 16) || (x == 109 * 16 + 8 && y == 21 * 16) || (x == 149 * 16 + 8 && y == 36 * 16) || (x == 149 * 16 + 8 && y == 81 * 16) || (x == 169 * 16 + 8 && y == 36 * 16) || (x == 169 * 16 + 8 && y == 51 * 16) || (x == 169 * 16 + 8 && y == 66 * 16) || (x == 209 * 16 + 8 && y == 6 * 16) || (x == 229 * 16 + 8 && y == 6 * 16) || (x == 229 * 16 + 8 && y == 51 * 16) || (x == 229 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 23:
        if (y >= h - 32 && x < 20 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 21 * 16 + 8, 13 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 20 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 21 * 16 + 8, 19 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 || x == 49 * 16 + 8) && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, x + 80 * 16, y + 15 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 69 * 16 + 8 && y == 36 * 16) || (x == 89 * 16 + 8 && y == 6 * 16) || (x == 89 * 16 + 8 && y == 51 * 16) || (x == 109 * 16 + 8 && y == 66 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 36 * 16) || (x == 129 * 16 + 8 && y == 51 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 || x == 129 * 16 + 8) && y == 21 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, x - 80 * 16, y - 15 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 169 * 16 + 8 && y == 36 * 16) || (x == 189 * 16 + 8 && y == 6 * 16) || (x == 189 * 16 + 8 && y == 51 * 16) || (x == 209 * 16 + 8 && y == 66 * 16) || (x == 229 * 16 + 8 && y == 6 * 16) || (x == 229 * 16 + 8 && y == 36 * 16) || (x == 229 * 16 + 8 && y == 51 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 24:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 20 * 16 + 8, 18 * 16 + 8, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 6 * 16) || (x == 29 * 16 + 8 && y == 36 * 16) || (x == 49 * 16 + 8 && y == 36 * 16) || (x == 69 * 16 + 8 && y == 21 * 16) || (x == 89 * 16 + 8 && y == 51 * 16) || (x == 149 * 16 + 8 && y == 6 * 16) || (x == 169 * 16 + 8 && y == 66 * 16) || (x == 189 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(24, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 36 * 16) || (x == 149 * 16 + 8 && y == 36 * 16) || (x == 169 * 16 + 8 && y == 21 * 16) || (x == 189 * 16 + 8 && y == 51 * 16) || (x == 249 * 16 + 8 && y == 6 * 16) || (x == 269 * 16 + 8 && y == 66 * 16) || (x == 289 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(24, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 25:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 21 * 16, 8 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 51 * 16) || (x == 9 * 16 + 8 && y == 111 * 16) || (x == 69 * 16 + 8 && y == 21 * 16) || (x == 69 * 16 + 8 && y == 111 * 16) || (x == 89 * 16 + 8 && y == 96 * 16) || (x == 109 * 16 + 8 && y == 81 * 16) || (x == 129 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 6 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, x - 80 * 16, y + 60 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 && y == 51 * 16) || (x == 89 * 16 + 8 && y == 111 * 16) || (x == 149 * 16 + 8 && y == 21 * 16) || (x == 149 * 16 + 8 && y == 111 * 16) || (x == 169 * 16 + 8 && y == 96 * 16) || (x == 189 * 16 + 8 && y == 81 * 16) || (x == 209 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 29 * 16 + 8 && y == 66 * 16) || (x == 69 * 16 + 8 && y == 66 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, x + 80 * 16, y - 60 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 == 48 && (y + 16) / 16 == 82 && sol[48][82] == 3601)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, 188 * 16, 22 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if ((x + 8) / 16 == 191 && (y + 16) / 16 == 22 && sol[191][22] == 3601)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, 51 * 16, 82 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 26:
        if (y >= h - 32 && x < 140 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12, 39 * 16 + 8, 14 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 6 * 16) || (x == 9 * 16 + 8 && y == 96 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 96 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x + 140 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 149 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 96 * 16) || (x == 269 * 16 + 8 && y == 6 * 16) || (x == 269 * 16 + 8 && y == 96 * 16))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x - 140 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 >= 69 && (x + 8) / 16 <= 70 && (y + 16) / 16 == 82)
        {
            int randomV = (scene->getCoffre(12, 0) && !scene->getCoffre(12, 1)) ? 4 : rand() % 4;
            switch (randomV)
            {
            case 0:
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x - 60 * 16, y - 72 * 16, link->getDirection(), false, false, true);
                break;
            case 1:
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x + 60 * 16, y - 72 * 16, link->getDirection(), false, false, true);
                break;
            case 2:
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x - 60 * 16, y + 18 * 16, link->getDirection(), false, false, true);
                break;
            case 3:
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x + 60 * 16, y + 18 * 16, link->getDirection(), false, false, true);
                break;
            case 4:
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, x, y - 27 * 16, link->getDirection(), false, false, true);
                break;
            }
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 27:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(45, 29 * 16 + 8, 8, S, false, true);
            return true;
        }
        break;
    case 28:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 136 * 16 + 8, 4 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 29 * 16 + 8 && y == 66 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, x + 100 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 169 * 16 + 8 && y == 66 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, x - 100 * 16, y + 75 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 129 * 16 + 8 && y == 66 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, x - 100 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 69 * 16 + 8 && y == 141 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, x + 100 * 16, y - 75 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 >= 49 && (x + 8) / 16 <= 50 && (y + 16) / 16 == 111)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, 149 * 16 + 8, 113 * 16, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 29:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 29 * 16 + 8, 13 * 16, S, false, true);
            return true;
        }
        break;
    case 30:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 9 * 16 + 8, 8 * 16, S, false, true);
            return true;
        }
        break;
    case 31:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 53 * 16 + 8, 39 * 16, S, false, true);
            return true;
        }
        break;
    case 32:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(2, 89 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        break;
    case 33:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(2, 14 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 9 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(2, 14 * 16 + 8, 25 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 34:
        if (y >= h - 32 && x < 320)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 3 * 16 + 8, 13 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x < 320 * 2)
        {
            if (link->getStatus()->isOniLink())
            {
                link->setY(link->getY() - 4);
                link->setDirection(N);
                MainController::getInstance()->getGameController()->displayText(292);
                return false;
            }
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 10 * 16 + 8, 13 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 8 * 16 + 8, 5 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 49 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(34, x - 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(34, x + 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 35:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 39 * 16 + 8, 87 * 16, S, false, true);
            return true;
        }
        break;
    case 36:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(10, 24 * 16 + 8, 39 * 16, S, false, true);
            return true;
        }
        break;
    case 37:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 92 * 16 + 8, 32 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 5 * 16 + 8 && y == 7 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 88 * 16 + 8, 26 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 38:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 21 * 16 + 8, 21 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 13 * 16 + 8 && y == 7 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 26 * 16 + 8, 17 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 39:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 25 * 16 + 8, 69 * 16, S, false, true);
            return true;
        }
        break;
    case 40:
        // escaliers
        if (x == 52 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(40, x - 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 32 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(40, x + 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 9 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 42 * 16 + 8, 73 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 46 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 53 * 16 + 8, 71 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 41:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 63 * 16 + 8, 15 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 9 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(41, x + 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 6 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(41, x - 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 42:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 94 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        break;
    case 43:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 16 * 16 + 8, 56 * 16, S, false, true);
            return true;
        }
        if (x == 4 * 16 + 8 && y == 4 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 13 * 16 + 8, 51 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 44:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 41 * 16 + 8, 12 * 16, S, false, true);
            return true;
        }
        break;
    case 45:
        if (y <= 0)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(27, 29 * 16 + 8, 132 * 16, N, false, true);
            return true;
        }
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(2, 57 * 16 + 8, 38 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 13 * 16 + 8 && y == 10 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(45, x + 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 33 * 16 + 8 && y == 10 * 16)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(45, x - 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 46:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 66 * 16 + 8, 25 * 16, S, false, true);
            return true;
        }
        break;
    case 47:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 45 * 16 + 8, 20 * 16, S, false, true);
            return true;
        }
        break;
    case 48:
        if (y >= h - 32 && x < 320)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 30 * 16 + 8, 21 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 36 * 16 + 8, 21 * 16, S, false, true);
            return true;
        }
        break;
    case 49:
        if (y >= h - 32 && x < 320)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 16 * 16 + 8, 39 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 22 * 16 + 8, 39 * 16, S, false, true);
            return true;
        }
        break;
    case 50:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 56 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        break;
    case 51:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 47 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        break;
    case 52:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 65 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        break;
    case 53:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 19 * 16 + 8, 24 * 16, S, false, true);
            return true;
        }
        if (y <= 0)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 19 * 16 + 8, 16 * 16, N, false, true);
            return true;
        }
        break;
    case 54:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 34 * 16 + 8, 21 * 16, S, false, true);
            return true;
        }
        break;
    case 55:
        if (y >= h - 32 && x < 320)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 38 * 16 + 8, 7 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 44 * 16 + 8, 7 * 16, S, false, true);
            return true;
        }
        break;
    case 56:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 57 * 16 + 8, 7 * 16, S, false, true);
            return true;
        }
        break;
    case 57:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 49 * 16 + 8, 21 * 16, S, false, true);
            return true;
        }
        break;
    case 58:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 49 * 16 + 8, 33 * 16, S, false, true);
            return true;
        }
        break;
    case 59:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 64 * 16 + 8, 33 * 16, S, false, true);
            return true;
        }
        break;
    case 60:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 64 * 16 + 8, 21 * 16, S, false, true);
            return true;
        }
        break;
    case 61:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(10, 45 * 16 + 8, 51 * 16 + 8, S, false, true);
            return true;
        }
        break;
    case 62:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 40 * 16 + 8, 18 * 16, S, false, true);
            return true;
        }
        break;
    case 63:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 51 * 16 + 8, 32 * 16, S, false, true);
            return true;
        }
        break;
    case 64:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 29 * 16 + 8, 31 * 16, S, false, true);
            return true;
        }
        break;
    case 65:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 65 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        break;
    case 66:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 13 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        break;
    case 67:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 26 * 16 + 8, 24 * 16, S, false, true);
            return true;
        }
        break;
    case 68:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 38 * 16 + 8, 29 * 16, S, false, true);
            return true;
        }
        break;
    case 69:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 55 * 16 + 8, 27 * 16, S, false, true);
            return true;
        }
        break;
    case 70:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 48 * 16 + 8, 34 * 16, S, false, true);
            return true;
        }
        break;
    case 71:
        if (y >= h - 32)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 176 * 16 + 8, 71 * 16, S, false, true);
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

void Map::testAnim(int x, int y, Direction dir, bool sound)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // open door
    if ((getSol(x, y + 8 - 1) == 468 || getSol(x, y + 8 - 1) == 789 || getSol(x, y + 8 - 1) == 790) && dir == N)
    {
        ouvrePorteMaison(x, y);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
    }
    // open door dungeon
    if ((getSol(x, y + 8 - 1) == 1362 || getSol(x, y + 8 - 1) == 1363) && dir == N)
    {
        ouvrePorte(x, y, 0);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
    }

    if (map == 9 && scene->getAvancement() == AV_ARMEE_UP && nbEnnemis() == 0)
    {
        MainController::getInstance()->getGameController()->displayText(247);
        if (sound)
            AudioManager::getInstance()->playMusic(music);
    }

    if (map >= 15 && map < 29)
    {

        // doors with keys
        if (scene->getCoffre(map - 14, 3))
        {
            int i = 0;
            int j = 0;

            switch (map)
            {
            case 15:
                if (getSol(x, y + 7) == 1689 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 1693 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 1702 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 1708 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 16:
            case 20:
                if (getSol(x, y + 7) == 1894 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 1896 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 1903 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 1908 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 17:
                if (getSol(x, y + 7) == 2054 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 2056 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                break;
            case 18:
                if (getSol(x, y + 7) == 2254 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 2256 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 2263 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 2268 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 19:
                if (getSol(x, y + 7) == 2441 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 2443 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 2450 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 2455 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 21:
                if (getSol(x, y + 7) == 2636 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 2640 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 2649 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 2655 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 22:
                if (getSol(x, y + 7) == 2848 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 2850 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 2857 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 2862 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 23:
                if (getSol(x, y + 7) == 3094 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 3096 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 3103 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 3108 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 24:
                if (getSol(x - 1, y + 16) == 3258 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 3263 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 25:
                if (getSol(x, y + 7) == 3428 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 3430 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 3437 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 3442 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 26:
                if ((getSol(x, y + 7) == 3716 || getSol(x, y + 7) == 3873) && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 3718 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 3725 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 3730 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 27:
                if (getSol(x, y + 7) == 3968 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 3970 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 3977 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 3982 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 28:
                if (getSol(x, y + 7) == 4099 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 4101 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 4108 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 4113 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            }

            if (i != 0)
            {
                int k = 0;
                switch (map)
                {
                case 15:
                    if (bounds.getX() == 320)
                        k = 8;
                    else if (bounds.getX() == 320 * 2)
                        k = 9;
                    else if (bounds.getX() == 320 * 5)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 16:
                    if (bounds.getX() == 320 * 5)
                        k = 9;
                    else if (bounds.getY() == 240 * 4 && scene->getLink()->getX() < 129 * 16)
                        k = 10;
                    else if (bounds.getY() == 240 * 5)
                        k = 11;
                    else if (bounds.getY() == 240 * 4 && scene->getLink()->getX() >= 129 * 16)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 17:
                    if (bounds.getY() == 240)
                        k = 8;
                    else if (bounds.getY() == 240 * 3)
                        k = 9;
                    else if (bounds.getY() == 240 * 5)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 18:
                    if (bounds.getX() == 320 * 5 && bounds.getY() == 240)
                        k = 12;
                    else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 3)
                        k = 13;
                    else if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 2)
                        k = 14;
                    else if (bounds.getX() == 320 * 6 && bounds.getY() == 0)
                        k = 15;
                    else if (bounds.getX() == 320 * 13 && bounds.getY() == 240 * 2)
                        k = 16;
                    else if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 4)
                        k = 17;
                    else if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 2 && scene->getLink()->getX() < 299 * 16)
                        k = 18;
                    else
                        k = 19;
                    break;
                case 19:
                    if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 3)
                        k = 9;
                    else if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 4)
                        k = 10;
                    else if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 2)
                        k = 11;
                    else if (bounds.getX() == 320 * 7 && bounds.getY() == 0)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 20:
                    if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3 && scene->getLink()->getX() < 90 * 16)
                        k = 18;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2 && scene->getLink()->getX() < 90 * 16 && scene->getLink()->getY() > 37 * 16)
                        k = 19;
                    else if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2)
                        k = 20;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2 && scene->getLink()->getX() < 90 * 16 && scene->getLink()->getY() < 37 * 16)
                        k = 21;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && scene->getLink()->getX() < 90 * 16 && scene->getLink()->getY() > 22 * 16)
                        k = 22;
                    else if (bounds.getX() == 320 * 3 && bounds.getY() == 240)
                        k = 23;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && scene->getLink()->getX() < 90 * 16 && scene->getLink()->getY() < 22 * 16)
                        k = 24;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 0)
                        k = 25;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && scene->getLink()->getX() > 90 * 16 && scene->getLink()->getY() < 22 * 16)
                        k = 26;
                    else if (bounds.getX() == 320 * 5 && bounds.getY() == 240)
                        k = 27;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && scene->getLink()->getX() > 90 * 16 && scene->getLink()->getY() > 22 * 16)
                        k = 28;
                    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2 && scene->getLink()->getX() > 90 * 16 && scene->getLink()->getY() < 37 * 16)
                        k = 29;
                    else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 2)
                        k = 30;
                    else
                        k = 31;
                    break;
                case 21:
                    if (bounds.getX() == 320 && bounds.getY() == 240 * 2)
                        k = 11;
                    else if (bounds.getX() == 320 && bounds.getY() == 240)
                        k = 12;
                    else if (bounds.getX() == 320 * 6 && bounds.getY() == 240)
                        k = 13;
                    else if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 3)
                        k = 14;
                    else if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 3)
                        k = 15;
                    else if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 2)
                        k = 16;
                    else
                        k = 17;
                    break;
                case 22:
                    if (bounds.getX() == 320 && bounds.getY() == 240 * 2 && scene->getLink()->getX() < 55 * 16)
                        k = 10;
                    else if (bounds.getX() == 320 && bounds.getY() == 240 * 2 && scene->getLink()->getX() > 55 * 16)
                        k = 11;
                    else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 5 && scene->getLink()->getX() < 120 * 16)
                        k = 12;
                    else if (bounds.getX() == 320 * 6 && bounds.getY() == 240 && scene->getLink()->getX() < 140 * 16)
                        k = 13;
                    else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 5 && scene->getLink()->getX() > 120 * 16)
                        k = 14;
                    else
                        k = 15;
                    break;
                case 23:
                    if (bounds.getX() == 320 * 2)
                        k = 8;
                    else if (bounds.getY() == 240 * 4)
                        k = 9;
                    else if (bounds.getX() == 320 * 8)
                        k = 11;
                    else
                        k = 10;
                    break;
                case 24:
                    if (bounds.getX() == 320)
                        k = 9;
                    else if (bounds.getX() == 0)
                        k = 10;
                    else if (bounds.getX() == 320 * 3)
                        k = 11;
                    else if (bounds.getX() == 320 * 7)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 25:
                    if (bounds.getX() == 0)
                        k = 9;
                    else if (bounds.getX() == 320 && scene->getLink()->getX() < 25 * 16)
                        k = 10;
                    else if (bounds.getX() == 320 && bounds.getY() == 240 * 3)
                        k = 11;
                    else if (bounds.getX() == 320)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 26:
                    if (bounds.getX() == 320)
                        k = 9;
                    else if (bounds.getX() == 320 * 3 && scene->getLink()->getX() < 70 * 16)
                        k = 10;
                    else if (bounds.getX() == 320 * 3)
                        k = 11;
                    else if (bounds.getX() == 320 * 5)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 27:
                    if (bounds.getX() == 320)
                        k = 8;
                    else if (bounds.getX() == 320 * 4)
                        k = 9;
                    else if (bounds.getX() == 320 * 5)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 28:
                    if (bounds.getX() == 320 * 2)
                        k = 7;
                    else if (bounds.getX() == 320 * 3)
                        k = 8;
                    else
                        k = 9;
                    break;
                }
                if (k != 0)
                {
                    scene->setCoffre(map - 14, k, 1);
                }

                ouvrePorte(i, j, (dir == N || dir == S) ? 0 : 1);
                if (sound)
                    AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(map - 14, 3, scene->getCoffre(map - 14, 3) - 1);
            }
        }
        // boss
        if (scene->getCoffre(map - 14, 2) == 1 && dir == N)
        {
            int value = false;
            switch (map)
            {
            case 15:
                value = 1719;
                break;
            case 16:
            case 20:
                value = 1934;
                break;
            case 17:
                value = 2062;
                break;
            case 18:
                value = 2274;
                break;
            case 19:
                value = 2461;
                break;
            case 21:
                value = 2668;
                break;
            case 22:
                value = 2888;
                break;
            case 23:
                value = 3134;
                break;
            case 24:
                value = 3289;
                break;
            case 25:
                value = 3468;
                break;
            case 26:
                value = 3889;
                break;
            case 27:
                value = 4008;
                break;
            case 28:
                value = 4139;
                break;
            }
            if (getSol(x, y + 7) == value)
            {
                ouvrePorte(x / 16, ((y + 7) / 16) - 3, 0);
                if (sound)
                    AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(map - 14, 2, 2);
            }
        }
    }
}

void Map::ouvrePorteMaison(int x, int y)
{
    int i = x / 16;
    int j = (y + 8 - 1) / 16;

    setSol(x, y + 8 - 1, 474, SOL_BOIS);
    setSol(x + 16, y + 8 - 1, 475, SOL_BOIS);

    mur[i * 2][j * 2] = MUR;
    mur[i * 2][j * 2 + 1] = MUR;
    mur[i * 2 + 3][j * 2] = MUR;
    mur[i * 2 + 3][j * 2 + 1] = MUR;
}

void Map::testAnimRoom()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    switch (map)
    {
    case 15:
        if (bounds.getX() == 0 && bounds.getY() == 240 && mur[9 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 13, 0);
        }
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 && mur[109 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 28, 0);
        }
        if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 2 && mur[129 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 28, 0);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 0 && mur[40 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 6, 1);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 3 && mur[80 * 2][52 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 51, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 0 && mur[160 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 6, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(0) && mur[89 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                persistJarres();
                fermePorte(89, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(0) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(0) && mur[89 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 13, 0);
            }
            else if (link->getInventory()->hasGraal(0) && mur[89 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 28, 0);
            }
        }
        break;
    case 16:
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2 && mur[89 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 28, 0);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 && mur[160 * 2][22 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 21, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 5 && mur[149 * 2 + 1][73 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 73, 0);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 2 && mur[189 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 28, 0);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 3 && mur[240 * 2][52 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 51, 1);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 5)
        {
            if (!link->getInventory()->hasCoeur(1) && mur[249 * 2 + 1][88 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(249, 88, 0);
            }
            else if (!link->getInventory()->hasCoeur(1) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(1) && mur[249 * 2 + 1][73 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 73, 0);
            }
            else if (link->getInventory()->hasObject(BOMBES) && mur[249 * 2 + 1][88 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 88, 0);
            }
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 4 && mur[249 * 2 + 1][73 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 73, 0);
        }
        break;
    case 17:
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 7 && mur[149 * 2 + 1][103 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 103, 0);
        }
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(2) && mur[9 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(9, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(2) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(2) && mur[9 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(9, 28, 0);
            }
            else if (link->getInventory()->hasGraal(1) && mur[9 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(9, 43, 0);
            }
        }
        break;
    case 18:
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 2 && mur[109 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 28, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() <= 240 && mur[169 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 13, 0);
        }
        if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() == 240 * 2 && mur[200 * 2][37 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 36, 1);
        }
        if (bounds.getX() == 320 * 13 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(3) && mur[269 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(23);
                fermePorte(269, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(3) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(3) && mur[269 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(269, 13, 0);
            }
            else if (scene->getAvancement() >= AV_FILLE_MAIRE_SAUVEE && mur[269 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(269, 28, 0);
            }
        }
        break;
    case 19:
        if (bounds.getX() == 320 * 2 && bounds.getY() <= 240 && mur[49 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 13, 0);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(4) && mur[89 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(89, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(4) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(4) && mur[89 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 13, 0);
            }
            else if (link->getInventory()->hasGraal(2) && mur[89 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 43, 0);
            }
        }
        break;
    case 20:
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 5 && mur[89 * 2 + 1][73 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 73, 0);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3 && mur[80 * 2][67 * 2] == MUR && scene->getCoffre(6, 9))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 66, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3 && mur[100 * 2][67 * 2] == MUR && scene->getCoffre(6, 8))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 66, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3 && mur[80 * 2][52 * 2] == MUR && scene->getCoffre(6, 11))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 51, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3 && mur[100 * 2][52 * 2] == MUR && scene->getCoffre(6, 7))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 51, 1);
        }
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(5) && mur[9 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(9, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(5) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(5) && mur[9 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(9, 28, 0);
            }
            else if (link->getInventory()->hasObject(GRAPPIN) && mur[9 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(9, 43, 0);
            }
        }
        break;
    case 21:
        if (bounds.getX() <= 320 && bounds.getY() == 0 && mur[20 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 6, 1);
        }
        if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 0 && mur[120 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 6, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() >= 240 * 2 && mur[89 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 43, 0);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() >= 240 * 2 && mur[189 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 43, 0);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(6) && mur[249 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(249, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(6) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(6) && mur[249 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 13, 0);
            }
            else if (link->getInventory()->hasGraal(3) && mur[249 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 28, 0);
            }
        }
        break;
    case 22:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 4 && mur[20 * 2][67 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 66, 1);
        }
        if (bounds.getX() == 320 * 11 && bounds.getY() == 240 * 2 && mur[229 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 28, 0);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(7) && mur[89 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(89, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(7) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(7) && mur[89 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 13, 0);
            }
            else if (link->getInventory()->hasGraal(4) && mur[89 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 28, 0);
            }
        }
        break;
    case 23:
        if (bounds.getX() == 0 && bounds.getY() <= 240 && mur[9 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 13, 0);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() <= 240 && mur[69 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 13, 0);
        }
        if (((bounds.getX() == 320 * 3 && bounds.getY() == 240 * 3) || (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 4)) && mur[80 * 2][67 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 66, 1);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 0 && mur[169 * 2 + 1][13 * 2 + 1] != MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            fermePorte(169, 13, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240 && mur[169 * 2 + 1][13 * 2 + 1] == MUR)
        {
            ouvrePorte(169, 13, 0);
        }
        if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(8) && mur[209 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(209, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(8) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(8) && mur[209 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(209, 28, 0);
            }
            else if (scene->getCoffre(9, 27) && mur[209 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(209, 43, 0);
            }
        }
        break;
    case 24:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && mur[9 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 43, 0);
        }
        if (bounds.getX() == 320 * 6 && bounds.getY() >= 240 * 3 && mur[129 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 58, 0);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3 && mur[249 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 43, 0);
        }
        if (bounds.getX() == 320 * 13 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2 && mur[269 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(269, 28, 0);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(9) && mur[49 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(49, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(9) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(9) && mur[49 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 13, 0);
            }
            else if (scene->getCoffre(10, 27) && mur[49 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 28, 0);
            }
        }
        break;
    case 25:
        if (bounds.getX() == 320 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5 && mur[29 * 2 + 1][73 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 73, 0);
        }
        if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240 * 4 && mur[140 * 2][67 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 66, 1);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 7 && mur[200 * 2][112 * 2] == MUR && scene->getCoffre(11, 23) == 4 && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 111, 1);
            scene->setCoffre(11, 23, 5);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 5)
        {
            if (!link->getInventory()->hasCoeur(10) && mur[49 * 2 + 1][88 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                fermePorte(49, 88, 0);
            }
            else if (link->getInventory()->hasCoeur(10) && mur[49 * 2 + 1][73 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 73, 0);
            }
            else if (scene->getCoffre(11, 24) && mur[49 * 2 + 1][88 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 88, 0);
            }
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 && !link->getInventory()->hasCoeur(10) && nbEnnemis() == 0)
        {
            AudioManager::getInstance()->playMusic(20);
            setSol(191 * 16, 22 * 16, 3601);
        }
        break;
    case 26:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && mur[9 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 28, 0);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 3 && mur[40 * 2][52 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 51, 1);
        }
        if (bounds.getX() == 320 * 15 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(11) && mur[309 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(34);
                fermePorte(309, 43, 0);
                scene->getAnimationInGame()->startAnim(5);
            }
            else if (!link->getInventory()->hasCoeur(11) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->setPreviousMusic(33);
            }
            else if (link->getInventory()->hasCoeur(11) && mur[309 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(309, 28, 0);
            }
            else if (scene->getAvancement() >= AV_GANON_VU && mur[309 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(309, 43, 0);
            }
        }
        if (bounds.getX() == 320 * 15 && bounds.getY() == 240 && scene->getAvancement() < AV_GANON_VU)
        {
            scene->getAnimationInGame()->startAnim(6);
        }
        break;
    case 27:
        if (bounds.getX() == 320 && bounds.getY() == 0 && mur[20 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 6, 1);
        }
        if (bounds.getX() == 320 && bounds.getY() == 240 * 3)
        {
            if (!link->getInventory()->hasCoeur(12) && mur[29 * 2 + 1][58 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(29, 58, 0);
            }
            else if (!link->getInventory()->hasCoeur(12) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(12) && mur[29 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(29, 43, 0);
            }
            else if (link->getInventory()->hasObject(ARC_FEE) && mur[29 * 2 + 1][58 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(29, 58, 0);
            }
        }
        break;
    case 28:
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 2 && mur[120 * 2][37 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 36, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 0 && mur[149 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 13, 0);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 2 && mur[180 * 2][37 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 36, 1);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 8)
        {
            if (!scene->getCoffre(14, 13) && mur[49 * 2 + 1][133 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(49, 133, 0);
            }
            else if (!scene->getCoffre(14, 13) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(14, 13, 1);
                ouvrePorte(49, 118, 0);
                ouvrePorte(49, 133, 0);
            }
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 7)
        {
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(28);
            }
            else
            {
                AudioManager::getInstance()->playMusic(20);
            }
        }
        break;
    }
}

void Map::addCoffre(int x, int y, TypeItem type, int id)
{
    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    addObject(new Coffre(x, y, 0, false, type, id));
    BoundingBox b(x, y, 16, 16);
    if (b.intersect(link->getBoundingBox()))
    {
        link->setY(y - 24);
    }
}

void Map::permuteBlocs(int step)
{
    // 1 = orange up - blue down
    switch (map)
    { // 624 to 627, orange = 624, blue = 625, +2 = up
    case 7:
        if (step == 0)
        {
            setSol(8 * 16, 42 * 16, 1, 4, 627, MURRET);
        }
        else
        {
            setSol(8 * 16, 42 * 16, 1, 4, 625, PIERRE);
        }
        break;
    case 19:
        if (step == 0)
        {
            setSol(19 * 16, 19 * 16, 1, 3, 624, PIERRE);
            setSol(31 * 16, 22 * 16, 3, 1, 624, PIERRE);
            setSol(35 * 16, 35 * 16, 3, 1, 624, PIERRE);
            setSol(42 * 16, 5 * 16, 2, 1, 624, PIERRE);
            setSol(42 * 16, 9 * 16, 2, 1, 624, PIERRE);
            setSol(44 * 16, 5 * 16, 1, 5, 624, PIERRE);
            setSol(47 * 16, 47 * 16, 1, 2, 624, PIERRE);
            setSol(52 * 16, 47 * 16, 1, 2, 624, PIERRE);
            setSol(47 * 16, 49 * 16, 6, 1, 624, PIERRE);
            setSol(74 * 16, 66 * 16, 1, 2, 624, PIERRE);
            setSol(124 * 16, 6 * 16, 1, 3, 624, PIERRE);
            setSol(146 * 16, 25 * 16, 1, 3, 624, PIERRE);
            setSol(149 * 16, 10 * 16, 2, 1, 624, PIERRE);
            setSol(157 * 16, 36 * 16, 1, 2, 624, PIERRE);
            setSol(164 * 16, 6 * 16, 1, 3, 624, PIERRE);
            setSol(167 * 16, 19 * 16, 5, 1, 624, PIERRE);
            setSol(168 * 16, 54 * 16, 4, 1, 624, PIERRE);
            setSol(168 * 16, 55 * 16, 1, 1, 624, PIERRE);
            setSol(171 * 16, 55 * 16, 1, 1, 624, PIERRE);
            setSol(168 * 16, 70 * 16, 3, 1, 624, PIERRE);
            setSol(169 * 16, 47 * 16, 2, 1, 624, PIERRE);
            setSol(186 * 16, 65 * 16, 5, 1, 624, PIERRE);
            setSol(186 * 16, 69 * 16, 5, 1, 624, PIERRE);
            setSol(186 * 16, 66 * 16, 1, 3, 624, PIERRE);
            setSol(190 * 16, 66 * 16, 1, 3, 624, PIERRE);
            setSol(187 * 16, 48 * 16, 1, 1, 624, PIERRE);
            setSol(192 * 16, 48 * 16, 1, 1, 624, PIERRE);
            setSol(187 * 16, 56 * 16, 1, 1, 624, PIERRE);
            setSol(192 * 16, 56 * 16, 1, 1, 624, PIERRE);
            setSol(194 * 16, 51 * 16, 1, 3, 624, PIERRE);

            setSol(7 * 16, 17 * 16, 1, 2, 627, MURRET);
            setSol(7 * 16, 19 * 16, 6, 1, 627, MURRET);
            setSol(12 * 16, 17 * 16, 1, 2, 627, MURRET);
            setSol(7 * 16, 56 * 16, 1, 2, 627, MURRET);
            setSol(7 * 16, 55 * 16, 6, 1, 627, MURRET);
            setSol(12 * 16, 56 * 16, 1, 2, 627, MURRET);
            setSol(21 * 16, 29 * 16, 1, 3, 627, MURRET);
            setSol(28 * 16, 17 * 16, 1, 3, 627, MURRET);
            setSol(35 * 16, 32 * 16, 3, 1, 627, MURRET);
            setSol(42 * 16, 65 * 16, 2, 1, 627, MURRET);
            setSol(42 * 16, 69 * 16, 2, 1, 627, MURRET);
            setSol(44 * 16, 65 * 16, 1, 5, 627, MURRET);
            setSol(47 * 16, 11 * 16, 1, 2, 627, MURRET);
            setSol(47 * 16, 10 * 16, 6, 1, 627, MURRET);
            setSol(52 * 16, 11 * 16, 1, 2, 627, MURRET);
            setSol(47 * 16, 26 * 16, 1, 2, 627, MURRET);
            setSol(47 * 16, 25 * 16, 6, 1, 627, MURRET);
            setSol(52 * 16, 26 * 16, 1, 2, 627, MURRET);
            setSol(77 * 16, 66 * 16, 1, 2, 627, MURRET);
            setSol(109 * 16, 34 * 16, 2, 1, 627, MURRET);
            setSol(142 * 16, 20 * 16, 2, 1, 627, MURRET);
            setSol(142 * 16, 24 * 16, 2, 1, 627, MURRET);
            setSol(144 * 16, 20 * 16, 1, 5, 627, MURRET);
            setSol(144 * 16, 66 * 16, 1, 3, 627, MURRET);
            setSol(146 * 16, 17 * 16, 1, 3, 627, MURRET);
            setSol(149 * 16, 64 * 16, 2, 1, 627, MURRET);
            setSol(167 * 16, 23 * 16, 1, 2, 627, MURRET);
            setSol(167 * 16, 22 * 16, 4, 1, 627, MURRET);
            setSol(172 * 16, 20 * 16, 1, 2, 627, MURRET);
            setSol(172 * 16, 34 * 16, 1, 7, 627, MURRET);
            setSol(174 * 16, 66 * 16, 1, 3, 627, MURRET);
        }
        else
        {
            setSol(19 * 16, 19 * 16, 1, 3, 626, MURRET);
            setSol(31 * 16, 22 * 16, 3, 1, 626, MURRET);
            setSol(35 * 16, 35 * 16, 3, 1, 626, MURRET);
            setSol(42 * 16, 5 * 16, 2, 1, 626, MURRET);
            setSol(42 * 16, 9 * 16, 2, 1, 626, MURRET);
            setSol(44 * 16, 5 * 16, 1, 5, 626, MURRET);
            setSol(47 * 16, 47 * 16, 1, 2, 626, MURRET);
            setSol(52 * 16, 47 * 16, 1, 2, 626, MURRET);
            setSol(47 * 16, 49 * 16, 6, 1, 626, MURRET);
            setSol(74 * 16, 66 * 16, 1, 2, 626, MURRET);
            setSol(124 * 16, 6 * 16, 1, 3, 626, MURRET);
            setSol(146 * 16, 25 * 16, 1, 3, 626, MURRET);
            setSol(149 * 16, 10 * 16, 2, 1, 626, MURRET);
            setSol(157 * 16, 36 * 16, 1, 2, 626, MURRET);
            setSol(164 * 16, 6 * 16, 1, 3, 626, MURRET);
            setSol(167 * 16, 19 * 16, 5, 1, 626, MURRET);
            setSol(168 * 16, 54 * 16, 4, 1, 626, MURRET);
            setSol(168 * 16, 55 * 16, 1, 1, 626, MURRET);
            setSol(171 * 16, 55 * 16, 1, 1, 626, MURRET);
            setSol(168 * 16, 70 * 16, 3, 1, 626, MURRET);
            setSol(169 * 16, 47 * 16, 2, 1, 626, MURRET);
            setSol(186 * 16, 65 * 16, 5, 1, 626, MURRET);
            setSol(186 * 16, 69 * 16, 5, 1, 626, MURRET);
            setSol(186 * 16, 66 * 16, 1, 3, 626, MURRET);
            setSol(190 * 16, 66 * 16, 1, 3, 626, MURRET);
            setSol(187 * 16, 48 * 16, 1, 1, 626, MURRET);
            setSol(192 * 16, 48 * 16, 1, 1, 626, MURRET);
            setSol(187 * 16, 56 * 16, 1, 1, 626, MURRET);
            setSol(192 * 16, 56 * 16, 1, 1, 626, MURRET);
            setSol(194 * 16, 51 * 16, 1, 3, 626, MURRET);

            setSol(7 * 16, 17 * 16, 1, 2, 625, PIERRE);
            setSol(7 * 16, 19 * 16, 6, 1, 625, PIERRE);
            setSol(12 * 16, 17 * 16, 1, 2, 625, PIERRE);
            setSol(7 * 16, 56 * 16, 1, 2, 625, PIERRE);
            setSol(7 * 16, 55 * 16, 6, 1, 625, PIERRE);
            setSol(12 * 16, 56 * 16, 1, 2, 625, PIERRE);
            setSol(21 * 16, 29 * 16, 1, 3, 625, PIERRE);
            setSol(28 * 16, 17 * 16, 1, 3, 625, PIERRE);
            setSol(35 * 16, 32 * 16, 3, 1, 625, PIERRE);
            setSol(42 * 16, 65 * 16, 2, 1, 625, PIERRE);
            setSol(42 * 16, 69 * 16, 2, 1, 625, PIERRE);
            setSol(44 * 16, 65 * 16, 1, 5, 625, PIERRE);
            setSol(47 * 16, 11 * 16, 1, 2, 625, PIERRE);
            setSol(47 * 16, 10 * 16, 6, 1, 625, PIERRE);
            setSol(52 * 16, 11 * 16, 1, 2, 625, PIERRE);
            setSol(47 * 16, 26 * 16, 1, 2, 625, PIERRE);
            setSol(47 * 16, 25 * 16, 6, 1, 625, PIERRE);
            setSol(52 * 16, 26 * 16, 1, 2, 625, PIERRE);
            setSol(77 * 16, 66 * 16, 1, 2, 625, PIERRE);
            setSol(109 * 16, 34 * 16, 2, 1, 625, PIERRE);
            setSol(142 * 16, 20 * 16, 2, 1, 625, PIERRE);
            setSol(142 * 16, 24 * 16, 2, 1, 625, PIERRE);
            setSol(144 * 16, 20 * 16, 1, 5, 625, PIERRE);
            setSol(144 * 16, 66 * 16, 1, 3, 625, PIERRE);
            setSol(146 * 16, 17 * 16, 1, 3, 625, PIERRE);
            setSol(149 * 16, 64 * 16, 2, 1, 625, PIERRE);
            setSol(167 * 16, 23 * 16, 1, 2, 625, PIERRE);
            setSol(167 * 16, 22 * 16, 4, 1, 625, PIERRE);
            setSol(172 * 16, 20 * 16, 1, 2, 625, PIERRE);
            setSol(172 * 16, 34 * 16, 1, 7, 625, PIERRE);
            setSol(174 * 16, 66 * 16, 1, 3, 625, PIERRE);
        }
        break;
    case 21:
        if (step == 0)
        {
            setSol(7 * 16, 25 * 16, 6, 1, 624, PIERRE);
            setSol(7 * 16, 26 * 16, 1, 2, 624, PIERRE);
            setSol(12 * 16, 26 * 16, 1, 2, 624, PIERRE);
            setSol(7 * 16, 34 * 16, 6, 1, 624, PIERRE);
            setSol(7 * 16, 32 * 16, 1, 2, 624, PIERRE);
            setSol(12 * 16, 32 * 16, 1, 2, 624, PIERRE);
            setSol(35 * 16, 5 * 16, 1, 5, 624, PIERRE);
            setSol(36 * 16, 5 * 16, 2, 1, 624, PIERRE);
            setSol(36 * 16, 9 * 16, 2, 1, 624, PIERRE);
            setSol(84 * 16, 5 * 16, 1, 5, 624, PIERRE);
            setSol(82 * 16, 5 * 16, 2, 1, 624, PIERRE);
            setSol(82 * 16, 9 * 16, 2, 1, 624, PIERRE);
            setSol(84 * 16, 20 * 16, 1, 5, 624, PIERRE);
            setSol(82 * 16, 20 * 16, 2, 1, 624, PIERRE);
            setSol(82 * 16, 24 * 16, 2, 1, 624, PIERRE);
            setSol(49 * 16, 40 * 16, 2, 1, 624, PIERRE);
            setSol(69 * 16, 40 * 16, 2, 1, 624, PIERRE);
            setSol(73 * 16, 33 * 16, 2, 1, 624, PIERRE);
            setSol(102 * 16, 10 * 16, 6, 1, 624, PIERRE);
            setSol(113 * 16, 34 * 16, 5, 1, 624, PIERRE);
            setSol(149 * 16, 31 * 16, 2, 1, 624, PIERRE);
            setSol(147 * 16, 34 * 16, 6, 1, 624, PIERRE);
            setSol(147 * 16, 39 * 16, 6, 1, 624, PIERRE);
            setSol(147 * 16, 35 * 16, 1, 4, 624, PIERRE);
            setSol(152 * 16, 35 * 16, 1, 4, 624, PIERRE);
            setSol(266 * 16, 21 * 16, 1, 3, 624, PIERRE);
            setSol(279 * 16, 35 * 16, 1, 2, 624, PIERRE);
            setSol(284 * 16, 5 * 16, 1, 5, 624, PIERRE);
            setSol(282 * 16, 5 * 16, 2, 1, 624, PIERRE);
            setSol(282 * 16, 9 * 16, 2, 1, 624, PIERRE);

            setSol(46 * 16, 36 * 16, 1, 3, 627, MURRET);
            setSol(71 * 16, 36 * 16, 1, 3, 627, MURRET);
            setSol(49 * 16, 19 * 16, 2, 1, 627, MURRET);
            setSol(47 * 16, 49 * 16, 6, 1, 627, MURRET);
            setSol(47 * 16, 54 * 16, 6, 1, 627, MURRET);
            setSol(47 * 16, 50 * 16, 1, 4, 627, MURRET);
            setSol(52 * 16, 50 * 16, 1, 4, 627, MURRET);
            setSol(87 * 16, 25 * 16, 6, 1, 627, MURRET);
            setSol(87 * 16, 26 * 16, 1, 2, 627, MURRET);
            setSol(92 * 16, 26 * 16, 1, 2, 627, MURRET);
            setSol(87 * 16, 34 * 16, 6, 1, 627, MURRET);
            setSol(87 * 16, 32 * 16, 1, 2, 627, MURRET);
            setSol(92 * 16, 32 * 16, 1, 2, 627, MURRET);
            setSol(102 * 16, 34 * 16, 6, 1, 627, MURRET);
            setSol(113 * 16, 10 * 16, 5, 1, 627, MURRET);
            setSol(149 * 16, 41 * 16, 2, 1, 627, MURRET);
            setSol(167 * 16, 27 * 16, 1, 3, 627, MURRET);
            setSol(187 * 16, 10 * 16, 6, 1, 627, MURRET);
            setSol(187 * 16, 11 * 16, 1, 2, 627, MURRET);
            setSol(192 * 16, 11 * 16, 1, 2, 627, MURRET);
            setSol(280 * 16, 46 * 16, 1, 2, 627, MURRET);
        }
        else
        {
            setSol(7 * 16, 25 * 16, 6, 1, 626, MURRET);
            setSol(7 * 16, 26 * 16, 1, 2, 626, MURRET);
            setSol(12 * 16, 26 * 16, 1, 2, 626, MURRET);
            setSol(7 * 16, 34 * 16, 6, 1, 626, MURRET);
            setSol(7 * 16, 32 * 16, 1, 2, 626, MURRET);
            setSol(12 * 16, 32 * 16, 1, 2, 626, MURRET);
            setSol(35 * 16, 5 * 16, 1, 5, 626, MURRET);
            setSol(36 * 16, 5 * 16, 2, 1, 626, MURRET);
            setSol(36 * 16, 9 * 16, 2, 1, 626, MURRET);
            setSol(84 * 16, 5 * 16, 1, 5, 626, MURRET);
            setSol(82 * 16, 5 * 16, 2, 1, 626, MURRET);
            setSol(82 * 16, 9 * 16, 2, 1, 626, MURRET);
            setSol(84 * 16, 20 * 16, 1, 5, 626, MURRET);
            setSol(82 * 16, 20 * 16, 2, 1, 626, MURRET);
            setSol(82 * 16, 24 * 16, 2, 1, 626, MURRET);
            setSol(49 * 16, 40 * 16, 2, 1, 626, MURRET);
            setSol(69 * 16, 40 * 16, 2, 1, 626, MURRET);
            setSol(73 * 16, 33 * 16, 2, 1, 626, MURRET);
            setSol(102 * 16, 10 * 16, 6, 1, 626, MURRET);
            setSol(113 * 16, 34 * 16, 5, 1, 626, MURRET);
            setSol(149 * 16, 31 * 16, 2, 1, 626, MURRET);
            setSol(147 * 16, 34 * 16, 6, 1, 626, MURRET);
            setSol(147 * 16, 39 * 16, 6, 1, 626, MURRET);
            setSol(147 * 16, 35 * 16, 1, 4, 626, MURRET);
            setSol(152 * 16, 35 * 16, 1, 4, 626, MURRET);
            setSol(266 * 16, 21 * 16, 1, 3, 626, MURRET);
            setSol(279 * 16, 35 * 16, 1, 2, 626, MURRET);
            setSol(284 * 16, 5 * 16, 1, 5, 626, MURRET);
            setSol(282 * 16, 5 * 16, 2, 1, 626, MURRET);
            setSol(282 * 16, 9 * 16, 2, 1, 626, MURRET);

            setSol(46 * 16, 36 * 16, 1, 3, 625, PIERRE);
            setSol(71 * 16, 36 * 16, 1, 3, 625, PIERRE);
            setSol(49 * 16, 19 * 16, 2, 1, 625, PIERRE);
            setSol(47 * 16, 49 * 16, 6, 1, 625, PIERRE);
            setSol(47 * 16, 54 * 16, 6, 1, 625, PIERRE);
            setSol(47 * 16, 50 * 16, 1, 4, 625, PIERRE);
            setSol(52 * 16, 50 * 16, 1, 4, 625, PIERRE);
            setSol(87 * 16, 25 * 16, 6, 1, 625, PIERRE);
            setSol(87 * 16, 26 * 16, 1, 2, 625, PIERRE);
            setSol(92 * 16, 26 * 16, 1, 2, 625, PIERRE);
            setSol(87 * 16, 34 * 16, 6, 1, 625, PIERRE);
            setSol(87 * 16, 32 * 16, 1, 2, 625, PIERRE);
            setSol(92 * 16, 32 * 16, 1, 2, 625, PIERRE);
            setSol(102 * 16, 34 * 16, 6, 1, 625, PIERRE);
            setSol(113 * 16, 10 * 16, 5, 1, 625, PIERRE);
            setSol(149 * 16, 41 * 16, 2, 1, 625, PIERRE);
            setSol(167 * 16, 27 * 16, 1, 3, 625, PIERRE);
            setSol(187 * 16, 10 * 16, 6, 1, 625, PIERRE);
            setSol(187 * 16, 11 * 16, 1, 2, 625, PIERRE);
            setSol(192 * 16, 11 * 16, 1, 2, 625, PIERRE);
            setSol(280 * 16, 46 * 16, 1, 2, 625, PIERRE);
        }
        break;
    case 25:
        if (step == 0)
        {
            setSol(22 * 16, 109 * 16, 2, 1, 624, PIERRE);
            setSol(24 * 16, 109 * 16, 1, 7, 624, PIERRE);
            setSol(22 * 16, 115 * 16, 2, 1, 624, PIERRE);
            setSol(27 * 16, 47 * 16, 1, 2, 624, PIERRE);
            setSol(27 * 16, 49 * 16, 6, 1, 624, PIERRE);
            setSol(32 * 16, 47 * 16, 1, 2, 624, PIERRE);
            setSol(47 * 16, 35 * 16, 6, 1, 624, PIERRE);
            setSol(47 * 16, 39 * 16, 6, 1, 624, PIERRE);
            setSol(47 * 16, 36 * 16, 1, 3, 624, PIERRE);
            setSol(52 * 16, 36 * 16, 1, 3, 624, PIERRE);
            setSol(56 * 16, 109 * 16, 2, 1, 624, PIERRE);
            setSol(55 * 16, 109 * 16, 1, 7, 624, PIERRE);
            setSol(56 * 16, 115 * 16, 2, 1, 624, PIERRE);
            setSol(148 * 16, 109 * 16, 4, 1, 624, PIERRE);
            setSol(194 * 16, 81 * 16, 1, 2, 624, PIERRE);

            setSol(27 * 16, 92 * 16, 1, 2, 627, MURRET);
            setSol(27 * 16, 94 * 16, 6, 1, 627, MURRET);
            setSol(32 * 16, 92 * 16, 1, 2, 627, MURRET);
            setSol(36 * 16, 34 * 16, 2, 1, 627, MURRET);
            setSol(35 * 16, 34 * 16, 1, 7, 627, MURRET);
            setSol(36 * 16, 40 * 16, 2, 1, 627, MURRET);
            setSol(144 * 16, 110 * 16, 1, 5, 627, MURRET);
            setSol(168 * 16, 94 * 16, 4, 1, 627, MURRET);
            setSol(189 * 16, 86 * 16, 2, 1, 627, MURRET);
        }
        else
        {
            setSol(22 * 16, 109 * 16, 2, 1, 626, MURRET);
            setSol(24 * 16, 109 * 16, 1, 7, 626, MURRET);
            setSol(22 * 16, 115 * 16, 2, 1, 626, MURRET);
            setSol(27 * 16, 47 * 16, 1, 2, 626, MURRET);
            setSol(27 * 16, 49 * 16, 6, 1, 626, MURRET);
            setSol(32 * 16, 47 * 16, 1, 2, 626, MURRET);
            setSol(47 * 16, 35 * 16, 6, 1, 626, MURRET);
            setSol(47 * 16, 39 * 16, 6, 1, 626, MURRET);
            setSol(47 * 16, 36 * 16, 1, 3, 626, MURRET);
            setSol(52 * 16, 36 * 16, 1, 3, 626, MURRET);
            setSol(56 * 16, 109 * 16, 2, 1, 626, MURRET);
            setSol(55 * 16, 109 * 16, 1, 7, 626, MURRET);
            setSol(56 * 16, 115 * 16, 2, 1, 626, MURRET);
            setSol(148 * 16, 109 * 16, 4, 1, 626, MURRET);
            setSol(194 * 16, 81 * 16, 1, 2, 626, MURRET);

            setSol(27 * 16, 92 * 16, 1, 2, 625, PIERRE);
            setSol(27 * 16, 94 * 16, 6, 1, 625, PIERRE);
            setSol(32 * 16, 92 * 16, 1, 2, 625, PIERRE);
            setSol(36 * 16, 34 * 16, 2, 1, 625, PIERRE);
            setSol(35 * 16, 34 * 16, 1, 7, 625, PIERRE);
            setSol(36 * 16, 40 * 16, 2, 1, 625, PIERRE);
            setSol(144 * 16, 110 * 16, 1, 5, 625, PIERRE);
            setSol(168 * 16, 94 * 16, 4, 1, 625, PIERRE);
            setSol(189 * 16, 86 * 16, 2, 1, 625, PIERRE);
        }
        break;
    }
}

void Map::switchSphere(bool blue)
{
    List list;
    BoundingBox *box = new BoundingBox(0, 0, w, h);
    objects->get(box, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Sphere *sphere = dynamic_cast<Sphere *>(list.getNext());
        if (sphere != 0)
        {
            sphere->setBlue(blue);
        }
    }
    delete box;
}

void Map::switchStar()
{
    List list;
    BoundingBox *box = new BoundingBox(0, 0, w, h);
    objects->get(box, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        InterrupteurStar *star = dynamic_cast<InterrupteurStar *>(list.getNext());
        if (star != 0)
        {
            star->switchMode();
        }
    }
    delete box;
}

void Map::disablePiege()
{
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        PiegeDemi *demi = dynamic_cast<PiegeDemi *>(element);
        PiegeColere *colere = dynamic_cast<PiegeColere *>(element);
        if (demi != 0)
        {
            demi->disable();
        }
        else if (colere != 0)
        {
            colere->disable();
        }
    }
}

int Map::nbEnnemis()
{
    List list;
    ennemis->get(&bounds, &list);
    return list.size();
}

void Map::closeChests()
{
    if (map == 47)
    {
        int chests[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int randomValue = ((int)rand()) % 9;
        chests[randomValue] = 1;

        BoundingBox b(6 * 16, 6 * 16, 5 * 16, 5 * 16);
        List list;
        objects->get(&b, &list);

        int num = 0;
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
            if (coffre != 0)
            {
                if (chests[num])
                {
                    coffre->close(TI_QUART_COEUR, 15);
                }
                else
                {
                    coffre->close(TI_NO_ITEM);
                }
                num++;
            }
        }
    }
}

void Map::openChests(int x, int y)
{
    if (map != 47)
        return;

    List list;
    BoundingBox b(6 * 16, 6 * 16, 5 * 16, 5 * 16);
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
        if (coffre != 0)
        {
            coffre->open(true);
        }
    }
}

bool Map::areChestsClosed()
{
    if (map != 47)
        return false;

    BoundingBox b(6 * 16, 6 * 16, 16, 16);
    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
        if (coffre != 0)
        {
            return !coffre->isOpened();
        }
    }

    return false;
}

void Map::enervePoules()
{
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Poule *poule = dynamic_cast<Poule *>(list.getNext());
        if (poule != 0)
        {
            poule->enerve();
        }
    }
    MainController::getInstance()->getGameController()->getSceneController()->getScene()->setCoffre(0, 15, 1);
}

void Map::displayInterruptor(int x, int y)
{
    BoundingBox bb = BoundingBox(x, y, 16, 16);
    List list;
    objects->get(&bb, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Interrupteur *inter = dynamic_cast<Interrupteur *>(element);
        InterrupteurStar *star = dynamic_cast<InterrupteurStar *>(element);
        if (inter != 0)
        {
            inter->displayOnMap();
        }
        if (star != 0)
        {
            star->displayOnMap();
        }
    }
}

void Map::ouvrePorte(int x, int y, int type)
{
    if (map == 5 && type == 1)
    {
        setSol(x * 16, y * 16, 1298, TROU);
        return;
    }

    switch (map)
    {
    case 2:
        sol[x][y] = 181;
        sol[x + 1][y] = 182;
        sol[x][y + 1] = 1136;
        sol[x + 1][y + 1] = 1137;
        mur[x * 2 + 1][y * 2 + 1] = TERRE;
        mur[x * 2 + 2][y * 2 + 1] = TERRE;
        mur[x * 2 + 1][y * 2 + 2] = TERRE;
        mur[x * 2 + 2][y * 2 + 2] = TERRE;
        mur[x * 2 + 1][y * 2 + 3] = TERRE;
        mur[x * 2 + 2][y * 2 + 3] = TERRE;
        break;
    case 3:
    case 5:
    case 9:
        sol[x][y] = 181;
        sol[x + 1][y] = 182;
        sol[x][y + 1] = 183;
        sol[x + 1][y + 1] = 184;
        mur[x * 2 + 1][y * 2 + 1] = HERBE;
        mur[x * 2 + 2][y * 2 + 1] = HERBE;
        mur[x * 2 + 1][y * 2 + 2] = HERBE;
        mur[x * 2 + 2][y * 2 + 2] = HERBE;
        mur[x * 2 + 1][y * 2 + 3] = HERBE;
        mur[x * 2 + 2][y * 2 + 3] = HERBE;
        break;
    case 6:
    case 10:
        sol[x][y] = 181;
        sol[x + 1][y] = 182;
        if (type == 0)
        {
            sol[x][y + 1] = 478;
            sol[x + 1][y + 1] = 479;
        }
        else if (type == 1)
        {
            sol[x][y + 1] = 482;
            sol[x + 1][y + 1] = 483;
        }
        mur[x * 2 + 1][y * 2 + 1] = EAU;
        mur[x * 2 + 2][y * 2 + 1] = EAU;
        mur[x * 2 + 1][y * 2 + 2] = EAU;
        mur[x * 2 + 2][y * 2 + 2] = EAU;
        mur[x * 2 + 1][y * 2 + 3] = EAU;
        mur[x * 2 + 2][y * 2 + 3] = EAU;
        break;
    case 8:
        if (type == 0)
        {
            setSol(26 * 16, 40 * 16, 2, 1, 1374, PIERRE);
        }
        else if (type == 1)
        {
            sol[x][y] = 181;
            sol[x + 1][y] = 182;
            sol[x][y + 1] = 482;
            sol[x + 1][y + 1] = 483;
            mur[x * 2 + 1][y * 2 + 1] = EAU;
            mur[x * 2 + 2][y * 2 + 1] = EAU;
            mur[x * 2 + 1][y * 2 + 2] = EAU;
            mur[x * 2 + 2][y * 2 + 2] = EAU;
            mur[x * 2 + 1][y * 2 + 3] = EAU;
            mur[x * 2 + 2][y * 2 + 3] = EAU;
        }
        break;
    case 14:
        sol[x][y] = 181;
        sol[x + 1][y] = 182;
        sol[x][y + 1] = 1206;
        sol[x + 1][y + 1] = 1207;
        mur[x * 2 + 1][y * 2 + 1] = HERBE;
        mur[x * 2 + 2][y * 2 + 1] = HERBE;
        mur[x * 2 + 1][y * 2 + 2] = HERBE;
        mur[x * 2 + 2][y * 2 + 2] = HERBE;
        mur[x * 2 + 1][y * 2 + 3] = HERBE;
        mur[x * 2 + 2][y * 2 + 3] = HERBE;
        break;
    case 15:
        if (type == 0)
        {
            sol[x][y] = 1669;
            sol[x + 1][y] = 1670;
            sol[x][y + 1] = 1671;
            sol[x + 1][y + 1] = 1672;
            sol[x][y + 2] = 1664;
            sol[x + 1][y + 2] = 1665;
            sol[x][y + 3] = 1666;
            sol[x + 1][y + 3] = 1667;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 1680;
            sol[x][y + 1] = 1682;
            sol[x][y + 2] = 1684;
            sol[x + 1][y] = 1715;
            sol[x + 1][y + 1] = 1683;
            sol[x + 1][y + 2] = 1716;

            sol[x + 2][y] = 1713;
            sol[x + 2][y + 1] = 1675;
            sol[x + 2][y + 2] = 1714;
            sol[x + 3][y] = 1674;
            sol[x + 3][y + 1] = 1676;
            sol[x + 3][y + 2] = 1678;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 16:
    case 20:
        if (type == 0)
        {
            sol[x][y] = 1874;
            sol[x + 1][y] = 1875;
            sol[x][y + 1] = 1876;
            sol[x + 1][y + 1] = 1877;
            sol[x][y + 2] = 1868;
            sol[x + 1][y + 2] = 1869;
            sol[x][y + 3] = 1870;
            sol[x + 1][y + 3] = 1871;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 1885;
            sol[x][y + 1] = 1887;
            sol[x][y + 2] = 1889;
            sol[x + 1][y] = 1886;
            sol[x + 1][y + 1] = 1888;
            sol[x + 1][y + 2] = 1890;

            sol[x + 2][y] = 1878;
            sol[x + 2][y + 1] = 1880;
            sol[x + 2][y + 2] = 1882;
            sol[x + 3][y] = 1879;
            sol[x + 3][y + 1] = 1881;
            sol[x + 3][y + 2] = 1883;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 1821;
            mur[x * 2][y * 2] = PIERRE;
            mur[x * 2 + 1][y * 2] = PIERRE;
            mur[x * 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
        }
        break;
    case 17:
        if (type == 0)
        {
            sol[x][y] = 2032;
            sol[x + 1][y] = 2033;
            sol[x][y + 1] = 2034;
            sol[x + 1][y + 1] = 2035;
            sol[x][y + 2] = 2026;
            sol[x + 1][y + 2] = 2027;
            sol[x][y + 3] = 2028;
            sol[x + 1][y + 3] = 2029;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 2045;
            sol[x][y + 1] = 2047;
            sol[x][y + 2] = 2049;
            sol[x + 1][y] = 2046;
            sol[x + 1][y + 1] = 2048;
            sol[x + 1][y + 2] = 2050;

            sol[x + 2][y] = 2038;
            sol[x + 2][y + 1] = 2040;
            sol[x + 2][y + 2] = 2042;
            sol[x + 3][y] = 2039;
            sol[x + 3][y + 1] = 2041;
            sol[x + 3][y + 2] = 2043;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 2094;
            sol[x + 1][y] = 2095;
            sol[x][y + 1] = 2096;
            sol[x + 1][y + 1] = 2097;
            air[x][y + 1] = 2098;
            air[x + 1][y + 1] = 2099;
            sol[x][y + 2] = 2088;
            sol[x + 1][y + 2] = 2089;
            air[x][y + 2] = 2092;
            air[x + 1][y + 2] = 2093;
            sol[x][y + 3] = 2090;
            sol[x + 1][y + 3] = 2091;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 2107;
            sol[x][y + 1] = 2109;
            sol[x][y + 2] = 2111;
            sol[x + 1][y] = 2108;
            sol[x + 1][y + 1] = 2110;
            air[x + 1][y + 1] = 2113;
            sol[x + 1][y + 2] = 2112;

            sol[x + 2][y] = 2100;
            sol[x + 2][y + 1] = 2102;
            air[x + 2][y + 1] = 2106;
            sol[x + 2][y + 2] = 2104;
            sol[x + 3][y] = 2101;
            sol[x + 3][y + 1] = 2103;
            sol[x + 3][y + 2] = 2105;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            sol[x][y] = 2151;
            sol[x + 1][y] = 2153;
            sol[x][y + 1] = 2156;
            sol[x + 1][y + 1] = 2158;
            mur[x * 2][y * 2] = TROU;
            mur[x * 2 + 1][y * 2] = TROU;
            mur[x * 2][y * 2 + 1] = TROU;
            mur[x * 2 + 1][y * 2 + 1] = TROU;
            mur[x * 2][y * 2 + 2] = TROU;
            mur[x * 2 + 1][y * 2 + 2] = TROU;
            mur[x * 2][y * 2 + 3] = TROU;
            mur[x * 2 + 1][y * 2 + 3] = TROU;
            mur[x * 2 + 2][y * 2] = TROU;
            mur[x * 2 + 3][y * 2] = TROU;
            mur[x * 2 + 2][y * 2 + 1] = TROU;
            mur[x * 2 + 3][y * 2 + 1] = TROU;
            mur[x * 2 + 2][y * 2 + 2] = TROU;
            mur[x * 2 + 3][y * 2 + 2] = TROU;
            mur[x * 2 + 2][y * 2 + 3] = TROU;
            mur[x * 2 + 3][y * 2 + 3] = TROU;
        }
        break;
    case 18:
        if (type == 0)
        {
            sol[x][y] = 2232;
            sol[x + 1][y] = 2233;
            sol[x][y + 1] = 2234;
            sol[x + 1][y + 1] = 2235;
            sol[x][y + 2] = 2226;
            sol[x + 1][y + 2] = 2227;
            sol[x][y + 3] = 2228;
            sol[x + 1][y + 3] = 2229;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 2245;
            sol[x][y + 1] = 2247;
            sol[x][y + 2] = 2249;
            sol[x + 1][y] = 2246;
            sol[x + 1][y + 1] = 2248;
            sol[x + 1][y + 2] = 2250;

            sol[x + 2][y] = 2238;
            sol[x + 2][y + 1] = 2240;
            sol[x + 2][y + 2] = 2242;
            sol[x + 3][y] = 2239;
            sol[x + 3][y + 1] = 2241;
            sol[x + 3][y + 2] = 2243;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 2310;
            sol[x + 1][y] = 2311;
            sol[x][y + 1] = 2312;
            sol[x + 1][y + 1] = 2313;
            air[x][y + 1] = 2314;
            air[x + 1][y + 1] = 2315;
            sol[x][y + 2] = 2304;
            sol[x + 1][y + 2] = 2305;
            air[x][y + 2] = 2308;
            air[x + 1][y + 2] = 2309;
            sol[x][y + 3] = 2306;
            sol[x + 1][y + 3] = 2307;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 4)
        {
            sol[x][y] = 2324;
            sol[x + 1][y] = 2326;
            sol[x][y + 1] = 2329;
            sol[x + 1][y + 1] = 2331;
            mur[x * 2][y * 2] = TROU;
            mur[x * 2 + 1][y * 2] = TROU;
            mur[x * 2][y * 2 + 1] = TROU;
            mur[x * 2 + 1][y * 2 + 1] = TROU;
            mur[x * 2][y * 2 + 2] = TROU;
            mur[x * 2 + 1][y * 2 + 2] = TROU;
            mur[x * 2][y * 2 + 3] = TROU;
            mur[x * 2 + 1][y * 2 + 3] = TROU;
            mur[x * 2 + 2][y * 2] = TROU;
            mur[x * 2 + 3][y * 2] = TROU;
            mur[x * 2 + 2][y * 2 + 1] = TROU;
            mur[x * 2 + 3][y * 2 + 1] = TROU;
            mur[x * 2 + 2][y * 2 + 2] = TROU;
            mur[x * 2 + 3][y * 2 + 2] = TROU;
            mur[x * 2 + 2][y * 2 + 3] = TROU;
            mur[x * 2 + 3][y * 2 + 3] = TROU;
        }
        else if (type == 5)
        {
            sol[x][y] = 2178;
            mur[x * 2][y * 2] = PIERRE;
            mur[x * 2 + 1][y * 2] = PIERRE;
            mur[x * 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
        }
        break;
    case 19:
        if (type == 0)
        {
            sol[x][y] = 2419;
            sol[x + 1][y] = 2420;
            sol[x][y + 1] = 2421;
            sol[x + 1][y + 1] = 2422;
            sol[x][y + 2] = 2413;
            sol[x + 1][y + 2] = 2414;
            sol[x][y + 3] = 2415;
            sol[x + 1][y + 3] = 2416;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 2432;
            sol[x][y + 1] = 2434;
            sol[x][y + 2] = 2436;
            sol[x + 1][y] = 2433;
            sol[x + 1][y + 1] = 2435;
            sol[x + 1][y + 2] = 2437;

            sol[x + 2][y] = 2425;
            sol[x + 2][y + 1] = 2427;
            sol[x + 2][y + 2] = 2429;
            sol[x + 3][y] = 2426;
            sol[x + 3][y + 1] = 2428;
            sol[x + 3][y + 2] = 2430;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 2492;
            sol[x][y + 1] = 2494;
            sol[x][y + 2] = 2496;
            sol[x + 1][y] = 2493;
            sol[x + 1][y + 1] = 2495;
            air[x + 1][y + 1] = 2498;
            sol[x + 1][y + 2] = 2497;

            sol[x + 2][y] = 2485;
            sol[x + 2][y + 1] = 2487;
            air[x + 2][y + 1] = 2491;
            sol[x + 2][y + 2] = 2489;
            sol[x + 3][y] = 2486;
            sol[x + 3][y + 1] = 2488;
            sol[x + 3][y + 2] = 2490;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 21:
        if (type == 0)
        {
            sol[x][y] = 2615;
            sol[x + 1][y] = 2616;
            sol[x][y + 1] = 2617;
            sol[x + 1][y + 1] = 2618;
            sol[x][y + 2] = 2610;
            sol[x + 1][y + 2] = 2611;
            sol[x][y + 3] = 2612;
            sol[x + 1][y + 3] = 2613;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 2627;
            sol[x][y + 1] = 2629;
            sol[x][y + 2] = 2631;
            sol[x + 1][y] = 2663;
            sol[x + 1][y + 1] = 2664;
            sol[x + 1][y + 2] = 2665;

            sol[x + 2][y] = 2660;
            sol[x + 2][y + 1] = 2661;
            sol[x + 2][y + 2] = 2662;
            sol[x + 3][y] = 2621;
            sol[x + 3][y + 1] = 2623;
            sol[x + 3][y + 2] = 2625;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 22:
        if (type == 0)
        {
            sol[x][y] = (x < 160) ? 2826 : 2978;
            sol[x + 1][y] = (x < 160) ? 2827 : 2979;
            sol[x][y + 1] = (x < 160) ? 2828 : 2980;
            sol[x + 1][y + 1] = (x < 160) ? 2829 : 2981;
            sol[x][y + 2] = (x < 160) ? 2820 : 2972;
            sol[x + 1][y + 2] = (x < 160) ? 2821 : 2973;
            sol[x][y + 3] = (x < 160) ? 2822 : 2974;
            sol[x + 1][y + 3] = (x < 160) ? 2823 : 2975;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 2839;
            sol[x][y + 1] = 2841;
            sol[x][y + 2] = 2843;
            sol[x + 1][y] = 2840;
            sol[x + 1][y + 1] = 2842;
            sol[x + 1][y + 2] = 2844;

            sol[x + 2][y] = 2832;
            sol[x + 2][y + 1] = 2834;
            sol[x + 2][y + 2] = 2836;
            sol[x + 3][y] = 2833;
            sol[x + 3][y + 1] = 2835;
            sol[x + 3][y + 2] = 2837;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 2908;
            sol[x + 1][y] = 2909;
            sol[x][y + 1] = 2910;
            sol[x + 1][y + 1] = 2911;
            air[x][y + 1] = 2912;
            air[x + 1][y + 1] = 2913;
            sol[x][y + 2] = 2902;
            sol[x + 1][y + 2] = 2903;
            air[x][y + 2] = 2906;
            air[x + 1][y + 2] = 2907;
            sol[x][y + 3] = 2904;
            sol[x + 1][y + 3] = 2905;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 2921;
            sol[x][y + 1] = 2923;
            sol[x][y + 2] = 2925;
            sol[x + 1][y] = 2922;
            sol[x + 1][y + 1] = 2924;
            air[x + 1][y + 1] = 2927;
            sol[x + 1][y + 2] = 2926;

            sol[x + 2][y] = 2914;
            sol[x + 2][y + 1] = 2916;
            air[x + 2][y + 1] = 2920;
            sol[x + 2][y + 2] = 2918;
            sol[x + 3][y] = 2915;
            sol[x + 3][y + 1] = 2917;
            sol[x + 3][y + 2] = 2919;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 23:
        if (type == 0)
        {
            sol[x][y] = 3072;
            sol[x + 1][y] = 3073;
            sol[x][y + 1] = 3074;
            sol[x + 1][y + 1] = 3075;
            sol[x][y + 2] = 3066;
            sol[x + 1][y + 2] = 3067;
            sol[x][y + 3] = 3068;
            sol[x + 1][y + 3] = 3069;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3085;
            sol[x][y + 1] = 3087;
            sol[x][y + 2] = 3089;
            sol[x + 1][y] = 3086;
            sol[x + 1][y + 1] = 3088;
            sol[x + 1][y + 2] = 3090;

            sol[x + 2][y] = 3078;
            sol[x + 2][y + 1] = 3080;
            sol[x + 2][y + 2] = 3082;
            sol[x + 3][y] = 3079;
            sol[x + 3][y + 1] = 3081;
            sol[x + 3][y + 2] = 3083;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 3154;
            sol[x][y + 1] = 3156;
            sol[x][y + 2] = 3158;
            sol[x + 1][y] = 3155;
            sol[x + 1][y + 1] = 3157;
            air[x + 1][y + 1] = 3160;
            sol[x + 1][y + 2] = 3159;

            sol[x + 2][y] = 3147;
            sol[x + 2][y + 1] = 3149;
            air[x + 2][y + 1] = 3153;
            sol[x + 2][y + 2] = 3151;
            sol[x + 3][y] = 3148;
            sol[x + 3][y + 1] = 3150;
            sol[x + 3][y + 2] = 3152;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            sol[x][y] = 3161;
            sol[x + 1][y] = 3163;
            sol[x][y + 1] = 3166;
            sol[x + 1][y + 1] = 3168;
            mur[x * 2][y * 2] = TROU;
            mur[x * 2 + 1][y * 2] = TROU;
            mur[x * 2][y * 2 + 1] = TROU;
            mur[x * 2 + 1][y * 2 + 1] = TROU;
            mur[x * 2][y * 2 + 2] = TROU;
            mur[x * 2 + 1][y * 2 + 2] = TROU;
            mur[x * 2][y * 2 + 3] = TROU;
            mur[x * 2 + 1][y * 2 + 3] = TROU;
            mur[x * 2 + 2][y * 2] = TROU;
            mur[x * 2 + 3][y * 2] = TROU;
            mur[x * 2 + 2][y * 2 + 1] = TROU;
            mur[x * 2 + 3][y * 2 + 1] = TROU;
            mur[x * 2 + 2][y * 2 + 2] = TROU;
            mur[x * 2 + 3][y * 2 + 2] = TROU;
            mur[x * 2 + 2][y * 2 + 3] = TROU;
            mur[x * 2 + 3][y * 2 + 3] = TROU;
        }
        break;
    case 24:
        if (type == 0)
        {
            sol[x][y] = 3237;
            sol[x + 1][y] = 3238;
            sol[x][y + 1] = 3239;
            sol[x + 1][y + 1] = 3240;
            sol[x][y + 2] = 3231;
            sol[x + 1][y + 2] = 3232;
            sol[x][y + 3] = 3233;
            sol[x + 1][y + 3] = 3234;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3248;
            sol[x][y + 1] = 3250;
            sol[x][y + 2] = 3252;
            sol[x + 1][y] = 3249;
            sol[x + 1][y + 1] = 3251;
            sol[x + 1][y + 2] = 3253;

            sol[x + 2][y] = 3241;
            sol[x + 2][y + 1] = 3243;
            sol[x + 2][y + 2] = 3245;
            sol[x + 3][y] = 3242;
            sol[x + 3][y + 1] = 3244;
            sol[x + 3][y + 2] = 3246;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 3309;
            sol[x + 1][y] = 3310;
            sol[x][y + 1] = 3311;
            sol[x + 1][y + 1] = 3312;
            air[x][y + 1] = 3313;
            air[x + 1][y + 1] = 3314;
            sol[x][y + 2] = 3303;
            sol[x + 1][y + 2] = 3304;
            air[x][y + 2] = 3307;
            air[x + 1][y + 2] = 3308;
            sol[x][y + 3] = 3305;
            sol[x + 1][y + 3] = 3306;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 3322;
            sol[x][y + 1] = 3324;
            sol[x][y + 2] = 3326;
            sol[x + 1][y] = 3323;
            sol[x + 1][y + 1] = 3325;
            air[x + 1][y + 1] = 3328;
            sol[x + 1][y + 2] = 3327;

            sol[x + 2][y] = 3315;
            sol[x + 2][y + 1] = 3317;
            air[x + 2][y + 1] = 3321;
            sol[x + 2][y + 2] = 3319;
            sol[x + 3][y] = 3316;
            sol[x + 3][y + 1] = 3318;
            sol[x + 3][y + 2] = 3320;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            sol[x][y] = 3329;
            sol[x + 1][y] = 3331;
            sol[x][y + 1] = 3334;
            sol[x + 1][y + 1] = 3336;
            mur[x * 2][y * 2] = TROU;
            mur[x * 2 + 1][y * 2] = TROU;
            mur[x * 2][y * 2 + 1] = TROU;
            mur[x * 2 + 1][y * 2 + 1] = TROU;
            mur[x * 2][y * 2 + 2] = TROU;
            mur[x * 2 + 1][y * 2 + 2] = TROU;
            mur[x * 2][y * 2 + 3] = TROU;
            mur[x * 2 + 1][y * 2 + 3] = TROU;
            mur[x * 2 + 2][y * 2] = TROU;
            mur[x * 2 + 3][y * 2] = TROU;
            mur[x * 2 + 2][y * 2 + 1] = TROU;
            mur[x * 2 + 3][y * 2 + 1] = TROU;
            mur[x * 2 + 2][y * 2 + 2] = TROU;
            mur[x * 2 + 3][y * 2 + 2] = TROU;
            mur[x * 2 + 2][y * 2 + 3] = TROU;
            mur[x * 2 + 3][y * 2 + 3] = TROU;
        }
        break;
    case 25:
        if (type == 0)
        {
            sol[x][y] = 3406;
            sol[x + 1][y] = 3407;
            sol[x][y + 1] = 3408;
            sol[x + 1][y + 1] = 3409;
            sol[x][y + 2] = 3400;
            sol[x + 1][y + 2] = 3401;
            sol[x][y + 3] = 3402;
            sol[x + 1][y + 3] = 3403;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3419;
            sol[x][y + 1] = 3421;
            sol[x][y + 2] = 3423;
            sol[x + 1][y] = 3420;
            sol[x + 1][y + 1] = 3422;
            sol[x + 1][y + 2] = 3424;

            sol[x + 2][y] = 3412;
            sol[x + 2][y + 1] = 3414;
            sol[x + 2][y + 2] = 3416;
            sol[x + 3][y] = 3413;
            sol[x + 3][y + 1] = 3415;
            sol[x + 3][y + 2] = 3417;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 3488;
            sol[x + 1][y] = 3489;
            sol[x][y + 1] = 3490;
            sol[x + 1][y + 1] = 3491;
            air[x][y + 1] = 3492;
            air[x + 1][y + 1] = 3493;
            sol[x][y + 2] = 3482;
            sol[x + 1][y + 2] = 3483;
            air[x][y + 2] = 3486;
            air[x + 1][y + 2] = 3487;
            sol[x][y + 3] = 3484;
            sol[x + 1][y + 3] = 3485;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 3501;
            sol[x][y + 1] = 3503;
            sol[x][y + 2] = 3505;
            sol[x + 1][y] = 3502;
            sol[x + 1][y + 1] = 3504;
            air[x + 1][y + 1] = 3507;
            sol[x + 1][y + 2] = 3506;

            sol[x + 2][y] = 3494;
            sol[x + 2][y + 1] = 3496;
            air[x + 2][y + 1] = 3500;
            sol[x + 2][y + 2] = 3498;
            sol[x + 3][y] = 3495;
            sol[x + 3][y + 1] = 3497;
            sol[x + 3][y + 2] = 3499;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 26:
        if (type == 0)
        {
            sol[x][y] = x < 280 ? 3694 : 3851;
            sol[x + 1][y] = x < 280 ? 3695 : 3852;
            sol[x][y + 1] = x < 280 ? 3696 : 3853;
            sol[x + 1][y + 1] = x < 280 ? 3697 : 3854;
            sol[x][y + 2] = x < 280 ? 3688 : 3845;
            sol[x + 1][y + 2] = x < 280 ? 3689 : 3846;
            sol[x][y + 3] = x < 280 ? 3690 : 3847;
            sol[x + 1][y + 3] = x < 280 ? 3691 : 3848;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3707;
            sol[x][y + 1] = 3709;
            sol[x][y + 2] = 3711;
            sol[x + 1][y] = 3708;
            sol[x + 1][y + 1] = 3710;
            sol[x + 1][y + 2] = 3712;

            sol[x + 2][y] = 3700;
            sol[x + 2][y + 1] = 3702;
            sol[x + 2][y + 2] = 3704;
            sol[x + 3][y] = 3701;
            sol[x + 3][y + 1] = 3703;
            sol[x + 3][y + 2] = 3705;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 3763;
            sol[x][y + 1] = 3765;
            sol[x][y + 2] = 3767;
            sol[x + 1][y] = 3764;
            sol[x + 1][y + 1] = 3766;
            air[x + 1][y + 1] = 3769;
            sol[x + 1][y + 2] = 3768;

            sol[x + 2][y] = 3756;
            sol[x + 2][y + 1] = 3758;
            air[x + 2][y + 1] = 3762;
            sol[x + 2][y + 2] = 3760;
            sol[x + 3][y] = 3757;
            sol[x + 3][y + 1] = 3759;
            sol[x + 3][y + 2] = 3761;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 27:
        if (type == 0)
        {
            sol[x][y] = 3946;
            sol[x + 1][y] = 3947;
            sol[x][y + 1] = 3948;
            sol[x + 1][y + 1] = 3949;
            sol[x][y + 2] = 3940;
            sol[x + 1][y + 2] = 3941;
            sol[x][y + 3] = 3942;
            sol[x + 1][y + 3] = 3943;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3959;
            sol[x][y + 1] = 3961;
            sol[x][y + 2] = 3963;
            sol[x + 1][y] = 3960;
            sol[x + 1][y + 1] = 3962;
            sol[x + 1][y + 2] = 3964;

            sol[x + 2][y] = 3952;
            sol[x + 2][y + 1] = 3954;
            sol[x + 2][y + 2] = 3956;
            sol[x + 3][y] = 3953;
            sol[x + 3][y + 1] = 3955;
            sol[x + 3][y + 2] = 3957;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 4018;
            sol[x + 1][y] = 4019;
            sol[x][y + 1] = 4020;
            sol[x + 1][y + 1] = 4021;
            air[x][y + 1] = 4022;
            air[x + 1][y + 1] = 4023;
            sol[x][y + 2] = 4012;
            sol[x + 1][y + 2] = 4013;
            air[x][y + 2] = 4016;
            air[x + 1][y + 2] = 4017;
            sol[x][y + 3] = 4014;
            sol[x + 1][y + 3] = 4015;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        break;
    case 28:
        if (type == 0)
        {
            sol[x][y] = 4077;
            sol[x + 1][y] = 4078;
            sol[x][y + 1] = 4079;
            sol[x + 1][y + 1] = 4080;
            sol[x][y + 2] = 4071;
            sol[x + 1][y + 2] = 4072;
            sol[x][y + 3] = 4073;
            sol[x + 1][y + 3] = 4074;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 4090;
            sol[x][y + 1] = 4092;
            sol[x][y + 2] = 4094;
            sol[x + 1][y] = 4091;
            sol[x + 1][y + 1] = 4093;
            sol[x + 1][y + 2] = 4095;

            sol[x + 2][y] = 4083;
            sol[x + 2][y + 1] = 4085;
            sol[x + 2][y + 2] = 4087;
            sol[x + 3][y] = 4084;
            sol[x + 3][y + 1] = 4086;
            sol[x + 3][y + 2] = 4088;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 45:
        sol[x][y] = 1868;
        sol[x + 1][y] = 1869;
        sol[x][y + 1] = 1870;
        sol[x + 1][y + 1] = 1871;
        mur[x * 2 + 1][y * 2] = TERRE;
        mur[x * 2 + 2][y * 2] = TERRE;
        mur[x * 2 + 1][y * 2 + 1] = TERRE;
        mur[x * 2 + 2][y * 2 + 1] = TERRE;
        mur[x * 2 + 1][y * 2 + 2] = TERRE;
        mur[x * 2 + 2][y * 2 + 2] = TERRE;
        break;
    }
}

void Map::fermePorte(int x, int y, int type)
{
    switch (map)
    {
    case 15:
        if (type == 0)
        {
            sol[x][y] = 1725;
            sol[x + 1][y] = 1726;
            sol[x][y + 1] = 1727;
            sol[x + 1][y + 1] = 1728;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 16:
    case 20:
        if (type == 0)
        {
            sol[x][y] = 1916;
            sol[x + 1][y] = 1917;
            sol[x][y + 1] = 1918;
            sol[x + 1][y + 1] = 1919;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 17:
        if (type == 0)
        {
            sol[x][y] = 2068;
            sol[x + 1][y] = 2069;
            sol[x][y + 1] = 2070;
            sol[x + 1][y + 1] = 2071;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 18:
        if (type == 0)
        {
            sol[x][y] = 2280;
            sol[x + 1][y] = 2281;
            sol[x][y + 1] = 2282;
            sol[x + 1][y + 1] = 2283;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 19:
        if (type == 0)
        {
            sol[x][y] = 2467;
            sol[x + 1][y] = 2468;
            sol[x][y + 1] = 2469;
            sol[x + 1][y + 1] = 2470;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 21:
        if (type == 0)
        {
            sol[x][y] = 2674;
            sol[x + 1][y] = 2675;
            sol[x][y + 1] = 2676;
            sol[x + 1][y + 1] = 2677;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 22:
        if (type == 0)
        {
            sol[x][y] = 2870;
            sol[x + 1][y] = 2871;
            sol[x][y + 1] = 2872;
            sol[x + 1][y + 1] = 2873;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 23:
        if (type == 0)
        {
            sol[x][y] = 3116;
            sol[x + 1][y] = 3117;
            sol[x][y + 1] = 3118;
            sol[x + 1][y + 1] = 3119;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 24:
        if (type == 0)
        {
            sol[x][y] = 3271;
            sol[x + 1][y] = 3272;
            sol[x][y + 1] = 3273;
            sol[x + 1][y + 1] = 3274;
            sol[x][y + 2] = 3267;
            sol[x + 1][y + 2] = 3268;
            sol[x][y + 3] = 3269;
            sol[x + 1][y + 3] = 3270;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 25:
        if (type == 0)
        {
            sol[x][y] = 3450;
            sol[x + 1][y] = 3451;
            sol[x][y + 1] = 3452;
            sol[x + 1][y + 1] = 3453;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 26:
        if (type == 0)
        {
            sol[x][y] = 3883;
            sol[x + 1][y] = 3884;
            sol[x][y + 1] = 3885;
            sol[x + 1][y + 1] = 3886;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 27:
        if (type == 0)
        {
            sol[x][y] = 3990;
            sol[x + 1][y] = 3991;
            sol[x][y + 1] = 3992;
            sol[x + 1][y + 1] = 3993;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 28:
        if (type == 0)
        {
            sol[x][y] = 4121;
            sol[x + 1][y] = 4122;
            sol[x][y + 1] = 4123;
            sol[x + 1][y + 1] = 4124;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    }
}

void Map::removeStele()
{
    if (map != 14)
        return;

    int x = 94 * 16;
    int y = 35 * 16;

    BoundingBox b(x, y, 16, 16);

    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Stele *stele = dynamic_cast<Stele *>(list.getNext());
        if (stele != 0)
        {
            stele->explose();
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setCoffre(0, 10, 1);
        }
    }
}

void Map::songPlayed(int id)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    switch (id)
    {
    case 0:
        if (map == 14 && !scene->getCoffre(0, 10) && (link->getX() > 92 * 16 && link->getX() < 97 * 16) && (link->getY() > 37 * 16 + 8 && link->getY() < 42 * 16 + 8))
        {
            removeStele();
        }
        break;
    case 1:
        if (map < 15)
        {
            MainController::getInstance()->getGameController()->displayMap(map, true);
            AudioManager::getInstance()->playSound(TS_MENU1);
        }
        break;
    case 2:
        if (map == 26 && bounds.getX() == 320 * 15 && bounds.getY() == 240 * 2 && !link->getInventory()->hasObject(MASQUE))
        {
            List toCatch;
            ennemis->get(&bounds, &toCatch);
            toCatch.iterateOnFirst();
            while (toCatch.hasNext())
            {
                Ennemi075 *oniLink = dynamic_cast<Ennemi075 *>(toCatch.getNext());
                if (oniLink != 0)
                {
                    oniLink->catchToMask();
                }
            }
        }
        break;
    default:
        break;
    }
}

bool Map::testVillage(BoundingBox *box, bool isOni)
{
    if (isVillage(box))
    {
        if (map == 11 || (map >= 62 && map <= 66))
        {
            return !isOni;
        }
        return isOni;
    }
    return false;
}

bool Map::isVillage(BoundingBox *box)
{
    if (map >= 46 && map <= 70 && map != 61)
        return true; // maisons des villages
    BoundingBox tmp;
    switch (map)
    {
    case 3:
        tmp.setX(7 * 16);
        tmp.setY(12 * 16);
        tmp.setW(71 * 16);
        tmp.setH(42 * 16);
        if (tmp.intersect(box))
            return true;
        tmp.setX(17 * 16);
        tmp.setY(9 * 16);
        tmp.setW(47 * 16);
        tmp.setH(3 * 16);
        return tmp.intersect(box);
    case 7:
        tmp.setX(11 * 16);
        tmp.setY(13 * 16);
        tmp.setW(63 * 16);
        tmp.setH(29 * 16);
        if (tmp.intersect(box))
            return true;
        tmp.setX(31 * 16);
        tmp.setY(3 * 16);
        tmp.setW(34 * 16);
        tmp.setH(10 * 16);
        return tmp.intersect(box);
    case 11:
        tmp.setX(8 * 16);
        tmp.setY(8 * 16);
        tmp.setW(64 * 16);
        tmp.setH(36 * 16);
        return tmp.intersect(box);
    case 13:
        tmp.setX(24 * 16);
        tmp.setY(21 * 16);
        tmp.setW(40 * 16);
        tmp.setH(21 * 16);
        return tmp.intersect(box);
    }
    return false;
}

int Map::getEtage()
{
    switch (map)
    {
    case 15:
    case 16:
    case 19:
    case 21:
        return -(bounds.getX() / (100 * 16));
    case 17:
        if (bounds.getX() == 0)
            return 1;
        if (bounds.getX() < 320 * 6)
            return 0;
        return -1;
    case 18:
        if (bounds.getX() < 320 * 3)
            return 2;
        if (bounds.getX() < 320 * 6)
            return 1;
        if (bounds.getX() < 320 * 11)
            return 0;
        return -1;
    case 20:
        if (bounds.getX() == 0)
            return 1;
        if (bounds.getX() < 320 * 8)
            return 0;
        return -1;
    case 22:
        return 1 - (bounds.getX() / (80 * 16));
    case 23:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 4)
            return 2;
        if (bounds.getX() < 320 * 3)
            return 1;
        if (bounds.getX() < 320 * 8)
            return 0;
        if (bounds.getX() < 320 * 13)
            return -1;
        return -2;
    case 24:
        return 1 - (bounds.getX() / (100 * 16));
    case 25:
        if (bounds.getX() > 160 * 16 && bounds.getY() < 60 * 16)
            return 3;
        if (bounds.getY() < 60 * 16)
            return 2 - (bounds.getX() / (80 * 16));
        return -(bounds.getX() / (80 * 16));
    case 26:
        return -(bounds.getX() / (140 * 16));
    case 27:
        return 0;
    case 28:
        if (bounds.getX() > 100 * 16 && bounds.getY() > 75 * 16)
            return 3;
        if (bounds.getY() < 75 * 16)
            return 2 - (bounds.getX() / (100 * 16));
        return 0;
    case 34:
    case 40:
        return (bounds.getX() / (40 * 16));
    case 41:
        if (bounds.getX() == 0)
            return 0;
        return -1;
    default:
        return 0;
    }
}
