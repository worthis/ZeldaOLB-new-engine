#include "MapInitializer.h"

#include "Map.h"

#include "../../MainController.h"

#include "../objects/Pierre.h"
#include "../objects/Pancarte.h"
#include "../objects/Pnj.h"
#include "../objects/Poule.h"
#include "../objects/Coffre.h"
#include "../objects/PiegePics.h"
#include "../objects/PiegeLong.h"
#include "../objects/PiegeMurs.h"
#include "../objects/PiegeFeu.h"
#include "../objects/PiegeDemi.h"
#include "../objects/PiegeColere.h"
#include "../objects/Jarre.h"
#include "../objects/Sphere.h"
#include "../objects/Caisse.h"
#include "../objects/Interrupteur.h"
#include "../objects/InterrupteurStar.h"
#include "../objects/PiegeMain.h"
#include "../objects/TalkableArea.h"
#include "../objects/Barriere.h"
#include "../objects/Stele.h"

#include "../ennemis/Ennemi001.h"
#include "../ennemis/Ennemi002.h"
#include "../ennemis/Ennemi003.h"
#include "../ennemis/Ennemi004.h"
#include "../ennemis/Ennemi005.h"
#include "../ennemis/Ennemi006.h"
#include "../ennemis/Ennemi007.h"
#include "../ennemis/Ennemi008.h"
#include "../ennemis/Ennemi009.h"
#include "../ennemis/Ennemi010.h"
#include "../ennemis/Ennemi011.h"
#include "../ennemis/Ennemi012.h"
#include "../ennemis/Ennemi013.h"
#include "../ennemis/Ennemi014.h"
#include "../ennemis/Ennemi015.h"
#include "../ennemis/Ennemi016.h"
#include "../ennemis/Ennemi018.h"
#include "../ennemis/Ennemi019.h"
#include "../ennemis/Ennemi021.h"
#include "../ennemis/Ennemi022.h"
#include "../ennemis/Ennemi023.h"
#include "../ennemis/Ennemi024.h"
#include "../ennemis/Ennemi025.h"
#include "../ennemis/Ennemi026.h"
#include "../ennemis/Ennemi027.h"
#include "../ennemis/Ennemi028.h"
#include "../ennemis/Ennemi029.h"
#include "../ennemis/Ennemi030.h"
#include "../ennemis/Ennemi031.h"
#include "../ennemis/Ennemi032.h"
#include "../ennemis/Ennemi033.h"
#include "../ennemis/Ennemi034.h"
#include "../ennemis/Ennemi035.h"
#include "../ennemis/Ennemi037.h"
#include "../ennemis/Ennemi038.h"
#include "../ennemis/Ennemi039.h"
#include "../ennemis/Ennemi040.h"
#include "../ennemis/Ennemi041.h"
#include "../ennemis/Ennemi042.h"
#include "../ennemis/Ennemi043.h"
#include "../ennemis/Ennemi044.h"
#include "../ennemis/Ennemi045.h"
#include "../ennemis/Ennemi046.h"
#include "../ennemis/Ennemi047.h"
#include "../ennemis/Ennemi048.h"
#include "../ennemis/Ennemi050.h"
#include "../ennemis/Ennemi053.h"
#include "../ennemis/Ennemi054.h"
#include "../ennemis/Ennemi055.h"
#include "../ennemis/Ennemi056.h"
#include "../ennemis/Ennemi057.h"
#include "../ennemis/Ennemi060.h"
#include "../ennemis/Ennemi062.h"
#include "../ennemis/Ennemi063.h"
#include "../ennemis/Ennemi064.h"
#include "../ennemis/Ennemi066.h"
#include "../ennemis/Ennemi071.h"
#include "../ennemis/Ennemi072.h"
#include "../ennemis/Ennemi073.h"
#include "../ennemis/Ennemi075.h"
#include "../ennemis/Ennemi076.h"

/*
#include "../objects/Switch.h"
#include "../objects/Tombe.h"
*/

MapInitializer::MapInitializer(Map *m) : map(m)
{
}

MapInitializer::~MapInitializer()
{
}

void MapInitializer::addEnnemi(Ennemi *ennemi)
{
    map->addEnnemi(ennemi);
}

void MapInitializer::addItem(Item *item)
{
    map->addItem(item);
}

void MapInitializer::addObject(Object *object)
{
    map->addObject(object);
}

void MapInitializer::ouvrePorte(int x, int y, int type)
{
    map->ouvrePorte(x, y, type);
}

void MapInitializer::init()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    Inventory *inventory = link->getInventory();

    /*if (scene->getAvancement() == AV_GARDE_MOVE) {
        scene->setAvancement(AV_GARDE_OUT);
    }*/

    int monstre1 = 0;
    int monstre2 = 0;
    int monstre3 = 0;
    int zone = map->getId();
    if (!link->getStatus()->isOniLinkable())
    {
        if (zone == 12 || zone == 5 || zone == 6 || zone == 4 || zone == 10 || zone == 2 || zone == 9)
        {
            if (!scene->getMonsters(19))
                monstre1 = 1 + (rand() % 14);
            if (!scene->getMonsters(24))
                monstre2 = 1 + (rand() % 14);
            if (monstre2 == monstre1)
                monstre2 = 0;
            if (!scene->getMonsters(35))
                monstre3 = 1 + (rand() % 14);
            if (monstre3 == monstre1 || monstre3 == monstre2)
                monstre3 = 0;
        }
    }

    // int tmp = 0;
    switch (map->getId())
    {
    case 1:
        addObject(new Pierre(16 * 15, 16 * 31, 1, map));
        addObject(new Pierre(16 * 17, 16 * 9, 1, map));
        addObject(new Pierre(16 * 18, 16 * 8, 1, map));
        addObject(new Pierre(16 * 24, 16 * 23, 1, map));
        addObject(new Pierre(16 * 36, 16 * 10, 1, map));
        addObject(new Pierre(16 * 56, 16 * 36, 1, map));
        addObject(new Pierre(16 * 60, 16 * 11, 1, map));
        addObject(new Pierre(16 * 68, 16 * 4, 1, map));
        addObject(new Pierre(16 * 77, 16 * 8, 1, map));
        addObject(new Pierre(16 * 34, 16 * 45, 2, map));
        addObject(new Pierre(16 * 35, 16 * 45, 2, map));
        addObject(new Pierre(16 * 67, 16 * 25, 2, map));
        addObject(new Pancarte(16 * 3, 16 * 32, 169, map));
        addObject(new Pancarte(16 * 28, 16 * 15, 170, map));
        addObject(new Pancarte(16 * 56, 16 * 3, 171, map));
        addObject(new Pancarte(16 * 68, 16 * 43, 172, map));

        addObject(new Coffre(65 * 16, 19 * 16, 0, inventory->hasObject(BOTTES), TI_BOTTES));

        if (!inventory->hasQuartCoeur(0))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 10 * 16, 5 * 16, 0));
        }
        if (!inventory->hasQuartCoeur(1))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 76 * 16 + 8, 56 * 16 + 8, 1));
        }

        addEnnemi(new Ennemi003(56 * 16 + 2, 45 * 16 - 1));
        addEnnemi(new Ennemi003(58 * 16 + 2, 22 * 16 - 1));
        addEnnemi(new Ennemi003(69 * 16 + 2, 24 * 16 - 1));

        addEnnemi(new Ennemi004(13 * 16, 52 * 16 - 1));
        addEnnemi(new Ennemi004(29 * 16, 29 * 16 - 1));

        if (scene->getAvancement() < AV_PIT_A_VOIR)
        {
            addObject(new Pnj(16 * 29 + 8, 16 * 15, 47, 174));
        }
        break;
    case 2:
        addObject(new Pierre(16 * 14, 16 * 36, 1, map));
        addObject(new Pierre(16 * 18, 16 * 2, 1, map));
        addObject(new Pierre(16 * 19, 16 * 3, 1, map));
        addObject(new Pierre(16 * 20, 16 * 3, 1, map));
        addObject(new Pierre(16 * 21, 16 * 2, 1, map));
        addObject(new Pierre(16 * 35, 16 * 18, 1, map));
        addObject(new Pierre(16 * 50, 16 * 4, 1, map));
        addObject(new Pierre(16 * 79, 16 * 16, 1, map));
        addObject(new Pierre(16 * 79, 16 * 17, 1, map));
        addObject(new Pierre(16 * 84, 16 * 50, 1, map));
        addObject(new Pierre(16 * 111, 16 * 6, 1, map));
        addObject(new Pierre(16 * 31, 16 * 8, 2, map));
        addObject(new Pierre(16 * 52, 16 * 16, 2, map));
        addObject(new Pierre(16 * 72, 16 * 53, 2, map));
        addObject(new Pancarte(16 * 97, 16 * 55, 178, map));
        addObject(new Pancarte(16 * 31, 16 * 43, 179, map));
        addObject(new Pancarte(16 * 16, 16 * 6, 180, map));
        addObject(new Pancarte(16 * 83, 16 * 4, 181, map));
        addObject(new Pancarte(16 * 54, 16 * 40, 182, map));
        addObject(new Pancarte(16 * 4, 16 * 52, 183, map));

        addEnnemi(new Ennemi008(21 * 16, 9 * 16));

        addEnnemi(new Ennemi053(108 * 16, 45 * 16));
        addEnnemi(new Ennemi053(70 * 16, 50 * 16));
        addEnnemi(new Ennemi053(70 * 16, 22 * 16));
        addEnnemi(new Ennemi053(20 * 16, 43 * 16));
        addEnnemi(new Ennemi053(11 * 16, 9 * 16));
        addEnnemi(new Ennemi053(70 * 16, 6 * 16));
        addEnnemi(new Ennemi053(35 * 16, 15 * 16));
        addEnnemi(new Ennemi053(105 * 16, 6 * 16));

        addEnnemi(new Ennemi054(114 * 16, 12 * 16, N));
        addEnnemi(new Ennemi054(114 * 16, 25 * 16, N));
        addEnnemi(new Ennemi054(112 * 16, 36 * 16, N));

        if (monstre1 == zone)
            addEnnemi(new Ennemi019(50 * 16, 49 * 16));
        if (monstre2 == zone)
            addEnnemi(new Ennemi024(50 * 16, 49 * 16, false));
        if (monstre3 == zone)
            addEnnemi(new Ennemi035(50 * 16, 49 * 16));

        // barriere
        if (!scene->getCoffre(0, 0))
        {
            addObject(new Barriere(16 * 87 + 8, 16 * 35 + 4, map));
        }
        if (scene->getCoffre(0, 1))
        {
            ouvrePorte(14, 29, 1);
        }

        if (!inventory->hasQuartCoeur(2))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 116 * 16, 32 * 16 + 8, 2));
        }
        if (!inventory->hasQuartCoeur(3))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 15 * 16, 23 * 16, 3));
        }
        break;
    case 3:
        addObject(new Pierre(16 * 11, 16 * 45, 1, map));
        addObject(new Pierre(16 * 31, 16 * 5, 1, map));
        addObject(new Pierre(16 * 49, 16 * 13, 1, map));
        addObject(new Pierre(16 * 67, 16 * 19, 1, map));
        addObject(new Pierre(16 * 37, 16 * 10, 2, map));
        addObject(new Pierre(16 * 38, 16 * 11, 2, map));
        addObject(new Pierre(16 * 39, 16 * 11, 2, map));
        addObject(new Pierre(16 * 40, 16 * 11, 2, map));
        addObject(new Pierre(16 * 41, 16 * 10, 2, map));
        addObject(new Pierre(16 * 76, 16 * 16, 2, map));
        addObject(new Pierre(16 * 77, 16 * 49, 2, map));
        addObject(new Pancarte(16 * 5, 16 * 14, 187, map));
        addObject(new Pancarte(16 * 35, 16 * 54, 184, map));
        addObject(new Pancarte(16 * 44, 16 * 5, 185, map));
        addObject(new Pancarte(16 * 70, 16 * 16, 186, map));

        addObject(new Pnj(16 * 16, 16 * 20, 7, 188));
        addObject(new Pnj(16 * 20, 16 * 12, 13, 194));
        addObject(new Pnj(16 * 58, 16 * 12, 14, 196));
        if (scene->getAvancement() >= AV_MINE_OUVERTE)
        {
            addObject(new Pnj(16 * 74, 16 * 15 + 8, 33, 197));
        }
        else
        {
            addObject(new Pnj(16 * 72 + 8, 16 * 15 + 8, 33, 197));
        }
        addObject(new Pnj(16 * 35 + 8, 16 * 40, 22, 201));
        addObject(new Pnj(16 * 21, 16 * 27 + 8, 23, 202));
        addObject(new Pnj(16 * 50, 16 * 31 + 8, 1, 203));

        if (scene->getCoffre(0, 2))
        {
            ouvrePorte(10, 12, 0);
        }

        if (!inventory->hasQuartCoeur(4))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 13 * 16 + 8, 9 * 16 + 8, 4));
        }
        break;
    case 4:
        addObject(new Pierre(16 * 17, 16 * 14, 1, map));
        addObject(new Pierre(16 * 27, 16 * 21, 1, map));
        addObject(new Pierre(16 * 38, 16 * 26, 1, map));
        addObject(new Pierre(16 * 39, 16 * 27, 1, map));
        addObject(new Pierre(16 * 40, 16 * 26, 1, map));
        addObject(new Pierre(16 * 50, 16 * 7, 1, map));
        addObject(new Pierre(16 * 62, 16 * 10, 1, map));
        addObject(new Pierre(16 * 63, 16 * 11, 1, map));
        addObject(new Pierre(16 * 64, 16 * 11, 1, map));
        addObject(new Pierre(16 * 65, 16 * 10, 1, map));
        addObject(new Pancarte(16 * 5, 16 * 27, 207, map));
        addObject(new Pancarte(16 * 46, 16 * 29, 206, map));
        addObject(new Pancarte(16 * 64, 16 * 54, 205, map));
        addObject(new Pancarte(16 * 73, 16 * 14, 204, map));

        addEnnemi(new Ennemi001(29 * 16, 33 * 16 + 6));
        addEnnemi(new Ennemi001(40 * 16, 34 * 16 + 6));
        addEnnemi(new Ennemi001(52 * 16, 29 * 16 + 6));
        addEnnemi(new Ennemi001(59 * 16, 35 * 16 + 6));
        addEnnemi(new Ennemi001(50 * 16, 41 * 16 + 6));
        addEnnemi(new Ennemi001(30 * 16, 41 * 16 + 6));
        addEnnemi(new Ennemi001(19 * 16, 35 * 16 + 6));
        addEnnemi(new Ennemi001(12 * 16, 25 * 16 + 6));
        addEnnemi(new Ennemi001(12 * 16, 40 * 16 + 6));
        addEnnemi(new Ennemi001(30 * 16, 47 * 16 + 6));
        addEnnemi(new Ennemi001(50 * 16, 47 * 16 + 6));
        addEnnemi(new Ennemi001(65 * 16, 40 * 16 + 6));
        addEnnemi(new Ennemi001(65 * 16, 25 * 16 + 6));
        addEnnemi(new Ennemi001(40 * 16, 15 * 16 + 6));
        addEnnemi(new Ennemi001(25 * 16, 15 * 16 + 6));

        addEnnemi(new Ennemi054(12 * 16, 8 * 16, S));
        addEnnemi(new Ennemi054(7 * 16, 18 * 16, S));
        addEnnemi(new Ennemi054(7 * 16, 47 * 16, S));
        addEnnemi(new Ennemi054(19 * 16, 53 * 16, S));
        addEnnemi(new Ennemi054(33 * 16, 53 * 16, S));
        addEnnemi(new Ennemi054(47 * 16, 53 * 16, S));
        addEnnemi(new Ennemi054(26 * 16, 8 * 16, S));
        addEnnemi(new Ennemi054(40 * 16, 8 * 16, S));
        addEnnemi(new Ennemi054(65 * 16, 15 * 16, S));
        addEnnemi(new Ennemi054(71 * 16, 29 * 16, N));
        addEnnemi(new Ennemi054(71 * 16, 43 * 16, N));

        if (monstre1 == zone)
            addEnnemi(new Ennemi019(24 * 16, 32 * 16));
        if (monstre2 == zone)
            addEnnemi(new Ennemi024(24 * 16, 32 * 16, false));
        if (monstre3 == zone)
            addEnnemi(new Ennemi035(24 * 16, 32 * 16));

        if (!inventory->hasQuartCoeur(5))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 64 * 16, 5 * 16 + 8, 5));
        }
        break;
    case 5:
        addObject(new Pierre(16 * 4, 16 * 35, 1, map));
        addObject(new Pierre(16 * 61, 16 * 28, 1, map));
        addObject(new Pierre(16 * 74, 16 * 45, 1, map));
        addObject(new Pierre(16 * 77, 16 * 17, 1, map));
        addObject(new Pierre(16 * 89, 16 * 65, 1, map));
        addObject(new Pierre(16 * 91, 16 * 26, 1, map));
        addObject(new Pierre(16 * 108, 16 * 14, 1, map));
        addObject(new Pierre(16 * 108, 16 * 55, 1, map));
        addObject(new Pierre(16 * 113, 16 * 54, 1, map));
        addObject(new Pierre(16 * 116, 16 * 77, 1, map));
        addObject(new Pierre(16 * 118, 16 * 53, 1, map));
        addObject(new Pierre(16 * 128, 16 * 56, 1, map));
        addObject(new Pierre(16 * 129, 16 * 42, 1, map));
        addObject(new Pierre(16 * 130, 16 * 37, 1, map));
        addObject(new Pierre(16 * 131, 16 * 32, 1, map));
        addObject(new Pierre(16 * 132, 16 * 19, 1, map));
        addObject(new Pierre(16 * 132, 16 * 52, 1, map));
        addObject(new Pierre(16 * 136, 16 * 68, 1, map));
        addObject(new Pierre(16 * 148, 16 * 35, 1, map));
        addObject(new Pierre(16 * 154, 16 * 15, 1, map));
        addObject(new Pierre(16 * 158, 16 * 55, 1, map));
        addObject(new Pierre(16 * 170, 16 * 29, 1, map));
        addObject(new Pierre(16 * 182, 16 * 47, 1, map));
        addObject(new Pierre(16 * 191, 16 * 15, 1, map));
        addObject(new Pierre(16 * 191, 16 * 29, 1, map));
        addObject(new Pierre(16 * 192, 16 * 15, 1, map));
        addObject(new Pierre(16 * 192, 16 * 59, 1, map));
        addObject(new Pierre(16 * 193, 16 * 15, 1, map));
        addObject(new Pierre(16 * 69, 16 * 59, 2, map));
        addObject(new Pierre(16 * 78, 16 * 33, 2, map));
        addObject(new Pierre(16 * 79, 16 * 73, 2, map));
        addObject(new Pierre(16 * 97, 16 * 51, 2, map));
        addObject(new Pierre(16 * 112, 16 * 34, 2, map));
        addObject(new Pierre(16 * 117, 16 * 22, 2, map));
        addObject(new Pierre(16 * 131, 16 * 82, 2, map));
        addObject(new Pierre(16 * 145, 16 * 52, 2, map));
        addObject(new Pierre(16 * 154, 16 * 70, 2, map));
        addObject(new Pierre(16 * 156, 16 * 26, 2, map));
        addObject(new Pierre(16 * 169, 16 * 78, 2, map));
        addObject(new Pierre(16 * 173, 16 * 42, 2, map));
        addObject(new Pierre(16 * 195, 16 * 43, 2, map));
        addObject(new Pancarte(16 * 23, 16 * 71, 208, map));
        addObject(new Pancarte(16 * 36, 16 * 30, 209, map));
        addObject(new Pancarte(16 * 46, 16 * 62, 210, map));
        addObject(new Pancarte(16 * 181, 16 * 73, 211, map));

        addEnnemi(new Ennemi007(186 * 16, 12 * 16));
        addEnnemi(new Ennemi007(158 * 16, 61 * 16));
        addEnnemi(new Ennemi007(139 * 16, 45 * 16));
        addEnnemi(new Ennemi007(130 * 16, 75 * 16));
        addEnnemi(new Ennemi007(104 * 16, 61 * 16));
        addEnnemi(new Ennemi007(80 * 16, 43 * 16));
        addEnnemi(new Ennemi007(73 * 16, 25 * 16));
        addEnnemi(new Ennemi007(100 * 16, 28 * 16));
        addEnnemi(new Ennemi007(121 * 16, 21 * 16));
        addEnnemi(new Ennemi007(95 * 16, 40 * 16));
        addEnnemi(new Ennemi007(60 * 16, 42 * 16));
        addEnnemi(new Ennemi007(30 * 16, 49 * 16));
        addEnnemi(new Ennemi007(6 * 16, 60 * 16));
        addEnnemi(new Ennemi007(15 * 16, 85 * 16));
        addEnnemi(new Ennemi007(41 * 16, 86 * 16));

        addEnnemi(new Ennemi013(37 * 16, 24 * 16 - 4));
        addEnnemi(new Ennemi013(63 * 16, 34 * 16 - 4));
        addEnnemi(new Ennemi013(72 * 16, 20 * 16 - 4));
        addEnnemi(new Ennemi013(73 * 16, 53 * 16 - 4));
        addEnnemi(new Ennemi013(91 * 16, 40 * 16 - 4));
        addEnnemi(new Ennemi013(96 * 16, 17 * 16 - 4));
        addEnnemi(new Ennemi013(99 * 16, 72 * 16 - 4));
        addEnnemi(new Ennemi013(120 * 16, 65 * 16 - 4));
        addEnnemi(new Ennemi013(141 * 16, 23 * 16 - 4));
        addEnnemi(new Ennemi013(144 * 16, 74 * 16 - 4));
        addEnnemi(new Ennemi013(153 * 16, 56 * 16 - 4));
        addEnnemi(new Ennemi013(161 * 16, 33 * 16 - 4));
        addEnnemi(new Ennemi013(165 * 16, 17 * 16 - 4));
        addEnnemi(new Ennemi013(172 * 16, 55 * 16 - 4));
        addEnnemi(new Ennemi013(179 * 16, 41 * 16 - 4));
        addEnnemi(new Ennemi013(188 * 16, 53 * 16 - 4));

        addEnnemi(new Ennemi014(71 * 16 - 12, 35 * 16));
        addEnnemi(new Ennemi014(84 * 16 - 12, 19 * 16));
        addEnnemi(new Ennemi014(86 * 16 - 12, 31 * 16));
        addEnnemi(new Ennemi014(100 * 16 - 12, 48 * 16));
        addEnnemi(new Ennemi014(111 * 16 - 12, 18 * 16));
        addEnnemi(new Ennemi014(128 * 16 - 12, 25 * 16));
        addEnnemi(new Ennemi014(130 * 16 - 12, 14 * 16));
        addEnnemi(new Ennemi014(133 * 16 - 12, 60 * 16));
        addEnnemi(new Ennemi014(142 * 16 - 12, 31 * 16));
        addEnnemi(new Ennemi014(148 * 16 - 12, 67 * 16));
        addEnnemi(new Ennemi014(151 * 16 - 12, 47 * 16));
        addEnnemi(new Ennemi014(165 * 16 - 12, 49 * 16));
        addEnnemi(new Ennemi014(169 * 16 - 12, 37 * 16));
        addEnnemi(new Ennemi014(177 * 16 - 12, 61 * 16));
        addEnnemi(new Ennemi014(179 * 16 - 12, 30 * 16));

        addEnnemi(new Ennemi015(17 * 16 + 4, 34 * 16));
        addEnnemi(new Ennemi015(25 * 16 + 4, 34 * 16));
        addEnnemi(new Ennemi015(82 * 16, 37 * 16));
        addEnnemi(new Ennemi015(83 * 16, 58 * 16));
        addEnnemi(new Ennemi015(142 * 16, 56 * 16));
        addEnnemi(new Ennemi015(157 * 16, 22 * 16));

        if (monstre1 == zone)
            addEnnemi(new Ennemi019(157 * 16, 32 * 16));
        if (monstre2 == zone)
            addEnnemi(new Ennemi024(157 * 16, 32 * 16, false));
        if (monstre3 == zone)
            addEnnemi(new Ennemi035(157 * 16, 32 * 16));

        if (scene->getCoffre(0, 3))
        {
            ouvrePorte(25, 68, 0);
        }

        if (!inventory->hasQuartCoeur(6))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 194 * 16 + 8, 18 * 16 + 8, 6));
        }
        if (!inventory->hasQuartCoeur(7))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 70 * 16 + 8, 71 * 16 + 8, 7));
        }
        break;
    case 6:
        addObject(new Pierre(16 * 17, 16 * 53, 1, map));
        addObject(new Pierre(16 * 36, 16 * 53, 1, map));
        addObject(new Pierre(16 * 87, 16 * 53, 2, map));
        addObject(new Pancarte(16 * 16, 16 * 45, 212, map));
        addObject(new Pancarte(16 * 30, 16 * 26, 213, map));
        addObject(new Pancarte(16 * 41, 16 * 12, 214, map));
        addObject(new Pancarte(16 * 50, 16 * 49, 215, map));
        addObject(new Pancarte(16 * 109, 16 * 33, 216, map));
        addObject(new Pancarte(16 * 110, 16 * 5, 217, map));

        addEnnemi(new Ennemi009(46 * 16 + 8, 45 * 16 + 8));
        addEnnemi(new Ennemi009(85 * 16, 51 * 16 + 8));
        addEnnemi(new Ennemi009(105 * 16 + 8, 45 * 16 + 8));
        addEnnemi(new Ennemi009(110 * 16 + 8, 41 * 16 + 8));
        addEnnemi(new Ennemi009(50 * 16, 12 * 16 + 8));
        addEnnemi(new Ennemi009(66 * 16, 13 * 16 + 8));
        addEnnemi(new Ennemi009(81 * 16, 6 * 16 + 8));
        addEnnemi(new Ennemi009(94 * 16, 7 * 16 + 8));
        addEnnemi(new Ennemi009(37 * 16, 51 * 16 + 8));
        addEnnemi(new Ennemi009(51 * 16, 51 * 16 + 8));

        addEnnemi(new Ennemi010(9 * 16, 28 * 16));
        addEnnemi(new Ennemi010(15 * 16, 12 * 16));
        addEnnemi(new Ennemi010(30 * 16, 36 * 16));
        addEnnemi(new Ennemi010(65 * 16, 40 * 16));
        addEnnemi(new Ennemi010(75 * 16, 28 * 16));

        addEnnemi(new Ennemi027(41 * 16, 32 * 16 - 1));
        addEnnemi(new Ennemi027(52 * 16, 32 * 16 - 1));

        if (monstre1 == zone)
            addEnnemi(new Ennemi019(46 * 16, 49 * 16));
        if (monstre2 == zone)
            addEnnemi(new Ennemi024(46 * 16, 49 * 16, false));
        if (monstre3 == zone)
            addEnnemi(new Ennemi035(46 * 16, 49 * 16));

        if (scene->getCoffre(0, 4))
        {
            ouvrePorte(92, 31, 1);
        }

        if (!inventory->hasQuartCoeur(8))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 89 * 16, 28 * 16 + 8, 8));
        }
        break;
    case 7:
        addObject(new Pierre(16 * 21, 16 * 12, 1, map));
        addObject(new Pierre(16 * 37, 16 * 55, 1, map));
        addObject(new Pierre(16 * 38, 16 * 54, 1, map));
        addObject(new Pierre(16 * 39, 16 * 54, 1, map));
        addObject(new Pierre(16 * 40, 16 * 54, 1, map));
        addObject(new Pierre(16 * 41, 16 * 55, 1, map));
        addObject(new Pierre(16 * 62, 16 * 54, 2, map));
        addObject(new Pancarte(16 * 4, 16 * 42, 218, map));
        addObject(new Pancarte(16 * 19, 16 * 7, 219, map));
        addObject(new Pancarte(16 * 44, 16 * 43, 220, map));
        addObject(new Pancarte(16 * 74, 16 * 48, 221, map));
        if (scene->getAvancement() >= AV_MANOIR_OUVERT)
        {
            addObject(new Pnj(16 * 13 + 8 - 3, 16 * 13 + 5, 46, 222));
        }
        else
        {
            addObject(new Pnj(16 * 16 - 3, 16 * 12 + 8 + 5, 46, 222));
        }
        if (scene->getAvancement() < AV_ZELDA_CHEZ_PIT || scene->getAvancement() >= AV_FILLE_MAIRE_SAUVEE)
        {
            addObject(new Pnj(16 * 34 + 8, 16 * 35, 2, 224));
            addObject(new Pnj(16 * 23 + 8, 16 * 34, 10, 229));
            addObject(new Pnj(16 * 53 + 8, 16 * 19, 9, 230));
            addObject(new Pnj(16 * 42, 16 * 27, 11, 231));
            addObject(new Pnj(16 * 45 + 8, 16 * 29 + 8, 34, 232));
            addObject(new Pnj(16 * 27, 16 * 14, 35, 234));
            addObject(new Pnj(16 * 61, 16 * 39, 36, 235));
            addObject(new Poule(16 * 15, 16 * 34));
            addObject(new Poule(16 * 16, 16 * 36));
            addObject(new Poule(16 * 18, 16 * 34));
            addObject(new Poule(16 * 20, 16 * 36));
            addObject(new Poule(16 * 22, 16 * 34));
        }
        addObject(new Sphere(3 * 16, 45 * 16));
        break;
    case 8:
        addObject(new Pierre(16 * 4, 16 * 12, 1, map));
        addObject(new Pierre(16 * 4, 16 * 28, 1, map));
        addObject(new Pierre(16 * 7, 16 * 49, 1, map));
        addObject(new Pierre(16 * 36, 16 * 45, 1, map));
        addObject(new Pancarte(16 * 10, 16 * 45, 236, map));
        addObject(new Pancarte(16 * 18, 16 * 14, 237, map));
        addObject(new Pancarte(16 * 25, 16 * 43, 238, map));
        addObject(new Pancarte(16 * 36, 16 * 28, 239, map));

        addEnnemi(new Ennemi008(10 * 16, 31 * 16));
        addEnnemi(new Ennemi008(17 * 16, 35 * 16));
        addEnnemi(new Ennemi008(19 * 16, 44 * 16));
        addEnnemi(new Ennemi008(27 * 16, 46 * 16));
        addEnnemi(new Ennemi008(33 * 16, 30 * 16));
        addEnnemi(new Ennemi008(21 * 16 + 8, 14 * 16));

        addEnnemi(new Ennemi054(1 * 16, 35 * 16, S));
        addEnnemi(new Ennemi054(4 * 16, 47 * 16, S));
        addEnnemi(new Ennemi054(21 * 16, 51 * 16, N));
        addEnnemi(new Ennemi054(32 * 16, 51 * 16, N));

        if (scene->getCoffre(0, 5))
        {
            ouvrePorte(21, 20, 1);
        }
        break;
    case 9:
        addObject(new Pierre(16 * 7, 16 * 97, 1, map));
        addObject(new Pierre(16 * 21, 16 * 82, 1, map));
        addObject(new Pierre(16 * 38, 16 * 57, 1, map));
        addObject(new Pierre(16 * 43, 16 * 104, 1, map));
        addObject(new Pierre(16 * 44, 16 * 69, 1, map));
        addObject(new Pierre(16 * 45, 16 * 90, 1, map));
        addObject(new Pierre(16 * 64, 16 * 68, 1, map));

        addObject(new Pierre(16 * 2, 16 * 21, 2, map));
        addObject(new Pierre(16 * 2, 16 * 24, 2, map));
        addObject(new Pierre(16 * 3, 16 * 22, 2, map));
        addObject(new Pierre(16 * 3, 16 * 23, 2, map));
        addObject(new Pierre(16 * 26, 16 * 101, 2, map));
        addObject(new Pierre(16 * 45, 16 * 23, 2, map));
        addObject(new Pierre(16 * 50, 16 * 6, 2, map));
        addObject(new Pierre(16 * 64, 16 * 54, 2, map));

        addObject(new Pancarte(16 * 7, 16 * 89, 240, map));
        addObject(new Pancarte(16 * 7, 16 * 18, 241, map));
        addObject(new Pancarte(16 * 35, 16 * 80, 242, map));
        addObject(new Pancarte(16 * 37, 16 * 32, 243, map));
        addObject(new Pancarte(16 * 37, 16 * 101, 244, map));
        addObject(new Pancarte(16 * 65, 16 * 99, 245, map));
        addObject(new Pancarte(16 * 68, 16 * 9, 246, map));

        if (scene->getAvancement() == AV_ARMEE_UP)
        {
            addEnnemi(new Ennemi046(64 * 16 - 3, 29 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(59 * 16 - 3, 40 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(26 * 16 - 3, 71 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(22 * 16 - 3, 81 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(27 * 16 - 3, 94 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(41 * 16 - 3, 100 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(54 * 16 - 3, 97 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(65 * 16 - 3, 86 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(52 * 16 - 3, 80 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(40 * 16 - 3, 73 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(66 * 16 - 3, 71 * 16 + 8 - 11));
            addEnnemi(new Ennemi046(58 * 16 - 3, 59 * 16 + 8 - 11));

            addEnnemi(new Ennemi047(20 * 16 - 3, 52 * 16 + 8 - 11));
            addEnnemi(new Ennemi047(31 * 16 - 3, 52 * 16 + 8 - 11));
            addEnnemi(new Ennemi047(17 * 16 - 3, 41 * 16 + 8 - 11));
            addEnnemi(new Ennemi047(8 * 16 - 3, 35 * 16 + 8 - 11));
            addEnnemi(new Ennemi047(14 * 16 - 3, 15 * 16 + 8 - 11));
            addEnnemi(new Ennemi047(33 * 16 - 3, 10 * 10 + 8 - 11));
            addEnnemi(new Ennemi047(13 * 16 - 3, 24 * 16 + 8 - 11));

            addEnnemi(new Ennemi048(52 * 16 - 3, 9 * 16 + 8 - 11));
        }
        else
        {
            addEnnemi(new Ennemi054(12 * 16, 2 * 16, N));
            addEnnemi(new Ennemi054(30 * 16, 2 * 16, N));
            addEnnemi(new Ennemi054(48 * 16, 2 * 16, N));
            addEnnemi(new Ennemi054(76 * 16, 24 * 16, N));
            addEnnemi(new Ennemi054(67 * 16, 40 * 16, N));
            addEnnemi(new Ennemi054(67 * 16, 60 * 16, N));
            addEnnemi(new Ennemi054(73 * 16, 77 * 16, N));
            addEnnemi(new Ennemi054(73 * 16, 98 * 16, N));
            addEnnemi(new Ennemi054(7 * 16, 53 * 16, S));
            addEnnemi(new Ennemi054(34 * 16, 79 * 16, N));
            addEnnemi(new Ennemi054(45 * 16, 84 * 16, S));

            addEnnemi(new Ennemi055(46 * 16 + 5, 8 * 16));
            addEnnemi(new Ennemi055(14 * 16 + 5, 9 * 16));
            addEnnemi(new Ennemi055(69 * 16 + 5, 26 * 16));
            addEnnemi(new Ennemi055(12 * 16 + 5, 34 * 16));
            addEnnemi(new Ennemi055(21 * 16 + 5, 53 * 16));
            addEnnemi(new Ennemi055(32 * 16 + 5, 53 * 16));
            addEnnemi(new Ennemi055(61 * 16 + 5, 53 * 16));
            addEnnemi(new Ennemi055(40 * 16 + 5, 71 * 16));
            addEnnemi(new Ennemi055(59 * 16 + 5, 81 * 16));
            addEnnemi(new Ennemi055(26 * 16 + 5, 91 * 16));
            addEnnemi(new Ennemi055(43 * 16 + 5, 98 * 16));

            if (monstre1 == zone)
                addEnnemi(new Ennemi019(50 * 16, 92 * 16));
            if (monstre2 == zone)
                addEnnemi(new Ennemi024(50 * 16, 92 * 16, false));
            if (monstre3 == zone)
                addEnnemi(new Ennemi035(50 * 16, 92 * 16));
        }

        if (scene->getCoffre(0, 6))
        {
            ouvrePorte(39, 86, 0);
        }

        if (!inventory->hasQuartCoeur(9))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 66 * 16, 30 * 16 + 8, 9));
        }
        if (!inventory->hasQuartCoeur(10))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 44 * 16 + 8, 80 * 16 + 8, 10));
        }
        if (!inventory->hasQuartCoeur(11))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 18 * 16 + 8, 115 * 16 + 8, 11));
        }
        break;
    case 10:
        addObject(new Pierre(16 * 11, 16 * 17, 1, map));
        addObject(new Pierre(16 * 16, 16 * 29, 1, map));
        addObject(new Pierre(16 * 37, 16 * 46, 1, map));

        addObject(new Pierre(16 * 6, 16 * 40, 2, map));
        addObject(new Pierre(16 * 14, 16 * 57, 2, map));
        addObject(new Pierre(16 * 19, 16 * 13, 2, map));
        addObject(new Pierre(16 * 30, 16 * 32, 2, map));
        addObject(new Pierre(16 * 51, 16 * 57, 2, map));

        addObject(new Pancarte(16 * 8, 16 * 47, 249, map));
        addObject(new Pancarte(16 * 36, 16 * 9, 250, map));
        addObject(new Pancarte(16 * 49, 16 * 54, 251, map));
        addObject(new Pancarte(16 * 69, 16 * 44, 252, map));

        addEnnemi(new Ennemi012(11 * 16, 19 * 16));
        addEnnemi(new Ennemi012(11 * 16, 53 * 16));
        addEnnemi(new Ennemi012(20 * 16, 7 * 16));
        addEnnemi(new Ennemi012(38 * 16, 55 * 16));
        addEnnemi(new Ennemi012(12 * 16, 36 * 16));
        addEnnemi(new Ennemi012(58 * 16, 5 * 16));
        addEnnemi(new Ennemi012(60 * 16, 19 * 16));
        addEnnemi(new Ennemi012(74 * 16, 33 * 16));

        addEnnemi(new Ennemi053(8 * 16, 26 * 16));
        addEnnemi(new Ennemi053(11 * 16, 43 * 16));
        addEnnemi(new Ennemi053(16 * 16, 16 * 16));
        addEnnemi(new Ennemi053(25 * 16, 55 * 16));
        addEnnemi(new Ennemi053(27 * 16, 34 * 16));
        addEnnemi(new Ennemi053(35 * 16, 44 * 16));
        addEnnemi(new Ennemi053(51 * 16, 52 * 16));
        addEnnemi(new Ennemi053(70 * 16, 44 * 16));

        if (monstre1 == zone)
            addEnnemi(new Ennemi019(60 * 16, 24 * 16));
        if (monstre2 == zone)
            addEnnemi(new Ennemi024(60 * 16, 24 * 16, false));
        if (monstre3 == zone)
            addEnnemi(new Ennemi035(60 * 16, 24 * 16));

        if (scene->getCoffre(0, 7))
        {
            ouvrePorte(24, 38, 1);
        }

        if (!inventory->hasQuartCoeur(12))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 66 * 16 + 8, 7 * 16 + 8, 12));
        }
        break;
    case 11:
        addObject(new Pierre(16 * 20, 16 * 2, 2, map));
        addObject(new Pierre(16 * 21, 16 * 3, 2, map));
        addObject(new Pierre(16 * 22, 16 * 3, 2, map));
        addObject(new Pierre(16 * 23, 16 * 3, 2, map));
        addObject(new Pierre(16 * 24, 16 * 2, 2, map));

        addObject(new Pierre(16 * 3, 16 * 57, 3, map));
        addObject(new Pierre(16 * 15, 16 * 14, 3, map));
        addObject(new Pierre(16 * 18, 16 * 44, 3, map));
        addObject(new Pierre(16 * 19, 16 * 23, 3, map));
        addObject(new Pierre(16 * 21, 16 * 34, 3, map));
        addObject(new Pierre(16 * 26, 16 * 48, 3, map));
        addObject(new Pierre(16 * 30, 16 * 14, 3, map));
        addObject(new Pierre(16 * 37, 16 * 31, 3, map));
        addObject(new Pierre(16 * 50, 16 * 23, 3, map));
        addObject(new Pierre(16 * 51, 16 * 57, 3, map));
        addObject(new Pierre(16 * 3, 16 * 57, 3, map));
        addObject(new Pierre(16 * 61, 16 * 23, 3, map));
        addObject(new Pierre(16 * 66, 16 * 34, 3, map));
        addObject(new Pierre(16 * 67, 16 * 52, 3, map));

        addObject(new Pancarte(16 * 6, 16 * 55, 253, map));
        addObject(new Pancarte(16 * 21, 16 * 6, 254, map));
        addObject(new Pancarte(16 * 26, 16 * 45, 255, map));
        addObject(new Pancarte(16 * 38, 16 * 47, 256, map));
        addObject(new Pancarte(16 * 62, 16 * 45, 255, map));
        addObject(new Pancarte(16 * 70, 16 * 49, 257, map));

        addObject(new Pnj(16 * 20 + 8, 16 * 17, 3, 258));
        addObject(new Pnj(16 * 51 + 8, 16 * 16 - 1, 4, 259));
        addObject(new Pnj(16 * 35 + 8 + 2, 16 * 27, 5, 260));
        addObject(new Pnj(16 * 56 + 8, 16 * 34, 6, 261));
        break;
    case 12:
        addObject(new Pierre(16 * 4, 16 * 44, 3, map));
        addObject(new Pierre(16 * 29, 16 * 48, 3, map));
        addObject(new Pierre(16 * 34, 16 * 36, 3, map));
        addObject(new Pierre(16 * 51, 16 * 48, 3, map));
        addObject(new Pierre(16 * 66, 16 * 32, 3, map));

        addObject(new Pancarte(16 * 13, 16 * 13, 262, map));
        addObject(new Pancarte(16 * 18, 16 * 48, 263, map));
        addObject(new Pancarte(16 * 43, 16 * 20, 264, map));
        addObject(new Pancarte(16 * 61, 16 * 8, 265, map));
        addObject(new Pancarte(16 * 70, 16 * 32, 266, map));

        addObject(new TalkableArea(16 * 5 + 8, 16 * 9, 297));
        addObject(new TalkableArea(16 * 9 + 8, 16 * 9, 296));
        addObject(new TalkableArea(16 * 13 + 8, 16 * 9, 294));
        addObject(new TalkableArea(16 * 17 + 8, 16 * 9, 295));
        addObject(new TalkableArea(16 * 21 + 8, 16 * 9, 298));

        addEnnemi(new Ennemi011(10 * 16, 18 * 16));
        addEnnemi(new Ennemi011(15 * 16, 50 * 16));
        addEnnemi(new Ennemi011(58 * 16, 38 * 16));
        addEnnemi(new Ennemi011(60 * 16, 12 * 16));

        addEnnemi(new Ennemi056(7 * 16 - 1, 10 * 16 - 1));
        addEnnemi(new Ennemi056(7 * 16 - 1, 16 * 16 - 1));
        addEnnemi(new Ennemi056(7 * 16 - 1, 47 * 16 - 1));
        addEnnemi(new Ennemi056(20 * 16 - 1, 10 * 16 - 1));
        addEnnemi(new Ennemi056(28 * 16 - 1, 39 * 16 - 1));
        addEnnemi(new Ennemi056(33 * 16 - 1, 10 * 16 - 1));
        addEnnemi(new Ennemi056(33 * 16 - 1, 24 * 16 - 1));
        addEnnemi(new Ennemi056(46 * 16 - 1, 24 * 16 - 1));
        addEnnemi(new Ennemi056(58 * 16 - 1, 16 * 16 - 1));
        addEnnemi(new Ennemi056(49 * 16 - 1, 42 * 16 - 1));
        addEnnemi(new Ennemi056(62 * 16 - 1, 31 * 16 - 1));
        addEnnemi(new Ennemi056(69 * 16 - 1, 16 * 16 - 1));

        if (monstre1 == zone)
            addEnnemi(new Ennemi019(55 * 16, 43 * 16));
        if (monstre2 == zone)
            addEnnemi(new Ennemi024(55 * 16, 43 * 16, false));
        if (monstre3 == zone)
            addEnnemi(new Ennemi035(55 * 16, 43 * 16));
        break;
    case 13:
        addObject(new Pancarte(16 * 39, 16 * 36, 267, map));
        addObject(new Pancarte(16 * 48, 16 * 8, 246, map));
        addObject(new Pancarte(16 * 74, 16 * 22, 266, map));

        addObject(new Pnj(16 * 42, 16 * 32, 37, 268));
        addObject(new Pnj(16 * 58, 16 * 30, 38, 269));
        addObject(new Pnj(16 * 26 + 4, 16 * 33, 39, 270));
        break;
    case 14:
        addObject(new Pierre(16 * 16, 16 * 82, 1, map));
        addObject(new Pierre(16 * 20, 16 * 49, 1, map));
        addObject(new Pierre(16 * 25, 16 * 65, 1, map));
        addObject(new Pierre(16 * 36, 16 * 69, 1, map));
        addObject(new Pierre(16 * 40, 16 * 59, 1, map));
        addObject(new Pierre(16 * 42, 16 * 33, 1, map));
        addObject(new Pierre(16 * 51, 16 * 78, 1, map));
        addObject(new Pierre(16 * 52, 16 * 78, 1, map));
        addObject(new Pierre(16 * 55, 16 * 52, 1, map));
        addObject(new Pierre(16 * 62, 16 * 73, 1, map));
        addObject(new Pierre(16 * 88, 16 * 51, 1, map));
        addObject(new Pierre(16 * 100, 16 * 55, 1, map));
        addObject(new Pierre(16 * 104, 16 * 82, 1, map));
        addObject(new Pierre(16 * 117, 16 * 70, 1, map));
        addObject(new Pierre(16 * 131, 16 * 59, 1, map));
        addObject(new Pierre(16 * 149, 16 * 85, 1, map));

        addObject(new Pierre(16 * 8, 16 * 53, 2, map));
        addObject(new Pierre(16 * 29, 16 * 75, 2, map));
        addObject(new Pierre(16 * 30, 16 * 53, 2, map));
        addObject(new Pierre(16 * 50, 16 * 57, 2, map));
        addObject(new Pierre(16 * 53, 16 * 66, 2, map));
        addObject(new Pierre(16 * 72, 16 * 56, 2, map));
        addObject(new Pierre(16 * 99, 16 * 39, 2, map));
        addObject(new Pierre(16 * 100, 16 * 72, 2, map));
        addObject(new Pierre(16 * 117, 16 * 44, 2, map));
        addObject(new Pierre(16 * 126, 16 * 66, 2, map));

        addObject(new Pancarte(16 * 21, 16 * 58, 271, map));
        addObject(new Pancarte(16 * 27, 16 * 30, 272, map));
        addObject(new Pancarte(16 * 43, 16 * 80, 273, map));
        addObject(new Pancarte(16 * 63, 16 * 40, 274, map));
        addObject(new Pancarte(16 * 91, 16 * 38, 275, map));
        addObject(new Pancarte(16 * 131, 16 * 71, 276, map));
        addObject(new Pancarte(16 * 135, 16 * 13, 277, map));
        addObject(new Pancarte(16 * 146, 16 * 81, 278, map));

        addEnnemi(new Ennemi005(63 * 16, 54 * 16 - 10));
        addEnnemi(new Ennemi005(64 * 16, 69 * 16 - 10));
        addEnnemi(new Ennemi005(83 * 16, 52 * 16 - 10));
        addEnnemi(new Ennemi005(91 * 16, 41 * 16 - 10));
        addEnnemi(new Ennemi005(96 * 16, 53 * 16 - 10));
        addEnnemi(new Ennemi005(103 * 16, 67 * 16 - 10));
        addEnnemi(new Ennemi005(112 * 16, 79 * 16 - 10));
        addEnnemi(new Ennemi005(126 * 16, 60 * 16 - 10));
        addEnnemi(new Ennemi005(139 * 16, 70 * 16 - 10));
        addEnnemi(new Ennemi005(143 * 16, 62 * 16 - 10));
        addEnnemi(new Ennemi005(144 * 16, 79 * 16 - 10));
        addEnnemi(new Ennemi005(153 * 16, 72 * 16 - 10));

        addEnnemi(new Ennemi006(18 * 16, 27 * 16 - 21));
        addEnnemi(new Ennemi006(23 * 16, 27 * 16 - 21));
        addEnnemi(new Ennemi006(58 * 16, 41 * 16 - 21));
        addEnnemi(new Ennemi006(62 * 16, 41 * 16 - 21));
        addEnnemi(new Ennemi006(66 * 16, 77 * 16 - 21));
        addEnnemi(new Ennemi006(80 * 16, 63 * 16 - 21));
        addEnnemi(new Ennemi006(84 * 16, 63 * 16 - 21));
        addEnnemi(new Ennemi006(94 * 16, 58 * 16 - 21));
        addEnnemi(new Ennemi006(95 * 16, 45 * 16 - 21));
        addEnnemi(new Ennemi006(110 * 16 + 8, 74 * 16 - 21));
        addEnnemi(new Ennemi006(133 * 16, 78 * 16 - 21));
        addEnnemi(new Ennemi006(148 * 16, 76 * 16 - 21));
        addEnnemi(new Ennemi006(90 * 16, 80 * 16 - 21));

        addEnnemi(new Ennemi044(6 * 16 - 3, 57 * 16 - 10));
        addEnnemi(new Ennemi044(17 * 16 - 3, 81 * 16 - 10));
        addEnnemi(new Ennemi044(29 * 16 - 3, 72 * 16 - 10));
        addEnnemi(new Ennemi044(33 * 16 - 3, 61 * 16 - 10));

        if (scene->getCoffre(0, 8))
        {
            ouvrePorte(16, 55, 1);
        }
        if (scene->getCoffre(0, 9))
        {
            ouvrePorte(94, 34, 1);
        }
        addObject(new Stele(94 * 16, 35 * 16, 279, scene->getCoffre(0, 10)));

        if (!inventory->hasQuartCoeur(13))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 82 * 16 + 8, 64 * 16 + 8, 13));
        }
        break;
    case 15:
        if (!inventory->hasCoeur(0))
        {
            addEnnemi(new Ennemi057(88 * 16 + 8, 18 * 16 - 1, map));
        }
        if (!inventory->hasGraal(0))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GRAAL, 90 * 16, 6 * 16 + 8, 0));
        }

        addObject(new Coffre(30 * 16 + 8, 47 * 16, 0, scene->getCoffre(1, 0), TI_CARTE_DONJON));
        addObject(new Coffre(89 * 16 + 8, 37 * 16, 0, scene->getCoffre(1, 1), TI_BOUSSOLE));
        addObject(new Coffre(169 * 16 + 8, 22 * 16, 0, scene->getCoffre(1, 2), TI_CLE_BOSS));
        if (scene->getCoffre(1, 2) == 2)
            ouvrePorte(89, 28, 0);

        addObject(new Coffre(129 * 16, 6 * 16 + 8, 1, link->getEpee() > 0, TI_EPEE_1));

        addObject(new Coffre(29 * 16 + 8, 7 * 16, 0, scene->getCoffre(1, 4), TI_CLE, 4));
        addObject(new Coffre(69 * 16 + 8, 52 * 16, 0, scene->getCoffre(1, 5), TI_CLE, 5));
        addObject(new Coffre(169 * 16 + 8, 52 * 16, 0, scene->getCoffre(1, 6), TI_CLE, 6));
        addObject(new Coffre(189 * 16 + 8, 7 * 16, 0, scene->getCoffre(1, 7), TI_CLE, 7));

        if (scene->getCoffre(1, 8))
            ouvrePorte(18, 21, 1);
        if (scene->getCoffre(1, 9))
            ouvrePorte(38, 51, 1);
        if (scene->getCoffre(1, 10))
            ouvrePorte(109, 43, 0);
        if (scene->getCoffre(1, 11))
            ouvrePorte(178, 21, 1);
        if (scene->getCoffre(1, 12))
            ouvrePorte(9, 43, 0);
        if (scene->getCoffre(1, 13))
            ouvrePorte(29, 13, 0);
        if (scene->getCoffre(1, 14))
            ouvrePorte(49, 43, 0);

        addObject(new Interrupteur(7 * 16, 42 * 16, 0, scene->getCoffre(1, 12), map));
        addObject(new Interrupteur(27 * 16, 12 * 16, 0, scene->getCoffre(1, 13), map));
        addObject(new Interrupteur(52 * 16, 42 * 16, 0, scene->getCoffre(1, 14), map));
        addObject(new Interrupteur(95 * 16, 27 * 16, 0, true, map));

        addEnnemi(new Ennemi001(109 * 16 + 8, 21 * 16 + 6));
        addEnnemi(new Ennemi001(139 * 16 + 8, 47 * 16 + 6));
        addEnnemi(new Ennemi001(152 * 16 + 8, 6 * 16 + 6));
        addEnnemi(new Ennemi001(189 * 16 + 8, 21 * 16 + 6));

        addEnnemi(new Ennemi004(17 * 16, 52 * 16));
        addEnnemi(new Ennemi004(57 * 16, 7 * 16));
        addEnnemi(new Ennemi004(70 * 16, 53 * 16));
        addEnnemi(new Ennemi004(126 * 16, 32 * 16));
        addEnnemi(new Ennemi004(133 * 16, 32 * 16));

        addEnnemi(new Ennemi018(1 * 16, 16 * 16 + 2));
        addEnnemi(new Ennemi018(18 * 16, 16 * 16 + 2));
        addEnnemi(new Ennemi018(186 * 16, 29 * 16 + 2));
        addEnnemi(new Ennemi018(193 * 16, 29 * 16 + 2));
        addEnnemi(new Ennemi018(165 * 16, 20 * 16 + 2));
        addEnnemi(new Ennemi018(165 * 16, 23 * 16 + 2));

        addObject(new PiegePics(38 * 16, 25 * 16, S));
        addObject(new PiegePics(50 * 16, 25 * 16, S));
        addObject(new PiegePics(51 * 16, 37 * 16, S));
        addObject(new PiegePics(64 * 16, 36 * 16, S));
        addObject(new PiegePics(55 * 16 - 8, 2 * 16, S));
        addObject(new PiegePics(132 * 16, 51 * 16, S));
        addObject(new PiegePics(135 * 16, 51 * 16, S));
        addObject(new PiegePics(138 * 16, 51 * 16, S));
        addObject(new PiegePics(141 * 16, 39 * 16, S));
        addObject(new PiegePics(145 * 16 + 8, 40 * 16 + 8, S));
        addObject(new PiegePics(150 * 16, 42 * 16, S));

        addObject(new Jarre(5 * 16, 4 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(29 * 16, 39 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(45 * 16, 33 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(56 * 16, 29 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(64 * 16, 38 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(84 * 16, 34 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(95 * 16, 34 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(115 * 16, 57 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(126 * 16, 19 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(133 * 16, 19 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(149 * 16, 6 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(173 * 16, 4 * 16, 1, TI_PETIT_COEUR, map));

        addObject(new Jarre(10 * 16, 21 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(22 * 16, 17 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(24 * 16, 17 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(26 * 16, 42 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(42 * 16, 2 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(42 * 16, 12 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(43 * 16, 20 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(46 * 16, 33 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(47 * 16, 33 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(55 * 16, 29 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 35 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(84 * 16, 17 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(84 * 16, 27 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(95 * 16, 40 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(95 * 16, 17 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(104 * 16, 57 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(115 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(127 * 16, 19 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(132 * 16, 19 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(144 * 16, 14 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(154 * 16, 32 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(155 * 16, 14 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(155 * 16, 32 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(157 * 16, 32 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(166 * 16, 10 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(166 * 16, 4 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(195 * 16, 47 * 16, 1, TI_NO_ITEM, map));

        addObject(new Jarre(14 * 16, 4 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(23 * 16, 17 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(36 * 16, 20 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(54 * 16, 29 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(74 * 16, 20 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(84 * 16, 40 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(104 * 16, 47 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(156 * 16, 32 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(173 * 16, 10 * 16, 1, TI_RUBIS_VERT, map));
        addObject(new Jarre(184 * 16, 47 * 16, 1, TI_RUBIS_VERT, map));
        break;
    case 16:
        if (!inventory->hasCoeur(1))
        {
            addEnnemi(new Ennemi060(248 * 16 + 8 - 1, 77 * 16 - 2));
        }
        if (!inventory->hasObject(BOMBES))
        {
            addObject(new Pnj(16 * 249 + 8, 16 * 62 + 8, 43, 320));
        }

        if (!scene->getCoffre(2, 5))
            addObject(new Pnj(16 * 174, 16 * 17 + 8, 40, 324));
        if (!scene->getCoffre(2, 6))
            addObject(new Pnj(16 * 185, 16 * 17 + 8, 41, 324));
        if (!scene->getCoffre(2, 7))
            addObject(new Pnj(16 * 194, 16 * 62 + 8, 42, 324));

        addObject(new Coffre(9 * 16 + 8, 7 * 16, 0, scene->getCoffre(2, 0), TI_CARTE_DONJON));
        addObject(new Coffre(139 * 16, 32 * 16, 0, scene->getCoffre(2, 1), TI_BOUSSOLE));
        addObject(new Coffre(251 * 16, 29 * 16, 0, scene->getCoffre(2, 2), TI_CLE_BOSS));
        if (scene->getCoffre(2, 2) == 2)
            ouvrePorte(249, 88, 0);

        if (scene->getCoffre(2, 9))
            ouvrePorte(109, 28, 0);
        if (scene->getCoffre(2, 10))
            ouvrePorte(118, 66, 1);
        if (scene->getCoffre(2, 11))
            ouvrePorte(124, 73, 0);
        if (scene->getCoffre(2, 12))
            ouvrePorte(134, 73, 0);
        if (scene->getCoffre(2, 13))
            ouvrePorte(249, 13, 0);
        if (scene->getCoffre(2, 14))
            ouvrePorte(9, 13, 0);
        if (scene->getCoffre(2, 15))
            ouvrePorte(58, 51, 1);
        if (scene->getCoffre(2, 16))
            ouvrePorte(89, 13, 0);
        if (scene->getCoffre(2, 17))
            ouvrePorte(174, 22, 2);
        if (scene->getCoffre(2, 18))
            ouvrePorte(185, 22, 2);
        if (scene->getCoffre(2, 19))
            ouvrePorte(178, 66, 1);
        if (scene->getCoffre(2, 20))
            ouvrePorte(194, 66, 2);
        if (scene->getCoffre(2, 21))
            ouvrePorte(204, 13, 0);
        if (scene->getCoffre(2, 22))
            ouvrePorte(238, 2, 1);
        if (scene->getCoffre(2, 23))
            ouvrePorte(229, 43, 0);
        if (scene->getCoffre(2, 24))
            ouvrePorte(238, 10, 1);
        if (scene->getCoffre(2, 25))
            ouvrePorte(238, 92, 1);
        if (scene->getCoffre(2, 26))
            ouvrePorte(269, 43, 0);
        if (scene->getCoffre(2, 27))
            ouvrePorte(278, 6, 1);
        if (scene->getCoffre(2, 28))
            ouvrePorte(289, 28, 0);
        if (scene->getCoffre(2, 29))
            ouvrePorte(278, 36, 1);
        if (scene->getCoffre(2, 30))
            ouvrePorte(158, 81, 1);
        if (scene->getCoffre(2, 31))
            ouvrePorte(258, 66, 1);
        if (scene->getCoffre(2, 32))
            ouvrePorte(269, 73, 0);

        addObject(new Interrupteur(5 * 16, 3 * 16, 0, scene->getCoffre(2, 14), map));
        addObject(new Interrupteur(44 * 16, 49 * 16, 0, scene->getCoffre(2, 15), map, false));
        addObject(new Interrupteur(91 * 16, 21 * 16, 0, scene->getCoffre(2, 16), map, false));
        addObject(new Interrupteur(163 * 16, 18 * 16, 0, scene->getCoffre(2, 17), map));
        addObject(new Interrupteur(196 * 16, 18 * 16, 0, scene->getCoffre(2, 18), map));
        addObject(new Interrupteur(185 * 16, 62 * 16, 0, scene->getCoffre(2, 19), map));
        addObject(new Interrupteur(196 * 16, 69 * 16, 0, scene->getCoffre(2, 20), map));
        addObject(new Interrupteur(207 * 16, 25 * 16, 0, scene->getCoffre(2, 21), map));
        addObject(new Interrupteur(223 * 16, 3 * 16, 0, scene->getCoffre(2, 22), map));
        addObject(new Interrupteur(236 * 16, 52 * 16, 0, scene->getCoffre(2, 23), map));
        addObject(new Interrupteur(256 * 16, 11 * 16, 0, scene->getCoffre(2, 24), map));
        addObject(new Interrupteur(256 * 16, 93 * 16, 0, scene->getCoffre(2, 25), map));
        addObject(new Interrupteur(269 * 16, 38 * 16, 0, scene->getCoffre(2, 26), map));
        addObject(new Interrupteur(287 * 16, 11 * 16, 0, scene->getCoffre(2, 27), map));
        addObject(new Interrupteur(292 * 16, 18 * 16, 0, scene->getCoffre(2, 28), map));
        addObject(new Interrupteur(296 * 16, 33 * 16, 0, scene->getCoffre(2, 29), map));

        addObject(new Caisse(82 * 16, 4 * 16, 0));
        addObject(new Caisse(82 * 16, 5 * 16, 0));
        addObject(new Caisse(82 * 16, 9 * 16, 0));
        addObject(new Caisse(82 * 16, 10 * 16, 0));
        addObject(new Caisse(83 * 16, 5 * 16, 0));
        addObject(new Caisse(83 * 16, 6 * 16, 0));
        addObject(new Caisse(83 * 16, 7 * 16, 0));
        addObject(new Caisse(83 * 16, 8 * 16, 0));
        addObject(new Caisse(83 * 16, 9 * 16, 0));

        addEnnemi(new Ennemi003(49 * 16 + 2, 50 * 16 - 1));
        addEnnemi(new Ennemi003(149 * 16 + 2, 82 * 16 - 1));
        addEnnemi(new Ennemi003(70 * 16 + 2, 56 * 16 - 1));
        addEnnemi(new Ennemi003(92 * 16 + 2, 57 * 16 - 1));
        addEnnemi(new Ennemi003(85 * 16 + 2, 37 * 16 - 1));
        addEnnemi(new Ennemi003(89 * 16 + 2, 36 * 16 - 1));
        addEnnemi(new Ennemi003(93 * 16 + 2, 37 * 16 - 1));
        addEnnemi(new Ennemi003(109 * 16 + 2, 45 * 16 - 1));
        addEnnemi(new Ennemi003(149 * 16 + 2, 41 * 16 - 1));
        addEnnemi(new Ennemi003(289 * 16 + 2, 5 * 16 - 1));
        addEnnemi(new Ennemi003(292 * 16 + 2, 22 * 16 - 1));
        addEnnemi(new Ennemi003(291 * 16 + 2, 52 * 16 - 1));
        addEnnemi(new Ennemi003(225 * 16 + 2, 69 * 16 - 1));
        addEnnemi(new Ennemi003(225 * 16 + 2, 75 * 16 - 1));
        addEnnemi(new Ennemi003(225 * 16 + 2, 81 * 16 - 1));
        addEnnemi(new Ennemi003(233 * 16 + 2, 69 * 16 - 1));
        addEnnemi(new Ennemi003(233 * 16 + 2, 75 * 16 - 1));
        addEnnemi(new Ennemi003(233 * 16 + 2, 81 * 16 - 1));
        addEnnemi(new Ennemi003(287 * 16 + 2, 70 * 16 - 1));
        addEnnemi(new Ennemi003(291 * 16 + 2, 70 * 16 - 1));
        addEnnemi(new Ennemi003(206 * 16 + 2, 49 * 16 - 1));
        addEnnemi(new Ennemi003(259 * 16 + 2, 33 * 16 - 1));
        addEnnemi(new Ennemi003(261 * 16 + 2, 41 * 16 - 1));
        addEnnemi(new Ennemi003(229 * 16 + 2, 52 * 16 - 1));

        addEnnemi(new Ennemi008(129 * 16 + 8, 21 * 16 + 8));
        addEnnemi(new Ennemi008(289 * 16 + 8, 66 * 16 + 8));
        addEnnemi(new Ennemi008(149 * 16 + 8, 21 * 16 + 8));
        addEnnemi(new Ennemi008(169 * 16 + 8, 66 * 16 + 8));
        addEnnemi(new Ennemi008(189 * 16 + 8, 36 * 16 + 8));
        addEnnemi(new Ennemi008(129 * 16 + 8, 81 * 16 + 8));
        addEnnemi(new Ennemi008(269 * 16 + 8, 6 * 16 + 8));
        addEnnemi(new Ennemi008(229 * 16 + 8, 96 * 16 + 8));
        addEnnemi(new Ennemi008(269 * 16 + 8, 96 * 16 + 8));
        addEnnemi(new Ennemi008(245 * 16, 49 * 16 + 8));
        addEnnemi(new Ennemi008(254 * 16, 49 * 16 + 8));
        addEnnemi(new Ennemi008(209 * 16 + 8, 20 * 16 + 8));
        addEnnemi(new Ennemi008(209 * 16 + 8, 2 * 16 + 8));

        addEnnemi(new Ennemi018(68 * 16 + 8, 53 * 16 + 2));
        addEnnemi(new Ennemi018(77 * 16, 53 * 16 + 2));
        addEnnemi(new Ennemi018(85 * 16 + 8, 53 * 16 + 2));
        addEnnemi(new Ennemi018(96 * 16 + 8, 47 * 16 + 2));
        addEnnemi(new Ennemi018(90 * 16, 7 * 16 + 2));
        addEnnemi(new Ennemi018(53 * 16, 3 * 16 + 2));
        addEnnemi(new Ennemi018(59 * 16 + 8, 3 * 16 + 2));
        addEnnemi(new Ennemi018(66 * 16, 3 * 16 + 2));
        addEnnemi(new Ennemi018(53 * 16, 11 * 16 + 2));
        addEnnemi(new Ennemi018(59 * 16 + 8, 11 * 16 + 2));
        addEnnemi(new Ennemi018(66 * 16, 11 * 16 + 2));
        addEnnemi(new Ennemi018(128 * 16, 40 * 16 + 2));
        addEnnemi(new Ennemi018(136 * 16, 38 * 16 + 2));
        addEnnemi(new Ennemi018(143 * 16, 45 * 16 + 2));
        addEnnemi(new Ennemi018(146 * 16, 37 * 16 + 2));
        addEnnemi(new Ennemi018(154 * 16, 40 * 16 + 2));
        addEnnemi(new Ennemi018(154 * 16, 54 * 16 + 2));
        addEnnemi(new Ennemi018(162 * 16, 51 * 16 + 2));
        addEnnemi(new Ennemi018(169 * 16, 33 * 16 + 2));
        addEnnemi(new Ennemi018(173 * 16, 47 * 16 + 2));
        addEnnemi(new Ennemi018(128 * 16, 48 * 16 + 2));
        addEnnemi(new Ennemi018(206 * 16, 40 * 16 + 2));
        addEnnemi(new Ennemi018(216 * 16, 50 * 16 + 2));
        addEnnemi(new Ennemi018(209 * 16, 7 * 16 + 2));
        addEnnemi(new Ennemi018(249 * 16 + 8, 97 * 16 + 2));
        addEnnemi(new Ennemi018(269 * 16 + 8, 56 * 16 + 2));
        addEnnemi(new Ennemi018(227 * 16, 7 * 16 + 2));
        addEnnemi(new Ennemi018(223 * 16, 23 * 16 + 2));
        addEnnemi(new Ennemi018(230 * 16, 34 * 16 + 2));
        addEnnemi(new Ennemi018(240 * 16, 27 * 16 + 2));
        addEnnemi(new Ennemi018(241 * 16, 20 * 16 + 2));
        addEnnemi(new Ennemi018(243 * 16, 37 * 16 + 2));
        addEnnemi(new Ennemi018(247 * 16, 30 * 16 + 2));
        addEnnemi(new Ennemi018(255 * 16, 27 * 16 + 2));
        addEnnemi(new Ennemi018(264 * 16, 19 * 16 + 2));
        addEnnemi(new Ennemi018(264 * 16, 29 * 16 + 2));
        addEnnemi(new Ennemi018(265 * 16, 37 * 16 + 2));
        addEnnemi(new Ennemi018(273 * 16, 26 * 16 + 2));
        addEnnemi(new Ennemi018(273 * 16, 40 * 16 + 2));
        addEnnemi(new Ennemi018(249 * 16, 7 * 16 + 2));
        addEnnemi(new Ennemi018(286 * 16, 38 * 16 + 2));
        addEnnemi(new Ennemi018(295 * 16, 37 * 16 + 2));

        addObject(new Jarre(24 * 16, 2 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(25 * 16, 2 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(24 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(25 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 2 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(31 * 16, 2 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(36 * 16, 2 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(37 * 16, 2 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(36 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(37 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(44 * 16, 49 * 16, 0, TI_INTERRUPTEUR, map));
        addObject(new Jarre(55 * 16, 49 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(44 * 16, 55 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(55 * 16, 55 * 16, 0, TI_PETIT_COEUR, map));

        addObject(new Jarre(87 * 16, 20 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(88 * 16, 20 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(89 * 16, 20 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(90 * 16, 20 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(91 * 16, 20 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(92 * 16, 20 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(87 * 16, 21 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(88 * 16, 21 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(89 * 16, 21 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(90 * 16, 21 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(91 * 16, 21 * 16, 0, TI_INTERRUPTEUR, map));
        addObject(new Jarre(92 * 16, 21 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(87 * 16, 22 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(88 * 16, 22 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(89 * 16, 22 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(90 * 16, 22 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(91 * 16, 22 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(92 * 16, 22 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(87 * 16, 23 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(88 * 16, 23 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(89 * 16, 23 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(90 * 16, 23 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(91 * 16, 23 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(92 * 16, 23 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(87 * 16, 24 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(88 * 16, 24 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(89 * 16, 24 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(90 * 16, 24 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(91 * 16, 24 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(92 * 16, 24 * 16, 0, TI_NO_ITEM, map));

        addObject(new Jarre(145 * 16, 19 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(145 * 16, 25 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(148 * 16, 54 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(149 * 16, 54 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(150 * 16, 54 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(148 * 16, 55 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(149 * 16, 55 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(150 * 16, 55 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(157 * 16, 19 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(157 * 16, 25 * 16, 0, TI_NO_ITEM, map));

        addObject(new Jarre(164 * 16, 62 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(164 * 16, 72 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(175 * 16, 62 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(175 * 16, 72 * 16, 0, TI_NO_ITEM, map));

        addObject(new Jarre(184 * 16, 32 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(184 * 16, 42 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(195 * 16, 32 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(195 * 16, 42 * 16, 0, TI_PETIT_COEUR, map));

        addObject(new Jarre(207 * 16, 64 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(207 * 16, 69 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(212 * 16, 64 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(212 * 16, 69 * 16, 0, TI_NO_ITEM, map));

        addObject(new Jarre(224 * 16, 92 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(224 * 16, 102 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(275 * 16, 92 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(275 * 16, 102 * 16, 0, TI_RUBIS_VERT, map));

        addObject(new Jarre(237 * 16, 40 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(238 * 16, 40 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(237 * 16, 41 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(238 * 16, 41 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(237 * 16, 42 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(238 * 16, 42 * 16, 0, TI_NO_ITEM, map));

        addObject(new Jarre(244 * 16, 47 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(255 * 16, 47 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(244 * 16, 57 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(255 * 16, 57 * 16, 0, TI_PETIT_COEUR, map));

        addObject(new Jarre(244 * 16, 77 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(255 * 16, 77 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(244 * 16, 87 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(255 * 16, 87 * 16, 0, TI_PETIT_COEUR, map));
        break;
    case 17:
        if (!inventory->hasCoeur(2))
        {
            addEnnemi(new Ennemi062(9 * 16 + 4, 34 * 16 - 8, true));
        }
        if (!inventory->hasGraal(1))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GRAAL, 10 * 16, 21 * 16 + 8, 1));
        }

        addObject(new Coffre(229 * 16 + 8, 112 * 16, 0, scene->getCoffre(3, 0), TI_CARTE_DONJON));
        addObject(new Coffre(229 * 16 + 8, 97 * 16, 0, scene->getCoffre(3, 1), TI_BOUSSOLE));
        addObject(new Coffre(54 * 16, 63 * 16, 0, scene->getCoffre(3, 2), TI_CLE_BOSS));
        if (scene->getCoffre(3, 2) == 2)
            ouvrePorte(9, 43, 0);

        addObject(new Coffre(69 * 16, 5 * 16 + 8, 1, inventory->hasObject(GANTS), TI_GANT));

        addObject(new Coffre(49 * 16 + 8, 52 * 16, 0, scene->getCoffre(3, 4), TI_CLE, 4));
        addObject(new Coffre(90 * 16, 52 * 16, 0, scene->getCoffre(3, 5), TI_CLE, 5));
        addObject(new Coffre(149 * 16 + 8, 97 * 16, 0, scene->getCoffre(3, 6), TI_CLE, 6));
        addObject(new Coffre(189 * 16 + 8, 52 * 16, 0, scene->getCoffre(3, 7), TI_CLE, 7));

        if (scene->getCoffre(3, 8))
            ouvrePorte(69, 13, 0);
        if (scene->getCoffre(3, 9))
            ouvrePorte(69, 43, 0);
        if (scene->getCoffre(3, 10))
            ouvrePorte(69, 73, 0);
        if (scene->getCoffre(3, 11))
            ouvrePorte(189, 28, 0);
        if (scene->getCoffre(3, 12))
            ouvrePorte(154, 73, 0);
        if (scene->getCoffre(3, 13))
            ouvrePorte(178, 21, 1);
        if (scene->getCoffre(3, 14))
            ouvrePorte(198, 81, 1);
        if (scene->getCoffre(3, 15))
            ouvrePorte(209, 73, 0);
        if (scene->getCoffre(3, 16))
            ouvrePorte(198, 111, 1);
        if (scene->getCoffre(3, 17))
            ouvrePorte(49, 43, 2);
        if (scene->getCoffre(3, 18))
            ouvrePorte(78, 51, 3);
        if (scene->getCoffre(3, 19))
            ouvrePorte(89, 73, 2);
        if (scene->getCoffre(3, 20))
            ouvrePorte(89, 66, 4);
        if (scene->getCoffre(3, 21))
            ouvrePorte(158, 111, 3);
        if (scene->getCoffre(3, 22))
            ouvrePorte(189, 43, 2);
        if (scene->getCoffre(3, 23))
            ouvrePorte(229, 103, 2);

        addObject(new Interrupteur(146 * 16, 66 * 16, 0, scene->getCoffre(3, 12), map));
        addObject(new Interrupteur(172 * 16, 27 * 16, 0, scene->getCoffre(3, 13), map));
        addObject(new Interrupteur(196 * 16, 78 * 16, 0, scene->getCoffre(3, 14), map));
        addObject(new Interrupteur(207 * 16, 71 * 16, 0, scene->getCoffre(3, 15), map));
        addObject(new Interrupteur(203 * 16, 110 * 16, 0, scene->getCoffre(3, 16), map));

        addObject(new Caisse(207 * 16, 20 * 16, 1));
        addObject(new Caisse(233 * 16, 21 * 16, 1));
        addObject(new Caisse(233 * 16, 39 * 16, 1));

        addEnnemi(new Ennemi001(5 * 16, 48 * 16 + 6));
        addEnnemi(new Ennemi001(14 * 16, 48 * 16 + 6));
        addEnnemi(new Ennemi001(43 * 16, 86 * 16 + 6));
        addEnnemi(new Ennemi001(63 * 16, 79 * 16 + 6));
        addEnnemi(new Ennemi001(50 * 16, 25 * 16 + 6));
        addEnnemi(new Ennemi001(58 * 16, 38 * 16 + 6));
        addEnnemi(new Ennemi001(62 * 16, 31 * 16 + 6));
        addEnnemi(new Ennemi001(69 * 16 + 8, 22 * 16 + 6));
        addEnnemi(new Ennemi001(77 * 16, 31 * 16 + 6));
        addEnnemi(new Ennemi001(81 * 16, 38 * 16 + 6));
        addEnnemi(new Ennemi001(89 * 16, 25 * 16 + 6));
        addEnnemi(new Ennemi001(146 * 16, 110 * 16 + 6));
        addEnnemi(new Ennemi001(150 * 16, 114 * 16 + 6));
        addEnnemi(new Ennemi001(153 * 16, 66 * 16 + 6));
        addEnnemi(new Ennemi001(169 * 16 + 8, 77 * 16 + 6));
        addEnnemi(new Ennemi001(189 * 16 + 8, 36 * 16 + 6));
        addEnnemi(new Ennemi001(189 * 16 + 8, 85 * 16 + 6));
        addEnnemi(new Ennemi001(211 * 16, 22 * 16 + 6));
        addEnnemi(new Ennemi001(169 * 16, 30 * 16 + 6));

        addEnnemi(new Ennemi018(146 * 16, 31 * 16 + 2));
        addEnnemi(new Ennemi018(149 * 16, 19 * 16 + 2));
        addEnnemi(new Ennemi018(150 * 16, 39 * 16 + 2));
        addEnnemi(new Ennemi018(154 * 16, 25 * 16 + 2));
        addEnnemi(new Ennemi018(159 * 16, 29 * 16 + 2));
        addEnnemi(new Ennemi018(161 * 16, 34 * 16 + 2));
        addEnnemi(new Ennemi018(166 * 16, 23 * 16 + 2));
        addEnnemi(new Ennemi018(172 * 16, 41 * 16 + 2));
        addEnnemi(new Ennemi018(174 * 16, 18 * 16 + 2));

        addEnnemi(new Ennemi053(44 * 16, 19 * 16));
        addEnnemi(new Ennemi053(49 * 16, 35 * 16));
        addEnnemi(new Ennemi053(90 * 16, 35 * 16));
        addEnnemi(new Ennemi053(95 * 16, 19 * 16));
        addEnnemi(new Ennemi053(45 * 16, 63 * 16));
        addEnnemi(new Ennemi053(54 * 16, 98 * 16));
        addEnnemi(new Ennemi053(84 * 16, 101 * 16));
        addEnnemi(new Ennemi053(85 * 16, 108 * 16));
        addEnnemi(new Ennemi053(94 * 16, 108 * 16));
        addEnnemi(new Ennemi053(154 * 16, 109 * 16));
        addEnnemi(new Ennemi053(169 * 16, 86 * 16));
        addEnnemi(new Ennemi053(217 * 16, 19 * 16));
        addEnnemi(new Ennemi053(217 * 16, 26 * 16));
        addEnnemi(new Ennemi053(233 * 16, 109 * 16));
        addEnnemi(new Ennemi053(233 * 16, 115 * 16));

        addObject(new PiegePics(54 * 16, 94 * 16, S));
        addObject(new PiegePics(55 * 16, 93 * 16, S));
        addObject(new PiegePics(56 * 16, 92 * 16, S));
        addObject(new PiegePics(57 * 16, 91 * 16, S));
        addObject(new PiegePics(58 * 16, 91 * 16, S));
        addObject(new PiegePics(63 * 16, 97 * 16, S));
        addObject(new PiegePics(66 * 16, 97 * 16, S));
        addObject(new PiegePics(69 * 16, 97 * 16, S));
        addObject(new PiegePics(72 * 16, 97 * 16, S));
        addObject(new PiegePics(77 * 16, 91 * 16, S));
        addObject(new PiegePics(78 * 16, 94 * 16, S));
        addObject(new PiegePics(79 * 16, 93 * 16, S));
        addObject(new PiegePics(80 * 16, 92 * 16, S));
        addObject(new PiegePics(81 * 16, 91 * 16, S));
        addObject(new PiegePics(84 * 16, 94 * 16, S));
        addObject(new PiegePics(85 * 16, 93 * 16, S));
        addObject(new PiegePics(86 * 16, 92 * 16, S));
        addObject(new PiegePics(87 * 16, 91 * 16, S));

        addObject(new PiegeLong(126 * 16, 32 * 16, S));
        addObject(new PiegeLong(126 * 16, 52 * 16, S));
        addObject(new PiegeLong(126 * 16, 72 * 16, S));
        addObject(new PiegeLong(205 * 16, 36 * 16, S));
        addObject(new PiegeLong(213 * 16, 36 * 16, S));
        addObject(new PiegeLong(221 * 16, 36 * 16, S));
        addObject(new PiegeLong(226 * 16, 62 * 16, S));
        addObject(new PiegeLong(246 * 16, 32 * 16, S));

        addObject(new Jarre(4 * 16, 32 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(4 * 16, 42 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(4 * 16, 47 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(15 * 16, 32 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(15 * 16, 42 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(15 * 16, 47 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(44 * 16, 115 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(52 * 16, 39 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(55 * 16, 115 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 24 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(64 * 16, 89 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(64 * 16, 94 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(71 * 16, 89 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(71 * 16, 94 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(75 * 16, 24 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(84 * 16, 115 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(87 * 16, 39 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(95 * 16, 115 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(125 * 16, 50 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(125 * 16, 51 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(134 * 16, 45 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(134 * 16, 46 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(134 * 16, 56 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(134 * 16, 57 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(142 * 16, 72 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(147 * 16, 72 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(182 * 16, 109 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(182 * 16, 115 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(197 * 16, 109 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(197 * 16, 115 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(204 * 16, 64 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(215 * 16, 64 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(184 * 16, 32 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(184 * 16, 42 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(195 * 16, 32 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(195 * 16, 42 * 16, 1, TI_BOMBE, map));
        break;
    case 18:
        if (!inventory->hasCoeur(3))
        {
            addEnnemi(new Ennemi063(269 * 16 - 13, 17 * 16 - 4));
        }
        if (scene->getAvancement() < AV_FILLE_MAIRE_SAUVEE)
        {
            addObject(new Pnj(16 * 270, 16 * 2, 45, 332));
        }

        if (!inventory->hasObject(ARC))
        {
            addObject(new Pnj(16 * 150, 16 * 46, 44, 329));
        }
        else
        {
            addEnnemi(new Ennemi064(150 * 16 - 4, 47 * 16 - 4));
        }

        addObject(new Coffre(149 * 16 + 8, 37 * 16, 0, scene->getCoffre(4, 0), TI_CARTE_DONJON));
        addObject(new Coffre(116 * 16, 18 * 16, 0, scene->getCoffre(4, 1), TI_BOUSSOLE));
        addObject(new Coffre(269 * 16 + 8, 67 * 16, 0, scene->getCoffre(4, 2), TI_CLE_BOSS));
        if (scene->getCoffre(4, 2) == 2)
            ouvrePorte(269, 28, 0);

        addObject(new Coffre(106 * 16, 33 * 16, 0, scene->getCoffre(4, 4), TI_CLE, 4));
        addObject(new Coffre(129 * 16 + 8, 67 * 16, 0, scene->getCoffre(4, 5), TI_CLE, 5));
        addObject(new Coffre(169 * 16 + 8, 21 * 16, 0, scene->getCoffre(4, 6), TI_CLE, 6));
        addObject(new Coffre(209 * 16 + 8, 67 * 16, 0, scene->getCoffre(4, 7), TI_CLE, 7));
        addObject(new Coffre(229 * 16 + 8, 37 * 16, 0, scene->getCoffre(4, 8), TI_CLE, 8));
        addObject(new Coffre(229 * 16 + 8, 51 * 16 + 8, 0, scene->getCoffre(4, 9), TI_CLE, 9));
        addObject(new Coffre(292 * 16, 25 * 16, 0, scene->getCoffre(4, 10), TI_CLE, 10));
        addObject(new Coffre(292 * 16, 56 * 16, 0, scene->getCoffre(4, 11), TI_CLE, 11));

        if (scene->getCoffre(4, 12))
            ouvrePorte(98, 21, 1);
        if (scene->getCoffre(4, 13))
            ouvrePorte(98, 51, 1);
        if (scene->getCoffre(4, 14))
            ouvrePorte(138, 51, 1);
        if (scene->getCoffre(4, 15))
            ouvrePorte(149, 28, 0);
        if (scene->getCoffre(4, 16))
            ouvrePorte(278, 36, 1);
        if (scene->getCoffre(4, 17))
            ouvrePorte(278, 66, 1);
        if (scene->getCoffre(4, 18))
            ouvrePorte(289, 43, 0);
        if (scene->getCoffre(4, 19))
            ouvrePorte(309, 43, 0);
        if (scene->getCoffre(4, 20))
            ouvrePorte(149, 58, 0);
        if (scene->getCoffre(4, 21))
            ouvrePorte(158, 21, 1);
        if (scene->getCoffre(4, 22))
            ouvrePorte(169, 58, 0);
        if (scene->getCoffre(4, 23))
            ouvrePorte(189, 58, 0);
        if (scene->getCoffre(4, 24))
            ouvrePorte(198, 66, 1);
        if (scene->getCoffre(4, 25))
            ouvrePorte(238, 36, 1);
        if (scene->getCoffre(4, 26))
            ouvrePorte(238, 51, 1);
        if (scene->getCoffre(4, 27))
            ouvrePorte(258, 51, 1);
        if (scene->getCoffre(4, 28))
            ouvrePorte(270, 7, 5);
        if (scene->getCoffre(4, 29))
            ouvrePorte(278, 51, 1);
        if (scene->getCoffre(4, 30))
            ouvrePorte(289, 28, 0);
        if (scene->getCoffre(4, 31))
            ouvrePorte(309, 58, 0);
        if (scene->getCoffre(4, 32))
            ouvrePorte(69, 21, 4);
        if (scene->getCoffre(4, 33))
            ouvrePorte(249, 43, 2);
        if (scene->getCoffre(4, 34))
            ouvrePorte(289, 58, 2);

        if (scene->getCoffre(4, 35))
        {
            ouvrePorte(189, 28, 0);
            map->setSol(185 * 16, 17 * 16, 1812);
            map->setSol(189 * 16, 7 * 16, 1812);
            map->setSol(193 * 16, 17 * 16, 1812);
            map->setSol(196 * 16, 25 * 16, 1812);
            map->setSol(200 * 16, 16 * 16, 1812);
            map->setSol(203 * 16, 4 * 16, 1812);
            map->setSol(208 * 16, 16 * 16, 1812);
            map->setSol(212 * 16, 23 * 16, 1812);
            map->setSol(213 * 16, 11 * 16, 1812);
        }
        if (scene->getCoffre(4, 36))
        {
            ouvrePorte(229, 28, 0);
            map->setSol(226 * 16, 13 * 16, 1812);
            map->setSol(239 * 16, 5 * 16, 1812);
            map->setSol(239 * 16, 21 * 16, 1812);
            map->setSol(253 * 16, 13 * 16, 1812);
        }

        addObject(new Interrupteur(143 * 16, 56 * 16, 0, scene->getCoffre(4, 20), map));
        addObject(new Interrupteur(155 * 16, 15 * 16, 0, scene->getCoffre(4, 21), map));
        addObject(new Interrupteur(174 * 16, 56 * 16, 0, scene->getCoffre(4, 22), map));
        addObject(new Interrupteur(197 * 16, 62 * 16, 0, scene->getCoffre(4, 23), map));
        addObject(new Interrupteur(203 * 16, 71 * 16, 0, scene->getCoffre(4, 24), map));
        addObject(new Interrupteur(234 * 16, 41 * 16, 0, scene->getCoffre(4, 25), map));
        addObject(new Interrupteur(234 * 16, 48 * 16, 0, scene->getCoffre(4, 26), map));
        addObject(new Interrupteur(247 * 16, 48 * 16, 0, scene->getCoffre(4, 27), map));
        addObject(new Interrupteur(265 * 16, 11 * 16, 0, scene->getCoffre(4, 28), map));
        addObject(new Interrupteur(287 * 16, 48 * 16, 0, scene->getCoffre(4, 29), map));
        addObject(new Interrupteur(287 * 16, 25 * 16, 0, scene->getCoffre(4, 30), map));
        addObject(new Interrupteur(307 * 16, 48 * 16, 0, scene->getCoffre(4, 31), map));

        addObject(new PiegeMain(2 * 16, 17 * 16));
        addObject(new PiegeMain(102 * 16, 47 * 16));
        addObject(new PiegeMain(122 * 16, 2 * 16));
        addObject(new PiegeMain(262 * 16, 62 * 16));
        addObject(new PiegeMain(282 * 16, 2 * 16));
        addObject(new PiegeMain(222 * 16, 32 * 16));
        addObject(new PiegeMain(222 * 16, 47 * 16));
        addObject(new PiegeMain(62 * 16, 47 * 16));
        addObject(new PiegeMain(62 * 16, 32 * 16));
        addObject(new PiegeMain(62 * 16, 17 * 16));
        addObject(new PiegeMain(102 * 16, 32 * 16));
        addObject(new PiegeMain(82 * 16, 17 * 16));
        addObject(new PiegeMain(102 * 16, 17 * 16));
        addObject(new PiegeMain(142 * 16, 32 * 16));
        addObject(new PiegeMain(182 * 16, 47 * 16));
        addObject(new PiegeMain(122 * 16, 32 * 16));
        addObject(new PiegeMain(122 * 16, 62 * 16));

        addObject(new PiegeFeu(239 * 16, 13 * 16));

        addObject(new PiegeLong(288 * 16, 72 * 16, S));
        addObject(new PiegeLong(296 * 16, 62 * 16, S));
        addObject(new PiegeLong(304 * 16, 72 * 16, S));
        addObject(new PiegeLong(236 * 16, 65 * 16, S));

        addEnnemi(new Ennemi012(7 * 16, 50 * 16));
        addEnnemi(new Ennemi012(9 * 16, 37 * 16));
        addEnnemi(new Ennemi012(13 * 16, 24 * 16));
        addEnnemi(new Ennemi012(19 * 16, 54 * 16));
        addEnnemi(new Ennemi012(30 * 16, 29 * 16));
        addEnnemi(new Ennemi012(39 * 16, 50 * 16));
        addEnnemi(new Ennemi012(50 * 16, 38 * 16));
        addEnnemi(new Ennemi012(51 * 16, 20 * 16));
        addEnnemi(new Ennemi012(69 * 16 + 8, 18 * 16));
        addEnnemi(new Ennemi012(69 * 16 + 8, 37 * 16));
        addEnnemi(new Ennemi012(74 * 16, 52 * 16));
        addEnnemi(new Ennemi012(84 * 16, 52 * 16));
        addEnnemi(new Ennemi012(109 * 16, 34 * 16));
        addEnnemi(new Ennemi012(110 * 16, 18 * 16));
        addEnnemi(new Ennemi012(139 * 16, 3 * 16));
        addEnnemi(new Ennemi012(126 * 16, 44 * 16));
        addEnnemi(new Ennemi012(133 * 16, 44 * 16));
        addEnnemi(new Ennemi012(129 * 16 + 8, 71 * 16));
        addEnnemi(new Ennemi012(149 * 16 + 8, 38 * 16));
        addEnnemi(new Ennemi012(170 * 16, 24 * 16));
        addEnnemi(new Ennemi012(189 * 16, 18 * 16));
        addEnnemi(new Ennemi012(195 * 16, 4 * 16));
        addEnnemi(new Ennemi012(209 * 16, 11 * 16));
        addEnnemi(new Ennemi012(215 * 16, 3 * 16));
        addEnnemi(new Ennemi012(215 * 16, 26 * 16));
        addEnnemi(new Ennemi012(285 * 16, 18 * 16));
        addEnnemi(new Ennemi012(295 * 16, 10 * 16));
        addEnnemi(new Ennemi012(313 * 16, 14 * 16));

        addEnnemi(new Ennemi062(189 * 16 + 4, 39 * 16, false));

        addEnnemi(new Ennemi064(169 * 16 - 4, 6 * 16 - 4));
        addEnnemi(new Ennemi064(206 * 16 - 4, 45 * 16 - 4));
        addEnnemi(new Ennemi064(212 * 16 - 4, 45 * 16 - 4));
        addEnnemi(new Ennemi064(209 * 16 - 4, 47 * 16 - 4));
        addEnnemi(new Ennemi064(249 * 16 - 4, 36 * 16 - 4));
        addEnnemi(new Ennemi064(269 * 16 - 4, 37 * 16 - 4));
        addEnnemi(new Ennemi064(249 * 16 - 4, 51 * 16 - 4));
        addEnnemi(new Ennemi064(299 * 16 - 4, 36 * 16 - 4));
        addEnnemi(new Ennemi064(299 * 16 - 4, 51 * 16 - 4));

        addObject(new Jarre(162 * 16, 2 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(162 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(164 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(175 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(177 * 16, 2 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(177 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(184 * 16, 32 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(184 * 16, 42 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(184 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(184 * 16, 57 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(195 * 16, 32 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(195 * 16, 42 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(195 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(195 * 16, 57 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(203 * 16, 11 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(203 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(204 * 16, 11 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(204 * 16, 12 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(205 * 16, 11 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(205 * 16, 12 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(242 * 16, 32 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(242 * 16, 42 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(257 * 16, 32 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(257 * 16, 42 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(315 * 16, 49 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(315 * 16, 55 * 16, 0, TI_NO_ITEM, map));
        break;
    case 19:
        if (!inventory->hasCoeur(4))
        {
            addEnnemi(new Ennemi045(78 * 16 - 1, 27 * 16));
        }
        if (!inventory->hasGraal(2))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GRAAL, 90 * 16, 6 * 16 + 8, 2));
        }

        addObject(new Coffre(45 * 16, 33 * 16, 0, scene->getCoffre(5, 0), TI_CARTE_DONJON));
        addObject(new Coffre(9 * 16 + 8, 65 * 16, 0, scene->getCoffre(5, 1), TI_BOUSSOLE));
        addObject(new Coffre(196 * 16, 52 * 16, 0, scene->getCoffre(5, 2), TI_CLE_BOSS));
        if (scene->getCoffre(5, 2) == 2)
            ouvrePorte(89, 43, 0);

        addObject(new Coffre(168 * 16 + 8, 16 * 16 + 8, 1, inventory->hasObject(MARTEAU), TI_MARTEAU));

        addObject(new Coffre(9 * 16 + 8, 52 * 16, 0, scene->getCoffre(5, 4), TI_CLE, 4));
        addObject(new Coffre(112 * 16, 67 * 16, 0, scene->getCoffre(5, 5), TI_CLE, 5));
        addObject(new Coffre(146 * 16, 66 * 16, 0, scene->getCoffre(5, 6), TI_CLE, 6));
        addObject(new Coffre(169 * 16, 23 * 16, 0, scene->getCoffre(5, 7), TI_CLE, 7));
        addObject(new Coffre(188 * 16, 67 * 16, 0, scene->getCoffre(5, 8), TI_CLE, 8));

        if (scene->getCoffre(5, 9))
            ouvrePorte(49, 43, 0);
        if (scene->getCoffre(5, 10))
            ouvrePorte(49, 58, 0);
        if (scene->getCoffre(5, 11))
            ouvrePorte(149, 28, 0);
        if (scene->getCoffre(5, 12))
            ouvrePorte(158, 6, 1);
        if (scene->getCoffre(5, 13))
            ouvrePorte(158, 66, 1);
        if (scene->getCoffre(5, 14))
            ouvrePorte(9, 43, 0);
        if (scene->getCoffre(5, 15))
            ouvrePorte(78, 51, 1);
        if (scene->getCoffre(5, 16))
            ouvrePorte(129, 58, 0);
        if (scene->getCoffre(5, 17))
            ouvrePorte(129, 28, 0);
        if (scene->getCoffre(5, 18))
            ouvrePorte(149, 13, 0);
        if (scene->getCoffre(5, 19))
            ouvrePorte(138, 66, 1);
        if (scene->getCoffre(5, 20))
            ouvrePorte(178, 36, 1);
        if (scene->getCoffre(5, 21))
            ouvrePorte(158, 21, 3);

        if (scene->getCoffre(5, 22))
        {
            ouvrePorte(38, 51, 1);
            map->setSol(43 * 16, 49 * 16, 1812);
            map->setSol(43 * 16, 55 * 16, 1812);
        }
        if (scene->getCoffre(5, 23))
        {
            ouvrePorte(58, 51, 1);
            map->setSol(56 * 16, 49 * 16, 1812);
            map->setSol(56 * 16, 55 * 16, 1812);
        }
        if (scene->getCoffre(5, 24))
        {
            ouvrePorte(178, 51, 1);
            map->setSol(165 * 16, 35 * 16, 1812);
            map->setSol(165 * 16, 39 * 16, 1812);
            map->setSol(165 * 16, 50 * 16, 1812);
            map->setSol(165 * 16, 54 * 16, 1812);
            map->setSol(174 * 16, 35 * 16, 1812);
            map->setSol(174 * 16, 39 * 16, 1812);
            map->setSol(174 * 16, 50 * 16, 1812);
            map->setSol(174 * 16, 54 * 16, 1812);
        }

        addObject(new Interrupteur(7 * 16, 41 * 16, 0, scene->getCoffre(5, 14), map));
        addObject(new Interrupteur(74 * 16, 47 * 16, 0, scene->getCoffre(5, 15), map, false));
        addObject(new Interrupteur(116 * 16, 67 * 16, 0, scene->getCoffre(5, 16), map));
        addObject(new Interrupteur(136 * 16, 22 * 16, 0, scene->getCoffre(5, 17), map));
        addObject(new Interrupteur(143 * 16, 7 * 16, 0, scene->getCoffre(5, 18), map));
        addObject(new Interrupteur(156 * 16, 67 * 16, 0, scene->getCoffre(5, 19), map));
        addObject(new Interrupteur(194 * 16, 38 * 16, 0, scene->getCoffre(5, 20), map));

        addObject(new Caisse(25 * 16, 33 * 16, 4));
        addObject(new Caisse(25 * 16, 34 * 16, 4));
        addObject(new Caisse(27 * 16, 52 * 16, 4));
        addObject(new Caisse(28 * 16, 52 * 16, 4));
        addObject(new Caisse(113 * 16, 67 * 16, 4));
        addObject(new Caisse(191 * 16, 67 * 16, 4));
        addObject(new Caisse(192 * 16, 67 * 16, 4));
        addObject(new Caisse(29 * 16, 28 * 16, 4));
        addObject(new Caisse(30 * 16, 28 * 16, 4));

        addObject(new Sphere(23 * 16, 11 * 16));
        addObject(new Sphere(23 * 16, 20 * 16));
        addObject(new Sphere(36 * 16, 28 * 16));
        addObject(new Sphere(54 * 16, 33 * 16));
        addObject(new Sphere(76 * 16, 7 * 16));
        addObject(new Sphere(80 * 16, 69 * 16));
        addObject(new Sphere(109 * 16, 17 * 16));
        addObject(new Sphere(149 * 16, 7 * 16));
        addObject(new Sphere(156 * 16, 22 * 16));
        addObject(new Sphere(169 * 16, 72 * 16));
        addObject(new Sphere(174 * 16 + 8, 43 * 16 + 8));
        addObject(new Sphere(176 * 16, 27 * 16));

        addObject(new PiegePics(71 * 16, 5 * 16 + 8, S));
        addObject(new PiegePics(72 * 16, 8 * 16 + 8, S));
        addObject(new PiegePics(73 * 16, 5 * 16 + 8, S));
        addObject(new PiegePics(74 * 16, 8 * 16 + 8, S));

        addObject(new PiegeLong(11 * 16, 8 * 16 + 8, S));
        addObject(new PiegeLong(19 * 16, 8 * 16 + 8, S));
        addObject(new PiegeLong(27 * 16, 8 * 16 + 8, S));
        addObject(new PiegeLong(16 * 16, 65 * 16 + 8, S));
        addObject(new PiegeLong(24 * 16, 65 * 16 + 8, S));
        addObject(new PiegeLong(186 * 16, 46 * 16 + 8, S));
        addObject(new PiegeLong(186 * 16, 57 * 16 + 8, S));

        addObject(new PiegeFeu(44 * 16, 17 * 16));
        addObject(new PiegeFeu(55 * 16, 17 * 16));
        addObject(new PiegeFeu(62 * 16, 57 * 16));
        addObject(new PiegeFeu(77 * 16, 57 * 16));
        addObject(new PiegeFeu(102 * 16, 2 * 16));
        addObject(new PiegeFeu(117 * 16, 2 * 16));
        addObject(new PiegeFeu(102 * 16, 27 * 16));
        addObject(new PiegeFeu(117 * 16, 27 * 16));
        addObject(new PiegeFeu(102 * 16, 32 * 16));
        addObject(new PiegeFeu(137 * 16, 32 * 16));
        addObject(new PiegeFeu(102 * 16, 57 * 16));
        addObject(new PiegeFeu(137 * 16, 57 * 16));
        addObject(new PiegeFeu(162 * 16, 2 * 16));
        addObject(new PiegeFeu(197 * 16, 2 * 16));
        addObject(new PiegeFeu(162 * 16, 12 * 16));
        addObject(new PiegeFeu(197 * 16, 12 * 16));
        addObject(new PiegeFeu(182 * 16, 17 * 16));
        addObject(new PiegeFeu(197 * 16, 17 * 16));
        addObject(new PiegeFeu(182 * 16, 42 * 16));
        addObject(new PiegeFeu(197 * 16, 42 * 16));

        addEnnemi(new Ennemi005(49 * 16 + 8, 52 * 16 - 10));
        addEnnemi(new Ennemi005(49 * 16 + 8, 3 * 16 - 10));
        addEnnemi(new Ennemi005(69 * 16 + 8, 7 * 16 - 10));
        addEnnemi(new Ennemi005(17 * 16 + 8, 20 * 16 - 10));
        addEnnemi(new Ennemi005(9 * 16 + 8, 28 * 16 - 10));
        addEnnemi(new Ennemi005(17 * 16 + 8, 52 * 16 - 10));
        addEnnemi(new Ennemi005(89 * 16 + 8, 52 * 16 - 10));
        addEnnemi(new Ennemi005(80 * 16 + 8, 67 * 16 - 10));
        addEnnemi(new Ennemi005(122 * 16 + 8, 67 * 16 - 10));
        addEnnemi(new Ennemi005(153 * 16 + 8, 48 * 16 - 10));
        addEnnemi(new Ennemi005(130 * 16 + 8, 7 * 16 - 10));
        addEnnemi(new Ennemi005(172 * 16 + 8, 7 * 16 - 10));
        addEnnemi(new Ennemi005(182 * 16 + 8, 7 * 16 - 10));

        addEnnemi(new Ennemi025(49 * 16 - 6 + 8, 21 * 16 - 14));
        addEnnemi(new Ennemi025(69 * 16 - 6 + 8, 49 * 16 - 14));
        addEnnemi(new Ennemi025(168 * 16 - 6 + 8, 36 * 16 - 14));
        addEnnemi(new Ennemi025(169 * 16 - 6 + 8, 49 * 16 - 14));
        addEnnemi(new Ennemi025(109 * 16 - 6 + 8, 47 * 16 - 14));
        addEnnemi(new Ennemi025(129 * 16 - 6 + 8, 42 * 16 - 14));
        addEnnemi(new Ennemi025(109 * 16 - 6 + 8, 9 * 16 - 14));

        addObject(new Jarre(5 * 16, 2 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(5 * 16, 8 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(35 * 16, 65 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(36 * 16, 65 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(37 * 16, 65 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(64 * 16, 2 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(65 * 16, 2 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(66 * 16, 2 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(67 * 16, 2 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(68 * 16, 2 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 12 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(65 * 16, 12 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(66 * 16, 12 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(67 * 16, 12 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(68 * 16, 12 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(62 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(63 * 16, 47 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(64 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(65 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(66 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(67 * 16, 47 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(68 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(69 * 16, 47 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(70 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(71 * 16, 47 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(72 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(73 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(74 * 16, 47 * 16, 1, TI_INTERRUPTEUR, map));
        addObject(new Jarre(75 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(76 * 16, 47 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(77 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(86 * 16, 47 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(87 * 16, 47 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(92 * 16, 47 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(93 * 16, 47 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(162 * 16, 21 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(162 * 16, 22 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(162 * 16, 23 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(162 * 16, 24 * 16, 1, TI_MAGIE_PEU, map));
        break;
    case 20:
        if (!inventory->hasCoeur(5))
        {
            addEnnemi(new Ennemi040(9 * 16 - 8 - 3, 33 * 16 - 10));
        }
        if (!inventory->hasObject(GRAPPIN))
        {
            addObject(new Coffre(9 * 16, 18 * 16 + 8, 1, inventory->hasObject(GRAPPIN), TI_GRAPPIN));
        }

        addObject(new Coffre(75 * 16, 17 * 16, 0, scene->getCoffre(6, 0), TI_CARTE_DONJON));
        addObject(new Coffre(91 * 16, 41 * 16, 0, scene->getCoffre(6, 1), TI_BOUSSOLE));
        addObject(new Coffre(96 * 16, 48 * 16, 0, scene->getCoffre(6, 2), TI_CLE_BOSS));
        if (scene->getCoffre(6, 2) == 2)
            ouvrePorte(9, 43, 0);

        if (!scene->getCoffre(6, 4))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_CLE, 14 * 16 + 8, 54 * 16 + 8, 4, false));
        }
        addObject(new Coffre(9 * 16 + 8, 81 * 16, 0, scene->getCoffre(6, 5), TI_CLE, 5));
        if (!scene->getCoffre(6, 6))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_CLE, 23 * 16 + 8, 3 * 16 + 8, 6, false));
        }

        if (scene->getCoffre(6, 7))
            ouvrePorte(98, 51, 1);
        if (scene->getCoffre(6, 8))
            ouvrePorte(98, 66, 1);
        if (scene->getCoffre(6, 9))
            ouvrePorte(78, 66, 1);
        if (scene->getCoffre(6, 11))
            ouvrePorte(78, 51, 1);
        if (scene->getCoffre(6, 18))
            ouvrePorte(84, 43, 0);
        if (scene->getCoffre(6, 19))
            ouvrePorte(78, 40, 1);
        if (scene->getCoffre(6, 20))
            ouvrePorte(78, 32, 1);
        if (scene->getCoffre(6, 21))
            ouvrePorte(84, 28, 0);
        if (scene->getCoffre(6, 22))
            ouvrePorte(78, 25, 1);
        if (scene->getCoffre(6, 23))
            ouvrePorte(78, 17, 1);
        if (scene->getCoffre(6, 24))
            ouvrePorte(84, 13, 0);
        if (scene->getCoffre(6, 25))
            ouvrePorte(94, 13, 0);
        if (scene->getCoffre(6, 26))
            ouvrePorte(98, 17, 1);
        if (scene->getCoffre(6, 27))
            ouvrePorte(98, 25, 1);
        if (scene->getCoffre(6, 28))
            ouvrePorte(94, 28, 0);
        if (scene->getCoffre(6, 29))
            ouvrePorte(98, 32, 1);
        if (scene->getCoffre(6, 30))
            ouvrePorte(98, 40, 1);
        if (scene->getCoffre(6, 31))
            ouvrePorte(94, 43, 0);
        if (scene->getCoffre(6, 32))
            ouvrePorte(58, 51, 1);
        if (scene->getCoffre(6, 33))
            ouvrePorte(58, 66, 1);
        if (scene->getCoffre(6, 34))
            ouvrePorte(118, 51, 1);
        if (scene->getCoffre(6, 35))
            ouvrePorte(118, 66, 1);

        addObject(new Pancarte(16 * 91, 16 * 77, 334, map));
        addObject(new Pancarte(16 * 82, 16 * 69, 335, map));
        addObject(new Pancarte(16 * 97, 16 * 69, 336, map));
        addObject(new Pancarte(16 * 82, 16 * 54, 337, map));
        addObject(new Pancarte(16 * 97, 16 * 54, 338, map));
        addObject(new Pancarte(16 * 86, 16 * 48, 339, map));
        addObject(new Pancarte(16 * 91, 16 * 53, 340, map));

        addObject(new Caisse(90 * 16, 18 * 16, 0));
        addObject(new Caisse(90 * 16, 26 * 16, 0));
        addObject(new Caisse(90 * 16, 33 * 16, 0));
        addObject(new Caisse(90 * 16, 41 * 16, 0));
        addObject(new Caisse(96 * 16, 49 * 16, 0));

        addObject(new PiegeMain(23 * 16, 48 * 16));
        addObject(new PiegeMain(2 * 16, 77 * 16));

        addObject(new PiegeColere(2 * 16, 32 * 16));
        addObject(new PiegeColere(17 * 16, 32 * 16));
        addObject(new PiegeColere(130 * 16, 17 * 16));
        addObject(new PiegeColere(132 * 16, 33 * 16));
        addObject(new PiegeColere(157 * 16, 21 * 16));
        addObject(new PiegeColere(157 * 16, 37 * 16));
        addObject(new PiegeColere(144 * 16, 12 * 16));
        addObject(new PiegeColere(155 * 16, 12 * 16));
        addObject(new PiegeColere(149 * 16, 57 * 16));
        addObject(new PiegeColere(150 * 16, 57 * 16));
        addObject(new PiegeColere(164 * 16, 4 * 16));
        addObject(new PiegeColere(195 * 16, 4 * 16));
        addObject(new PiegeColere(164 * 16, 25 * 16));
        addObject(new PiegeColere(195 * 16, 25 * 16));
        addObject(new PiegeColere(164 * 16, 64 * 16));
        addObject(new PiegeColere(195 * 16, 64 * 16));
        addObject(new PiegeColere(164 * 16, 85 * 16));
        addObject(new PiegeColere(195 * 16, 85 * 16));
        addObject(new PiegeColere(224 * 16, 4 * 16));
        addObject(new PiegeColere(255 * 16, 4 * 16));
        addObject(new PiegeColere(224 * 16, 25 * 16));
        addObject(new PiegeColere(255 * 16, 25 * 16));
        addObject(new PiegeColere(224 * 16, 64 * 16));
        addObject(new PiegeColere(255 * 16, 64 * 16));
        addObject(new PiegeColere(224 * 16, 85 * 16));
        addObject(new PiegeColere(255 * 16, 85 * 16));

        addEnnemi(new Ennemi001(89 * 16 + 8, 66 * 16 + 6));

        addEnnemi(new Ennemi002(110 * 16 - 3, 48 * 16 + 6));
        addEnnemi(new Ennemi002(231 * 16 - 3, 6 * 16 + 6));
        addEnnemi(new Ennemi002(231 * 16 - 3, 18 * 16 + 6));
        addEnnemi(new Ennemi002(248 * 16 - 3, 18 * 16 + 6));

        addEnnemi(new Ennemi025(69 * 16 - 6 + 8, 48 * 16 - 14));
        addEnnemi(new Ennemi025(171 * 16 - 6, 18 * 16 - 14));
        addEnnemi(new Ennemi025(188 * 16 - 6, 18 * 16 - 14));
        addEnnemi(new Ennemi025(188 * 16 - 6, 6 * 16 - 14));

        addEnnemi(new Ennemi037(69 * 16 + 8, 64 * 16 - 10));
        addEnnemi(new Ennemi037(171 * 16 + 8, 80 * 16 - 10));
        addEnnemi(new Ennemi037(171 * 16 + 8, 66 * 16 - 10));
        addEnnemi(new Ennemi037(188 * 16 + 8, 66 * 16 - 10));

        addEnnemi(new Ennemi041(110 * 16, 64 * 16 - 8));
        addEnnemi(new Ennemi041(231 * 16, 67 * 16 - 8));
        addEnnemi(new Ennemi041(248 * 16, 67 * 16 - 8));
        addEnnemi(new Ennemi041(248 * 16, 81 * 16 - 8));

        addEnnemi(new Ennemi055(84 * 16 + 5, 78 * 16));
        addEnnemi(new Ennemi055(94 * 16 + 5, 78 * 16));
        addEnnemi(new Ennemi055(29 * 16 + 5, 4 * 16));
        addEnnemi(new Ennemi055(26 * 16 + 5, 23 * 16));
        addEnnemi(new Ennemi055(51 * 16 + 5, 33 * 16));
        addEnnemi(new Ennemi055(48 * 16 + 5, 65 * 16));
        addEnnemi(new Ennemi055(45 * 16 + 5, 84 * 16));
        addEnnemi(new Ennemi055(133 * 16 + 5, 84 * 16));
        addEnnemi(new Ennemi055(128 * 16 + 5, 64 * 16));
        addEnnemi(new Ennemi055(149 * 16 + 5, 52 * 16));
        addEnnemi(new Ennemi055(135 * 16 + 5, 22 * 16));
        addEnnemi(new Ennemi055(141 * 16 + 5, 32 * 16));
        addEnnemi(new Ennemi055(148 * 16 + 5, 4 * 16));

        addObject(new Jarre(7 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(8 * 16, 47 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(11 * 16, 47 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(12 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(24 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(25 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(26 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(27 * 16, 49 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(28 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(29 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 49 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(32 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(33 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(34 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(35 * 16, 49 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(24 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(25 * 16, 50 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(26 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(27 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(28 * 16, 50 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(29 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(32 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(33 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(34 * 16, 50 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(35 * 16, 50 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(25 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(26 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(27 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(32 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(33 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(34 * 16, 12 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(44 * 16, 77 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(44 * 16, 87 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(55 * 16, 77 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(55 * 16, 87 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(124 * 16, 77 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(124 * 16, 87 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(135 * 16, 77 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(135 * 16, 87 * 16, 0, (scene->getCoffre(6, 13)) ? TI_NO_ITEM : TI_CLE, map));
        addObject(new Jarre(127 * 16, 39 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(132 * 16, 39 * 16, 0, (scene->getCoffre(6, 12)) ? TI_NO_ITEM : TI_CLE, map));
        addObject(new Jarre(144 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(145 * 16, 47 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(146 * 16, 47 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(153 * 16, 47 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(154 * 16, 47 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(155 * 16, 47 * 16, 0, TI_NO_ITEM, map));
        break;
    case 21:
        if (!inventory->hasCoeur(6))
        {
            addEnnemi(new Ennemi066(247 * 16, 16 * 16, map));
        }
        if (!inventory->hasGraal(3))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GRAAL, 250 * 16, 6 * 16 + 8, 3));
        }

        addObject(new Coffre(96 * 16, 18 * 16, 0, scene->getCoffre(7, 0), TI_CARTE_DONJON));
        addObject(new Coffre(29 * 16 + 8, 2 * 16, 0, scene->getCoffre(7, 1), TI_BOUSSOLE));
        addObject(new Coffre(49 * 16 + 8, 6 * 16, 0, scene->getCoffre(7, 2), TI_CLE_BOSS));
        if (scene->getCoffre(7, 2) == 2)
            ouvrePorte(249, 28, 0);

        addObject(new Coffre(255 * 16 + 8, 50 * 16 + 8, 1, inventory->hasObject(PALMES), TI_PALMES));

        addObject(new Coffre(83 * 16, 2 * 16, 0, scene->getCoffre(7, 4), TI_CLE, 4));
        addObject(new Coffre(106 * 16 + 8, 2 * 16, 0, scene->getCoffre(7, 5), TI_CLE, 5));
        addObject(new Coffre(124 * 16, 37 * 16, 0, scene->getCoffre(7, 6), TI_CLE, 6));
        addObject(new Coffre(159 * 16, 22 * 16, 0, scene->getCoffre(7, 7), TI_CLE, 7));
        addObject(new Coffre(158 * 16, 37 * 16, 0, scene->getCoffre(7, 8), TI_CLE, 8));
        addObject(new Coffre(231 * 16, 19 * 16, 0, scene->getCoffre(7, 9), TI_CLE, 9));
        addObject(new Coffre(249 * 16 + 8, 49 * 16, 0, scene->getCoffre(7, 10), TI_CLE, 10));

        if (scene->getCoffre(7, 11))
            ouvrePorte(29, 43, 0);
        if (scene->getCoffre(7, 12))
            ouvrePorte(49, 13, 0);
        if (scene->getCoffre(7, 13))
            ouvrePorte(118, 21, 1);
        if (scene->getCoffre(7, 14))
            ouvrePorte(158, 51, 1);
        if (scene->getCoffre(7, 15))
            ouvrePorte(178, 51, 1);
        if (scene->getCoffre(7, 16))
            ouvrePorte(209, 43, 0);
        if (scene->getCoffre(7, 17))
            ouvrePorte(238, 36, 1);
        if (scene->getCoffre(7, 18))
            ouvrePorte(29, 13, 0);
        if (scene->getCoffre(7, 19))
            ouvrePorte(38, 51, 1);
        if (scene->getCoffre(7, 20))
            ouvrePorte(38, 6, 1);
        if (scene->getCoffre(7, 21))
            ouvrePorte(89, 28, 0);
        if (scene->getCoffre(7, 22))
            ouvrePorte(118, 51, 1);
        if (scene->getCoffre(7, 23))
            ouvrePorte(169, 13, 0);
        if (scene->getCoffre(7, 24))
            ouvrePorte(189, 13, 0);
        if (scene->getCoffre(7, 25))
            ouvrePorte(229, 28, 0);
        if (scene->getCoffre(7, 26))
            ouvrePorte(229, 43, 0);
        if (scene->getCoffre(7, 27))
            ouvrePorte(278, 21, 1);

        addObject(new Interrupteur(24 * 16, 22 * 16, 0, scene->getCoffre(7, 18), map));
        addObject(new Interrupteur(23 * 16, 56 * 16, 0, scene->getCoffre(7, 19), map));
        addObject(new Interrupteur(57 * 16, 7 * 16, 0, scene->getCoffre(7, 20), map));
        addObject(new Interrupteur(96 * 16, 26 * 16, 0, scene->getCoffre(7, 21), map));
        addObject(new Interrupteur(130 * 16, 49 * 16, 0, scene->getCoffre(7, 22), map));
        addObject(new Interrupteur(176 * 16, 7 * 16, 0, scene->getCoffre(7, 23), map));
        addObject(new Interrupteur(196 * 16, 11 * 16, 0, scene->getCoffre(7, 24), map));
        addObject(new Interrupteur(230 * 16, 25 * 16, 0, scene->getCoffre(7, 25), map));
        addObject(new Interrupteur(223 * 16, 52 * 16, 0, scene->getCoffre(7, 26), map));
        addObject(new Interrupteur(272 * 16, 26 * 16, 0, scene->getCoffre(7, 27), map));

        addObject(new Sphere(50 * 16, 2 * 16));
        addObject(new Sphere(56 * 16 + 8, 56 * 16));
        addObject(new Sphere(89 * 16 + 8, 6 * 16));
        addObject(new Sphere(110 * 16, 22 * 16));
        addObject(new Sphere(137 * 16, 52 * 16));
        addObject(new Sphere(272 * 16, 51 * 16));
        addObject(new Sphere(283 * 16, 3 * 16));

        addEnnemi(new Ennemi009(9 * 16 + 8, 21 * 16 + 8));
        addEnnemi(new Ennemi009(29 * 16 + 8, 4 * 16 + 8));
        addEnnemi(new Ennemi009(269 * 16 + 8, 6 * 16 + 8));

        addEnnemi(new Ennemi010(59 * 16 + 8, 32 * 16));
        addEnnemi(new Ennemi010(39 * 16 + 8, 32 * 16));
        addEnnemi(new Ennemi010(49 * 16 + 8, 27 * 16));
        addEnnemi(new Ennemi010(139 * 16 + 8, 32 * 16 + 8));
        addEnnemi(new Ennemi010(162 * 16 + 8, 32 * 16 + 8));

        addEnnemi(new Ennemi022(71 * 16, 52 * 16 - 7));
        addEnnemi(new Ennemi022(65 * 16, 37 * 16 - 7));
        addEnnemi(new Ennemi022(33 * 16, 37 * 16 - 7));
        addEnnemi(new Ennemi022(36 * 16, 22 * 16 - 7));
        addEnnemi(new Ennemi022(62 * 16, 22 * 16 - 7));
        addEnnemi(new Ennemi022(95 * 16, 7 * 16 - 7));
        addEnnemi(new Ennemi022(193 * 16, 33 * 16 - 7));
        addEnnemi(new Ennemi022(106 * 16, 4 * 16 - 7));
        addEnnemi(new Ennemi022(174 * 16, 27 * 16 - 7));
        addEnnemi(new Ennemi022(140 * 16, 18 * 16 - 7));
        addEnnemi(new Ennemi022(206 * 16, 11 * 16 - 7));
        addEnnemi(new Ennemi022(223 * 16, 6 * 16 - 7));
        addEnnemi(new Ennemi022(232 * 16, 14 * 16 - 7));
        addEnnemi(new Ennemi022(295 * 16, 3 * 16 - 7));
        addEnnemi(new Ennemi022(295 * 16, 48 * 16 - 7));
        addEnnemi(new Ennemi022(264 * 16, 34 * 16 - 7));
        addEnnemi(new Ennemi022(249 * 16, 55 * 16 - 7));
        addEnnemi(new Ennemi022(129 * 16, 55 * 16 - 7));

        addEnnemi(new Ennemi023(89 * 16 + 3, 36 * 16 - 1));
        addEnnemi(new Ennemi023(70 * 16 + 3, 7 * 16 - 1));
        addEnnemi(new Ennemi023(9 * 16 + 3, 36 * 16 - 1));
        addEnnemi(new Ennemi023(166 * 16 + 3, 7 * 16 - 1));
        addEnnemi(new Ennemi023(104 * 16 + 3, 38 * 16 - 1));
        addEnnemi(new Ennemi023(169 * 16 + 3, 52 * 16 - 1));
        addEnnemi(new Ennemi023(224 * 16 + 3, 37 * 16 - 1));
        addEnnemi(new Ennemi023(214 * 16 + 3, 37 * 16 - 1));
        addEnnemi(new Ennemi023(269 * 16 + 3, 22 * 16 - 1));
        addEnnemi(new Ennemi023(29 * 16 + 3, 52 * 16 - 1));

        addEnnemi(new Ennemi027(92 * 16, 48 * 16 - 1));
        addEnnemi(new Ennemi027(92 * 16, 56 * 16 - 1));
        addEnnemi(new Ennemi027(96 * 16, 22 * 16 - 1));
        addEnnemi(new Ennemi027(4 * 16, 3 * 16 - 1));
        addEnnemi(new Ennemi027(15 * 16, 3 * 16 - 1));
        addEnnemi(new Ennemi027(194 * 16, 50 * 16 - 1));
        addEnnemi(new Ennemi027(194 * 16, 54 * 16 - 1));
        addEnnemi(new Ennemi027(149 * 16 + 8, 7 * 16 - 1));
        addEnnemi(new Ennemi027(124 * 16, 3 * 16 - 1));
        addEnnemi(new Ennemi027(129 * 16 + 8, 3 * 16 - 1));
        addEnnemi(new Ennemi027(135 * 16, 3 * 16 - 1));
        addEnnemi(new Ennemi027(232 * 16, 52 * 16 - 1));

        addObject(new Jarre(95 * 16, 32 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(95 * 16, 42 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(144 * 16, 4 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(144 * 16, 10 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(165 * 16, 4 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(165 * 16, 10 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(182 * 16, 49 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(182 * 16, 55 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(184 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(184 * 16, 57 * 16, 1, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(195 * 16, 47 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(195 * 16, 57 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(197 * 16, 49 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(197 * 16, 55 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(194 * 16, 19 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(194 * 16, 25 * 16, 1, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(205 * 16, 34 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(205 * 16, 40 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(255 * 16, 35 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(255 * 16, 36 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(255 * 16, 37 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(255 * 16, 38 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(255 * 16, 39 * 16, 1, TI_FLECHE, map));
        break;
    case 22:
        if (!inventory->hasCoeur(7))
        {
            addEnnemi(new Ennemi028(89 * 16, 17 * 16 - 6));
        }
        if (!inventory->hasGraal(4))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GRAAL, 90 * 16, 6 * 16 + 8, 4));
        }

        addObject(new Coffre(132 * 16, 77 * 16, 0, scene->getCoffre(8, 0), TI_CARTE_DONJON));
        addObject(new Coffre(39 * 16 + 8, 32 * 16, 0, scene->getCoffre(8, 1), TI_BOUSSOLE));
        addObject(new Coffre(50 * 16, 21 * 16, 0, scene->getCoffre(8, 2), TI_CLE_BOSS));
        if (scene->getCoffre(8, 2) == 2)
            ouvrePorte(89, 28, 0);

        addObject(new Coffre(109 * 16 + 8, 6 * 16 + 8, 1, scene->getCoffre(8, 25), link->getTunique() == 1 ? TI_TUNIQUE_BLEUE : TI_TUNIQUE_ROUGE));

        addObject(new Coffre(9 * 16, 23 * 16, 0, scene->getCoffre(8, 4), TI_CLE, 4));
        addObject(new Coffre(83 * 16, 48 * 16, 0, scene->getCoffre(8, 5), TI_CLE, 5));
        addObject(new Coffre(119 * 16 + 8, 35 * 16, 0, scene->getCoffre(8, 6), TI_CLE, 6));
        addObject(new Coffre(156 * 16, 33 * 16, 0, scene->getCoffre(8, 7), TI_CLE, 7));
        addObject(new Coffre(169 * 16, 82 * 16, 0, scene->getCoffre(8, 8), TI_CLE, 8));
        addObject(new Coffre(179 * 16 + 8, 7 * 16, 0, scene->getCoffre(8, 9), TI_CLE, 9));

        if (scene->getCoffre(8, 10))
            ouvrePorte(49, 28, 0);
        if (scene->getCoffre(8, 11))
            ouvrePorte(58, 36, 1);
        if (scene->getCoffre(8, 12))
            ouvrePorte(98, 81, 1);
        if (scene->getCoffre(8, 13))
            ouvrePorte(118, 21, 1);
        if (scene->getCoffre(8, 14))
            ouvrePorte(138, 81, 1);
        if (scene->getCoffre(8, 15))
            ouvrePorte(149, 28, 0);
        if (scene->getCoffre(8, 16))
            ouvrePorte(9, 73, 0);
        if (scene->getCoffre(8, 17))
            ouvrePorte(38, 21, 1);
        if (scene->getCoffre(8, 18))
            ouvrePorte(169, 28, 0);
        if (scene->getCoffre(8, 19))
            ouvrePorte(189, 73, 0);
        if (scene->getCoffre(8, 20))
            ouvrePorte(209, 43, 0);
        if (scene->getCoffre(8, 21))
            ouvrePorte(9, 28, 2);
        if (scene->getCoffre(8, 22))
            ouvrePorte(69, 28, 2);
        if (scene->getCoffre(8, 23))
            ouvrePorte(98, 6, 3);

        if (scene->getCoffre(8, 24))
        {
            ouvrePorte(58, 51, 1);
            map->setSol(62 * 16, 49 * 16, 1812);
            map->setSol(62 * 16, 55 * 16, 1812);
            map->setSol(62 * 16, 64 * 16, 1812);
            map->setSol(62 * 16, 70 * 16, 1812);
            map->setSol(75 * 16, 49 * 16, 1812);
            map->setSol(75 * 16, 55 * 16, 1812);
            map->setSol(75 * 16, 64 * 16, 1812);
            map->setSol(75 * 16, 70 * 16, 1812);
        }

        addObject(new Interrupteur(16 * 16, 80 * 16, 0, scene->getCoffre(8, 16), map));
        addObject(new Interrupteur(52 * 16, 26 * 16, 0, scene->getCoffre(8, 17), map));
        addObject(new Interrupteur(166 * 16, 27 * 16, 0, scene->getCoffre(8, 18), map));
        addObject(new Interrupteur(196 * 16, 77 * 16, 0, scene->getCoffre(8, 19), map));
        addObject(new Interrupteur(217 * 16, 42 * 16, 0, scene->getCoffre(8, 20), map, false));

        addObject(new Caisse(139 * 16, 22 * 16, 4));
        addObject(new Caisse(140 * 16, 22 * 16, 4));
        addObject(new Caisse(190 * 16, 22 * 16, 4));
        addObject(new Caisse(191 * 16, 22 * 16, 4));
        addObject(new Caisse(204 * 16, 78 * 16, 4));
        addObject(new Caisse(205 * 16, 78 * 16, 4));

        addObject(new PiegeLong(25 * 16, 76 * 16 + 8, S));
        addObject(new PiegeLong(47 * 16, 76 * 16 + 8, S));
        addObject(new PiegeLong(126 * 16, 20 * 16 + 8, S));
        addObject(new PiegeLong(146 * 16, 20 * 16 + 8, S));
        addObject(new PiegeLong(207 * 16, 16 * 16 + 8, S));
        addObject(new PiegeLong(215 * 16, 26 * 16 + 8, S));
        addObject(new PiegeLong(216 * 16, 3 * 16 + 8, S));

        addEnnemi(new Ennemi001(190 * 16, 32 * 16 + 6));
        addEnnemi(new Ennemi001(210 * 16, 32 * 16 + 6));
        addEnnemi(new Ennemi001(170 * 16, 22 * 16 + 6));
        addEnnemi(new Ennemi001(156 * 16, 36 * 16 + 6));
        addEnnemi(new Ennemi001(83 * 16, 51 * 16 + 6));
        addEnnemi(new Ennemi001(39 * 16, 69 * 16 + 6));
        addEnnemi(new Ennemi001(39 * 16, 34 * 16 + 6));
        addEnnemi(new Ennemi001(75 * 16, 36 * 16 + 6));
        addEnnemi(new Ennemi001(187 * 16, 81 * 16 + 6));
        addEnnemi(new Ennemi001(196 * 16 + 8, 82 * 16 + 6));
        addEnnemi(new Ennemi001(214 * 16 + 8, 77 * 16 + 6));

        addEnnemi(new Ennemi018(236 * 16, 82 * 16 + 2));
        addEnnemi(new Ennemi018(206 * 16, 53 * 16 + 2));
        addEnnemi(new Ennemi018(204 * 16, 68 * 16 + 2));
        addEnnemi(new Ennemi018(198 * 16, 56 * 16 + 2));
        addEnnemi(new Ennemi018(185 * 16, 64 * 16 + 2));

        addEnnemi(new Ennemi055(230 * 16 + 5, 37 * 16));
        addEnnemi(new Ennemi055(108 * 16 + 8 + 5, 81 * 16));
        addEnnemi(new Ennemi055(128 * 16 + 8 + 5, 81 * 16));
        addEnnemi(new Ennemi055(108 * 16 + 8 + 5, 42 * 16));
        addEnnemi(new Ennemi055(128 * 16 + 5, 42 * 16));
        addEnnemi(new Ennemi055(118 * 16 + 5, 58 * 16));
        addEnnemi(new Ennemi055(5 * 16 + 5, 64 * 16));
        addEnnemi(new Ennemi055(12 * 16 + 5, 64 * 16));
        addEnnemi(new Ennemi055(67 * 16 + 5, 58 * 16));
        addEnnemi(new Ennemi055(8 * 16 + 5, 43 * 16));
        addEnnemi(new Ennemi055(170 * 16 + 5, 81 * 16));

        addObject(new Jarre(5 * 16, 34 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(5 * 16, 55 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(10 * 16, 23 * 16, 0, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(69 * 16, 23 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(70 * 16, 23 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(69 * 16, 24 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(70 * 16, 24 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(69 * 16, 25 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(70 * 16, 25 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(84 * 16, 34 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(95 * 16, 34 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(169 * 16, 55 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(170 * 16, 55 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(175 * 16, 34 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(176 * 16, 34 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(177 * 16, 34 * 16, 0, TI_BOMBE, map));
        addObject(new Jarre(182 * 16, 32 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(183 * 16, 32 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Jarre(182 * 16, 42 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(183 * 16, 42 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(216 * 16, 32 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(217 * 16, 32 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(216 * 16, 42 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(217 * 16, 42 * 16, 0, TI_INTERRUPTEUR, map));
        addObject(new Jarre(222 * 16, 34 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(222 * 16, 40 * 16, 0, TI_FLECHE, map));
        addObject(new Jarre(235 * 16, 34 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(235 * 16, 40 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(237 * 16, 50 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(237 * 16, 51 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(237 * 16, 52 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(237 * 16, 53 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(237 * 16, 54 * 16, 0, TI_FLECHE, map));
        break;
    case 23:
        if (!inventory->hasCoeur(8))
        {
            addEnnemi(new Ennemi071(209 * 16 - 10, 32 * 16 - 7));
        }
        addObject(new Pnj(16 * 209, 16 * 19 + 8, 16, 347));

        addObject(new Coffre(169 * 16 + 8, 3 * 16, 0, scene->getCoffre(9, 0), TI_CARTE_DONJON));
        addObject(new Coffre(229 * 16 + 8, 67 * 16, 0, scene->getCoffre(9, 1), TI_BOUSSOLE));
        addObject(new Coffre(269 * 16 + 8, 65 * 16, 0, scene->getCoffre(9, 2), TI_CLE_BOSS));
        if (scene->getCoffre(9, 2) == 2)
            ouvrePorte(209, 43, 0);

        addObject(new Coffre(169 * 16, 51 * 16 + 8, 1, inventory->hasObject(BAGUETTE_FEU), TI_BAGUETTE_FEU));

        addObject(new Coffre(109 * 16 + 8, 23 * 16, 0, scene->getCoffre(9, 4), TI_CLE, 4));
        addObject(new Coffre(269 * 16 + 8, 5 * 16, 0, scene->getCoffre(9, 6), TI_CLE, 6));
        addObject(new Coffre(349 * 16 + 8, 65 * 16, 0, scene->getCoffre(9, 7), TI_CLE, 7));

        if (scene->getCoffre(9, 8))
            ouvrePorte(49, 13, 0);
        if (scene->getCoffre(9, 9))
            ouvrePorte(118, 66, 1);
        if (scene->getCoffre(9, 10))
            ouvrePorte(138, 36, 1);
        if (scene->getCoffre(9, 11))
            ouvrePorte(169, 43, 0);
        if (scene->getCoffre(9, 12))
            ouvrePorte(89, 28, 0);
        if (scene->getCoffre(9, 13))
            ouvrePorte(138, 51, 1);
        if (scene->getCoffre(9, 14))
            ouvrePorte(178, 21, 1);
        if (scene->getCoffre(9, 15))
            ouvrePorte(198, 6, 1);
        if (scene->getCoffre(9, 16))
            ouvrePorte(218, 6, 1);
        if (scene->getCoffre(9, 17))
            ouvrePorte(98, 36, 3);
        if (scene->getCoffre(9, 18))
            ouvrePorte(118, 36, 3);
        if (scene->getCoffre(9, 19))
            ouvrePorte(169, 7, 4);
        if (scene->getCoffre(9, 20))
            ouvrePorte(238, 51, 3);
        if (scene->getCoffre(9, 21))
            ouvrePorte(238, 66, 3);

        if (scene->getCoffre(9, 22))
        {
            ouvrePorte(18, 36, 1);
            map->setSol(22 * 16, 32 * 16, 1812);
            map->setSol(37 * 16, 42 * 16, 1812);
        }
        if (scene->getCoffre(9, 23))
        {
            ouvrePorte(38, 36, 1);
            map->setSol(49 * 16, 40 * 16, 1812);
            map->setSol(50 * 16, 40 * 16, 1812);
            map->setSol(56 * 16, 37 * 16, 1812);
        }
        if (scene->getCoffre(9, 24))
        {
            ouvrePorte(49, 28, 0);
            map->setSol(49 * 16, 22 * 16, 1812);
            map->setSol(50 * 16, 22 * 16, 1812);
        }
        if (scene->getCoffre(9, 25))
        {
            ouvrePorte(109, 43, 0);
            map->setSol(103 * 16, 37 * 16, 1812);
            map->setSol(116 * 16, 37 * 16, 1812);
        }
        if (scene->getCoffre(9, 26))
        {
            ouvrePorte(178, 66, 1);
            map->setSol(189 * 16, 72 * 16, 1812);
            map->setSol(190 * 16, 72 * 16, 1812);
        }

        addObject(new Interrupteur(92 * 16, 27 * 16, 0, scene->getCoffre(9, 12), map));
        addObject(new Interrupteur(150 * 16, 51 * 16, 0, scene->getCoffre(9, 13), map));
        addObject(new Interrupteur(165 * 16, 24 * 16, 0, scene->getCoffre(9, 14), map));
        addObject(new Interrupteur(212 * 16, 7 * 16, 0, scene->getCoffre(9, 15), map));
        addObject(new Interrupteur(207 * 16, 7 * 16, 0, scene->getCoffre(9, 16), map));

        addObject(new InterrupteurStar(249 * 16, 3 * 16, false, map));
        addObject(new InterrupteurStar(250 * 16, 3 * 16, false, map));
        addObject(new InterrupteurStar(89 * 16, 27 * 16, true, map));
        addObject(new InterrupteurStar(90 * 16, 27 * 16, true, map));

        addObject(new Caisse(51 * 16, 36 * 16, 3));
        addObject(new Caisse(51 * 16, 37 * 16, 3));
        addObject(new Caisse(51 * 16, 38 * 16, 3));
        addObject(new Caisse(53 * 16, 36 * 16, 3));
        addObject(new Caisse(53 * 16, 37 * 16, 3));
        addObject(new Caisse(53 * 16, 38 * 16, 3));

        addObject(new PiegePics(70 * 16, 50 * 16 + 8, S));
        addObject(new PiegePics(70 * 16, 65 * 16 + 8, S));
        addObject(new PiegePics(189 * 16, 30 * 16, S));
        addObject(new PiegePics(252 * 16, 38 * 16, S));
        addObject(new PiegePics(252 * 16, 30 * 16, S));
        addObject(new PiegePics(239 * 16, 28 * 16, S));
        addObject(new PiegePics(226 * 16, 28 * 16, S));

        addObject(new PiegeFeu(22 * 16, 42 * 16));
        addObject(new PiegeFeu(37 * 16, 32 * 16));
        addObject(new PiegeFeu(42 * 16, 27 * 16));
        addObject(new PiegeFeu(57 * 16, 27 * 16));
        addObject(new PiegeFeu(65 * 16, 67 * 16));
        addObject(new PiegeFeu(68 * 16, 49 * 16));

        addObject(new PiegeMain(261 * 16, 1 * 16));
        addObject(new PiegeMain(261 * 16, 61 * 16));
        addObject(new PiegeMain(301 * 16, 31 * 16));
        addObject(new PiegeMain(341 * 16, 1 * 16));
        addObject(new PiegeMain(341 * 16, 61 * 16));

        addObject(new PiegeLong(184 * 16, 21 * 16 - 8, S));

        addObject(new PiegeMurs(160 * 16, 4 * 16, map));

        addEnnemi(new Ennemi007(344 * 16, 6 * 16));
        addEnnemi(new Ennemi007(355 * 16, 6 * 16));
        addEnnemi(new Ennemi007(349 * 16 + 8, 2 * 16));
        addEnnemi(new Ennemi007(349 * 16 + 8, 10 * 16));
        addEnnemi(new Ennemi007(249 * 16, 52 * 16));
        addEnnemi(new Ennemi007(173 * 16, 23 * 16));
        addEnnemi(new Ennemi007(233 * 16, 28 * 16));
        addEnnemi(new Ennemi007(105 * 16, 50 * 16));
        addEnnemi(new Ennemi007(114 * 16, 50 * 16));
        addEnnemi(new Ennemi007(9 * 16 + 8, 65 * 16));

        addEnnemi(new Ennemi029(69 * 16 + 8, 22 * 16 - 10));
        addEnnemi(new Ennemi029(109 * 16 + 8, 36 * 16 - 10));
        addEnnemi(new Ennemi029(225 * 16 + 8, 67 * 16 - 10));
        addEnnemi(new Ennemi029(244 * 16, 8 * 16 - 10));
        addEnnemi(new Ennemi029(255 * 16, 8 * 16 - 10));
        addEnnemi(new Ennemi029(93 * 16, 35 * 16 - 10));
        addEnnemi(new Ennemi029(106 * 16, 67 * 16 - 10));
        addEnnemi(new Ennemi029(113 * 16, 67 * 16 - 10));
        addEnnemi(new Ennemi029(166 * 16, 67 * 16 - 10));
        addEnnemi(new Ennemi029(253 * 16, 67 * 16 - 10));
        addEnnemi(new Ennemi029(145 * 16 + 8, 61 * 16 - 10));
        addEnnemi(new Ennemi029(150 * 16, 68 * 16 - 10));
        addEnnemi(new Ennemi029(106 * 16, 21 * 16 - 10));
        addEnnemi(new Ennemi029(113 * 16, 21 * 16 - 10));
        addEnnemi(new Ennemi029(149 * 16 + 8, 29 * 16 - 10));
        addEnnemi(new Ennemi029(9 * 16 + 8, 36 * 16 - 10));
        addEnnemi(new Ennemi029(225 * 16, 49 * 16 - 10));
        addEnnemi(new Ennemi029(234 * 16, 49 * 16 - 10));
        addEnnemi(new Ennemi029(86 * 16, 35 * 16 - 10));

        addEnnemi(new Ennemi030(89 * 16 + 8, 67 * 16 - 8));
        addEnnemi(new Ennemi030(196 * 16, 23 * 16 - 8 - 8));
        addEnnemi(new Ennemi030(196 * 16, 31 * 16 - 8 - 8));
        addEnnemi(new Ennemi030(129 * 16 + 8, 67 * 16 - 8));
        addEnnemi(new Ennemi030(237 * 16, 39 * 16 - 8 - 8));
        addEnnemi(new Ennemi030(241 * 16 + 8, 23 * 16 - 8));
        addEnnemi(new Ennemi030(223 * 16 + 8, 21 * 16 - 8 - 8));
        addEnnemi(new Ennemi030(109 * 16 + 8, 5 * 16 - 8));
        addEnnemi(new Ennemi030(49 * 16 + 8, 37 * 16 - 8));

        addEnnemi(new Ennemi062(149 * 16 + 4, 3 * 16, false));
        addEnnemi(new Ennemi062(69 * 16 + 4, 3 * 16, false));
        addEnnemi(new Ennemi062(9 * 16 + 4, 20 * 16, false));

        addObject(new Jarre(49 * 16, 39 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(50 * 16, 39 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(84 * 16, 32 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(84 * 16, 62 * 16, 1, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(84 * 16, 72 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(95 * 16, 32 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(106 * 16, 62 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(113 * 16, 62 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(135 * 16, 62 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(135 * 16, 72 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(164 * 16, 17 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(164 * 16, 64 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(164 * 16, 70 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(175 * 16, 17 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(184 * 16, 47 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(195 * 16, 47 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(204 * 16, 49 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(215 * 16, 49 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(255 * 16, 64 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(255 * 16, 70 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(344 * 16, 2 * 16, 1, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(344 * 16, 10 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(355 * 16, 2 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(355 * 16, 10 * 16, 1, TI_MAGIE_PEU, map));
        break;
    case 24:
        if (!inventory->hasCoeur(9))
        {
            addEnnemi(new Ennemi043(49 * 16, 17 * 16));
        }
        addObject(new Pnj(16 * 49, 16 * 4 + 8, 16, 347));

        addObject(new Coffre(149 * 16 + 8, 21 * 16, 0, scene->getCoffre(10, 0), TI_CARTE_DONJON));
        addObject(new Coffre(97 * 16, 40 * 16, 0, scene->getCoffre(10, 1), TI_BOUSSOLE));
        addObject(new Coffre(152 * 16, 9 * 16, 0, scene->getCoffre(10, 2), TI_CLE_BOSS));
        if (scene->getCoffre(10, 2) == 2)
            ouvrePorte(49, 28, 0);

        addObject(new Coffre(48 * 16 + 8, 51 * 16 + 8, 1, inventory->hasObject(BAGUETTE_GLACE), TI_BAGUETTE_GLACE));

        addObject(new Coffre(26 * 16 + 8, 4 * 16, 0, scene->getCoffre(10, 4), TI_CLE, 4));
        addObject(new Coffre(89 * 16, 69 * 16, 0, scene->getCoffre(10, 5), TI_CLE, 5));
        addObject(new Coffre(109 * 16 + 8, 66 * 16, 0, scene->getCoffre(10, 6), TI_CLE, 6));
        addObject(new Coffre(149 * 16 + 8, 54 * 16, 0, scene->getCoffre(10, 7), TI_CLE, 7));
        addObject(new Coffre(169 * 16 + 8, 3 * 16, 0, scene->getCoffre(10, 8), TI_CLE, 8));

        if (scene->getCoffre(10, 9))
            ouvrePorte(38, 36, 1);
        if (scene->getCoffre(10, 10))
            ouvrePorte(38, 66, 1);
        if (scene->getCoffre(10, 11))
            ouvrePorte(58, 51, 1);
        if (scene->getCoffre(10, 12))
            ouvrePorte(138, 66, 1);
        if (scene->getCoffre(10, 13))
            ouvrePorte(178, 21, 1);
        if (scene->getCoffre(10, 14))
            ouvrePorte(58, 36, 1);
        if (scene->getCoffre(10, 15))
            ouvrePorte(89, 58, 0);
        if (scene->getCoffre(10, 16))
            ouvrePorte(109, 58, 0);
        if (scene->getCoffre(10, 17))
            ouvrePorte(118, 51, 1);
        if (scene->getCoffre(10, 18))
            ouvrePorte(149, 13, 0);
        if (scene->getCoffre(10, 19))
            ouvrePorte(158, 66, 1);
        if (scene->getCoffre(10, 20))
            ouvrePorte(178, 66, 1);
        if (scene->getCoffre(10, 21))
            ouvrePorte(238, 6, 1);
        if (scene->getCoffre(10, 22))
            ouvrePorte(49, 66, 4);
        if (scene->getCoffre(10, 23))
            ouvrePorte(69, 6, 4);
        if (scene->getCoffre(10, 24))
            ouvrePorte(178, 6, 3);
        if (scene->getCoffre(10, 25))
            ouvrePorte(189, 13, 2);
        if (scene->getCoffre(10, 28))
            ouvrePorte(129, 43, 0);

        if (scene->getCoffre(10, 26))
        {
            ouvrePorte(29, 28, 0);
            map->setSol(27 * 16, 32 * 16, 1812);
            map->setSol(32 * 16, 32 * 16, 1812);
        }
        if (scene->getCoffre(10, 29))
        {
            ouvrePorte(249, 28, 0);
            map->setSol(247 * 16, 32 * 16, 1812);
            map->setSol(252 * 16, 32 * 16, 1812);
        }

        addObject(new Interrupteur(43 * 16, 37 * 16, 0, scene->getCoffre(10, 14), map));
        addObject(new Interrupteur(83 * 16, 67 * 16, 0, scene->getCoffre(10, 15), map));
        addObject(new Interrupteur(107 * 16, 63 * 16, 0, scene->getCoffre(10, 16), map));
        addObject(new Interrupteur(124 * 16, 47 * 16, 0, scene->getCoffre(10, 17), map, false));
        addObject(new Interrupteur(147 * 16, 9 * 16, 0, scene->getCoffre(10, 18), map));
        addObject(new Interrupteur(164 * 16, 72 * 16, 0, scene->getCoffre(10, 19), map));
        addObject(new Interrupteur(185 * 16, 70 * 16, 0, scene->getCoffre(10, 20), map));
        addObject(new Interrupteur(233 * 16, 13 * 16, 0, scene->getCoffre(10, 21), map));
        addObject(new Interrupteur(127 * 16, 39 * 16, 0, scene->getCoffre(10, 28), map));

        addObject(new PiegePics(26 * 16, 8 * 16, S));
        addObject(new PiegePics(31 * 16, 8 * 16, S));
        addObject(new PiegePics(74 * 16, 49 * 16, S));
        addObject(new PiegePics(75 * 16, 48 * 16, S));
        addObject(new PiegePics(76 * 16, 47 * 16, S));
        addObject(new PiegePics(83 * 16, 49 * 16, S));
        addObject(new PiegePics(84 * 16, 48 * 16, S));
        addObject(new PiegePics(85 * 16, 47 * 16, S));

        addObject(new PiegeLong(6 * 16, 13 * 16, S));
        addObject(new PiegeLong(23 * 16, 64 * 16, S));
        addObject(new PiegeLong(78 * 16, 5 * 16, S));
        addObject(new PiegeLong(84 * 16, 17 * 16, S));
        addObject(new PiegeLong(66 * 16, 32 * 16, S));
        addObject(new PiegeLong(216 * 16, 34 * 16, S));
        addObject(new PiegeLong(286 * 16, 6 * 16 - 8, S));
        addObject(new PiegeLong(286 * 16, 23 * 16 + 8, S));
        addObject(new PiegeLong(220 * 16, 2 * 16 - 8, S));

        addObject(new PiegeColere(275 * 16, 61 * 16));
        addObject(new PiegeColere(277 * 16, 49 * 16));
        addObject(new PiegeColere(293 * 16, 57 * 16));

        addEnnemi(new Ennemi002(128 * 16 - 3, 52 * 16 - 10));
        addEnnemi(new Ennemi002(133 * 16 - 3, 53 * 16 - 10));
        addEnnemi(new Ennemi002(169 * 16 - 3 + 8, 36 * 16 - 10));
        addEnnemi(new Ennemi002(193 * 16 - 3, 22 * 16 - 10));
        addEnnemi(new Ennemi002(183 * 16 - 3, 52 * 16 - 10));
        addEnnemi(new Ennemi002(113 * 16 - 3, 52 * 16 - 10));
        addEnnemi(new Ennemi002(169 * 16 - 3 + 8, 71 * 16 - 10));
        addEnnemi(new Ennemi002(194 * 16 - 3, 70 * 16 - 10));

        addEnnemi(new Ennemi026(15 * 16, 55 * 16));
        addEnnemi(new Ennemi026(27 * 16, 55 * 16));
        addEnnemi(new Ennemi026(9 * 16, 67 * 16));
        addEnnemi(new Ennemi026(91 * 16, 41 * 16));
        addEnnemi(new Ennemi026(86 * 16, 67 * 16));
        addEnnemi(new Ennemi026(222 * 16, 65 * 16));
        addEnnemi(new Ennemi026(210 * 16, 14 * 16));
        addEnnemi(new Ennemi026(216 * 16, 14 * 16));
        addEnnemi(new Ennemi026(217 * 16, 20 * 16));
        addEnnemi(new Ennemi026(228 * 16, 9 * 16));
        addEnnemi(new Ennemi026(232 * 16, 20 * 16));
        addEnnemi(new Ennemi026(235 * 16, 3 * 16));
        addEnnemi(new Ennemi026(228 * 16, 48 * 16));

        addEnnemi(new Ennemi041(125 * 16, 66 * 16 - 8));
        addEnnemi(new Ennemi041(127 * 16, 71 * 16 - 8));
        addEnnemi(new Ennemi041(246 * 16, 22 * 16 - 8));
        addEnnemi(new Ennemi041(253 * 16, 22 * 16 - 8));
        addEnnemi(new Ennemi041(65 * 16, 52 * 16));
        addEnnemi(new Ennemi041(71 * 16, 69 * 16));
        addEnnemi(new Ennemi041(294 * 16, 36 * 16 - 8));
        addEnnemi(new Ennemi041(285 * 16, 40 * 16 - 8));

        addEnnemi(new Ennemi042(90 * 16 - 5, 7 * 16 - 3));
        addEnnemi(new Ennemi042(247 * 16 - 5, 51 * 16 - 3));
        addEnnemi(new Ennemi042(249 * 16 - 5, 55 * 16 - 3));
        addEnnemi(new Ennemi042(254 * 16 - 5, 52 * 16 - 3));
        addEnnemi(new Ennemi042(165 * 16 - 5, 51 * 16 - 3));
        addEnnemi(new Ennemi042(174 * 16 - 5, 51 * 16 - 3));
        addEnnemi(new Ennemi042(229 * 16 - 5 + 8, 36 * 16 - 3));
        addEnnemi(new Ennemi042(205 * 16 - 5, 37 * 16 - 3));
        addEnnemi(new Ennemi042(104 * 16 - 5, 18 * 16 - 3));
        addEnnemi(new Ennemi042(108 * 16 - 5, 12 * 16 - 3));
        addEnnemi(new Ennemi042(114 * 16 - 5, 16 * 16 - 3));
        addEnnemi(new Ennemi042(125 * 16 - 5 + 8, 13 * 16 - 3));

        addEnnemi(new Ennemi062(9 * 16 + 4, 39 * 16, false));
        addEnnemi(new Ennemi062(272 * 16 + 4, 19 * 16, false));

        addObject(new Jarre(30 * 16, 60 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 60 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 61 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 61 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 62 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 62 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(30 * 16, 63 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(31 * 16, 63 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(105 * 16, 70 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(114 * 16, 70 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(124 * 16, 47 * 16, 1, TI_INTERRUPTEUR, map));
        addObject(new Jarre(124 * 16, 57 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(144 * 16, 57 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(155 * 16, 57 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(204 * 16, 34 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(204 * 16, 40 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(220 * 16, 61 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(220 * 16, 62 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(220 * 16, 63 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(221 * 16, 56 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(222 * 16, 56 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(221 * 16, 57 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(222 * 16, 57 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(225 * 16, 51 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(225 * 16, 52 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(235 * 16, 34 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(235 * 16, 40 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(285 * 16, 21 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(285 * 16, 22 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(294 * 16, 13 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(294 * 16, 14 * 16, 1, TI_NO_ITEM, map));
        break;
    case 25:
        if (!inventory->hasCoeur(10))
        {
            addEnnemi(new Ennemi073(180 * 16, 240 - 152, map));
        }
        else
        {
            map->setSol(191 * 16, 22 * 16, 3601);
        }
        addObject(new Pnj(16 * 49, 16 * 64 + 8, 16, 347));

        addObject(new Coffre(129 * 16 + 8, 7 * 16, 0, scene->getCoffre(11, 0), TI_CARTE_DONJON));
        addObject(new Coffre(89 * 16 + 8, 7 * 16, 0, scene->getCoffre(11, 1), TI_BOUSSOLE));
        addObject(new Coffre(209 * 16 + 8, 112 * 16, 0, scene->getCoffre(11, 2), TI_CLE_BOSS));
        if (scene->getCoffre(11, 2) == 2)
            ouvrePorte(49, 88, 0);

        addObject(new Coffre(129 * 16, 20 * 16 + 8, 1, link->getBouclier() == 3, TI_BOUCLIER_3));

        addObject(new Coffre(126 * 16, 52 * 16, 0, scene->getCoffre(11, 4), TI_CLE, 4));
        addObject(new Coffre(132 * 16, 52 * 16, 0, scene->getCoffre(11, 5), TI_CLE, 5));
        addObject(new Coffre(190 * 16, 67 * 16, 0, scene->getCoffre(11, 6), TI_CLE, 6));
        addObject(new Coffre(189 * 16 + 8, 95 * 16 + 8, 0, scene->getCoffre(11, 7), TI_CLE, 7));
        addObject(new Coffre(229 * 16 + 8, 97 * 16, 0, scene->getCoffre(11, 8), TI_CLE, 8));

        if (scene->getCoffre(11, 9))
            ouvrePorte(9, 43, 0);
        if (scene->getCoffre(11, 10))
            ouvrePorte(18, 96, 1);
        if (scene->getCoffre(11, 11))
            ouvrePorte(29, 43, 0);
        if (scene->getCoffre(11, 12))
            ouvrePorte(29, 88, 0);
        if (scene->getCoffre(11, 13))
            ouvrePorte(89, 43, 0);
        if (scene->getCoffre(11, 14))
            ouvrePorte(69, 28, 0);
        if (scene->getCoffre(11, 15))
            ouvrePorte(69, 88, 0);
        if (scene->getCoffre(11, 16))
        {
            ouvrePorte(58, 96, 1);
            ouvrePorte(69, 103, 0);
        }
        if (scene->getCoffre(11, 17))
            ouvrePorte(89, 88, 0);
        if (scene->getCoffre(11, 18))
            ouvrePorte(129, 73, 0);
        if (scene->getCoffre(11, 19))
            ouvrePorte(38, 21, 3);
        if (scene->getCoffre(11, 20))
            ouvrePorte(49, 28, 2);
        if (scene->getCoffre(11, 21))
            ouvrePorte(109, 13, 2);
        if (scene->getCoffre(11, 22))
            ouvrePorte(129, 28, 2);

        if (scene->getCoffre(11, 25))
        {
            ouvrePorte(178, 66, 1);
            map->setSol(163 * 16, 74 * 16, 1812);
            map->setSol(163 * 16, 79 * 16, 1812);
            map->setSol(177 * 16, 74 * 16, 1812);
            map->setSol(177 * 16, 79 * 16, 1812);
        }

        addObject(new Interrupteur(67 * 16, 26 * 16, 0, scene->getCoffre(11, 14), map));
        addObject(new Interrupteur(77 * 16, 85 * 16, 0, scene->getCoffre(11, 15), map, false));
        addObject(new Interrupteur(77 * 16, 97 * 16, 0, scene->getCoffre(11, 16), map));
        addObject(new Interrupteur(96 * 16, 97 * 16, 0, scene->getCoffre(11, 17), map));
        addObject(new Interrupteur(123 * 16, 67 * 16, 0, scene->getCoffre(11, 18), map));

        addObject(new InterrupteurStar(31 * 16, 99 * 16, false, map, false));

        addObject(new Sphere(29 * 16 + 8, 21 * 16));
        addObject(new Sphere(9 * 16 + 8, 63 * 16));
        addObject(new Sphere(169 * 16 + 8, 112 * 16));
        addObject(new Sphere(205 * 16 + 8, 95 * 16 + 8));

        addObject(new Caisse(17 * 16, 4 * 16, 0));
        addObject(new Caisse(17 * 16, 5 * 16, 0));
        addObject(new Caisse(16 * 16, 5 * 16, 0));
        addObject(new Caisse(16 * 16, 6 * 16, 0));
        addObject(new Caisse(16 * 16, 7 * 16, 0));
        addObject(new Caisse(16 * 16, 8 * 16, 0));
        addObject(new Caisse(16 * 16, 9 * 16, 0));
        addObject(new Caisse(17 * 16, 9 * 16, 0));
        addObject(new Caisse(17 * 16, 10 * 16, 0));

        addObject(new PiegePics(228 * 16, 66 * 16, S));
        addObject(new PiegePics(229 * 16, 66 * 16, S));
        addObject(new PiegePics(230 * 16, 66 * 16, S));
        addObject(new PiegePics(231 * 16, 66 * 16, S));

        addObject(new PiegeFeu(26 * 16, 11 * 16));
        addObject(new PiegeFeu(35 * 16, 6 * 16));
        addObject(new PiegeFeu(44 * 16 + 8, 8 * 16));
        addObject(new PiegeFeu(53 * 16, 3 * 16));
        addObject(new PiegeFeu(69 * 16, 37 * 16));
        addObject(new PiegeFeu(70 * 16, 37 * 16));

        addObject(new PiegeLong(46 * 16, 49 * 16 - 8, S));
        addObject(new PiegeLong(56 * 16, 49 * 16 - 8, S));
        addObject(new PiegeLong(66 * 16, 49 * 16 - 8, S));
        addObject(new PiegeLong(146 * 16, 80 * 16 - 8, S));
        addObject(new PiegeLong(146 * 16, 99 * 16 - 8, S));

        addEnnemi(new Ennemi026(29 * 16 + 8, 37 * 16));
        addEnnemi(new Ennemi026(46 * 16, 26 * 16));
        addEnnemi(new Ennemi026(84 * 16, 70 * 16));
        addEnnemi(new Ennemi026(84 * 16, 78 * 16));
        addEnnemi(new Ennemi026(95 * 16, 72 * 16));
        addEnnemi(new Ennemi026(95 * 16, 80 * 16));
        addEnnemi(new Ennemi026(111 * 16, 67 * 16));
        addEnnemi(new Ennemi026(165 * 16, 108 * 16));
        addEnnemi(new Ennemi026(165 * 16, 116 * 16));
        addEnnemi(new Ennemi026(174 * 16, 108 * 16));
        addEnnemi(new Ennemi026(174 * 16, 116 * 16));
        addEnnemi(new Ennemi026(165 * 16, 70 * 16));
        addEnnemi(new Ennemi026(165 * 16, 76 * 16));
        addEnnemi(new Ennemi026(174 * 16, 70 * 16));
        addEnnemi(new Ennemi026(174 * 16, 76 * 16));
        addEnnemi(new Ennemi026(205 * 16 + 8, 81 * 16));
        addEnnemi(new Ennemi026(198 * 16 + 8, 78 * 16));
        addEnnemi(new Ennemi026(209 * 16, 88 * 16 + 8));
        addEnnemi(new Ennemi026(4 * 16, 26 * 16));
        addEnnemi(new Ennemi026(4 * 16, 38 * 16));
        addEnnemi(new Ennemi026(15 * 16, 20 * 16));
        addEnnemi(new Ennemi026(15 * 16, 32 * 16));

        addEnnemi(new Ennemi030(7 * 16 + 8, 83 * 16 - 8));
        addEnnemi(new Ennemi030(9 * 16 + 8, 85 * 16 - 8));
        addEnnemi(new Ennemi030(11 * 16 + 8, 87 * 16 - 8));
        addEnnemi(new Ennemi030(37 * 16, 10 * 16 - 8));
        addEnnemi(new Ennemi030(46 * 16, 4 * 16 - 8));

        addEnnemi(new Ennemi032(26 * 16, 97 * 16 - 7));
        addEnnemi(new Ennemi032(53 * 16, 97 * 16 - 7));
        addEnnemi(new Ennemi032(26 * 16, 113 * 16 - 7));
        addEnnemi(new Ennemi032(53 * 16, 113 * 16 - 7));
        addEnnemi(new Ennemi032(25 * 16, 33 * 16 - 7));
        addEnnemi(new Ennemi032(34 * 16, 33 * 16 - 7));
        addEnnemi(new Ennemi032(71 * 16, 5 * 16 - 7));
        addEnnemi(new Ennemi032(63 * 16, 37 * 16 - 7));
        addEnnemi(new Ennemi032(76 * 16, 37 * 16 - 7));
        addEnnemi(new Ennemi032(145 * 16, 37 * 16 - 7));
        addEnnemi(new Ennemi032(154 * 16, 37 * 16 - 7));
        addEnnemi(new Ennemi032(129 * 16 + 8, 23 * 16 - 7));
        addEnnemi(new Ennemi032(86 * 16, 5 * 16 - 7));
        addEnnemi(new Ennemi032(93 * 16, 5 * 16 - 7));
        addEnnemi(new Ennemi032(105 * 16, 8 * 16 - 7));
        addEnnemi(new Ennemi032(114 * 16, 8 * 16 - 7));
        addEnnemi(new Ennemi032(86 * 16, 97 * 16 - 7));
        addEnnemi(new Ennemi032(133 * 16, 67 * 16 - 7));
        addEnnemi(new Ennemi032(105 * 16, 67 * 16 - 7));
        addEnnemi(new Ennemi032(146 * 16, 112 * 16 - 7));
        addEnnemi(new Ennemi032(4 * 16, 66 * 16 - 7));
        addEnnemi(new Ennemi032(15 * 16, 66 * 16 - 7));

        addEnnemi(new Ennemi033(14 * 16 - 3, 112 * 16 - 9));
        addEnnemi(new Ennemi033(65 * 16 - 3, 112 * 16 - 9));
        addEnnemi(new Ennemi033(66 * 16 - 3, 82 * 16 - 9));
        addEnnemi(new Ennemi033(73 * 16 - 3, 82 * 16 - 9));
        addEnnemi(new Ennemi033(5 * 16 - 3, 3 * 16 - 9));
        addEnnemi(new Ennemi033(14 * 16 - 3, 3 * 16 - 9));
        addEnnemi(new Ennemi033(73 * 16 - 3, 24 * 16 - 9));
        addEnnemi(new Ennemi033(5 * 16 - 3, 51 * 16 - 9));
        addEnnemi(new Ennemi033(14 * 16 - 3, 51 * 16 - 9));
        addEnnemi(new Ennemi033(112 * 16 - 3, 52 * 16 - 9));
        addEnnemi(new Ennemi033(147 * 16 - 3, 52 * 16 - 9));
        addEnnemi(new Ennemi033(86 * 16 - 3, 25 * 16 - 9));
        addEnnemi(new Ennemi033(98 * 16 - 3, 21 * 16 - 9));
        addEnnemi(new Ennemi033(100 * 16 - 3, 36 * 16 - 9));
        addEnnemi(new Ennemi033(113 * 16 - 3, 34 * 16 - 9));
        addEnnemi(new Ennemi033(105 * 16 - 3, 92 * 16 - 9));
        addEnnemi(new Ennemi033(121 * 16 - 3, 97 * 16 - 9));
        addEnnemi(new Ennemi033(186 * 16 - 3, 67 * 16 - 9));
        addEnnemi(new Ennemi033(227 * 16 - 3, 112 * 16 - 9));
        addEnnemi(new Ennemi033(135 * 16 - 3, 78 * 16 - 9));

        addEnnemi(new Ennemi034(69 * 16 - 4 + 8, 97 * 16 - 9));
        addEnnemi(new Ennemi034(9 * 16 - 4 + 8, 8 * 16 - 9));
        addEnnemi(new Ennemi034(29 * 16 - 4 + 8, 52 * 16 - 9));
        addEnnemi(new Ennemi034(127 * 16 - 4, 7 * 16 - 9));
        addEnnemi(new Ennemi034(132 * 16 - 4, 112 * 16 - 9));

        addEnnemi(new Ennemi062(23 * 16 + 4, 79 * 16, false));
        addEnnemi(new Ennemi062(35 * 16 + 4, 79 * 16, false));
        addEnnemi(new Ennemi062(154 * 16 + 4, 64 * 16, false));

        switch (scene->getCoffre(11, 23))
        {
        case 0:
            addEnnemi(new Ennemi072(56 * 16, 36 * 16 + 6));
            break;
        case 1:
            addEnnemi(new Ennemi072(136 * 16, 36 * 16 + 6));
            break;
        case 2:
            addEnnemi(new Ennemi072(39 * 16, 104 * 16 + 6));
            break;
        case 3:
            addEnnemi(new Ennemi072(103 * 16, 115 * 16 + 6));
            break;
        case 4:
            addEnnemi(new Ennemi072(194 * 16, 111 * 16 + 6));
            break;
        case 5:
            ouvrePorte(198, 111, 1);
            break;
        }

        addObject(new Jarre(7 * 16, 100 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(12 * 16, 100 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(31 * 16, 99 * 16, 1, TI_INTERRUPTEUR, map));
        addObject(new Jarre(46 * 16, 79 * 16, 1, TI_PETIT_COEUR, map));
        addObject(new Jarre(46 * 16, 85 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(48 * 16, 99 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(48 * 16, 110 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(53 * 16, 79 * 16, 1, TI_MAGIE_PEU, map));
        addObject(new Jarre(53 * 16, 85 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(62 * 16, 34 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(62 * 16, 40 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(62 * 16, 79 * 16, 1, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(62 * 16, 85 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 32 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 42 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 77 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(64 * 16, 87 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(75 * 16, 32 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(75 * 16, 42 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(75 * 16, 77 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(75 * 16, 87 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(77 * 16, 34 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(77 * 16, 40 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(77 * 16, 79 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(77 * 16, 85 * 16, 1, TI_INTERRUPTEUR, map));
        addObject(new Jarre(122 * 16, 39 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(123 * 16, 39 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(124 * 16, 39 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(125 * 16, 39 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(125 * 16, 40 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(125 * 16, 41 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(125 * 16, 42 * 16, 1, TI_NO_ITEM, map));
        break;
    case 26:
        if (!link->getInventory()->hasObject(MASQUE))
        {
            addEnnemi(new Ennemi075(309 * 16 + 6, 32 * 16));
        }
        else if (!inventory->hasCoeur(11))
        {
            map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, 310 * 16 + 1, 37 * 16, 11));
        }
        if (scene->getAvancement() < AV_GANON_VU)
        {
            addObject(new Pnj(16 * 309 - 6, 16 * 17 - 8, 110, 351));
        }

        addObject(new Coffre(69 * 16 + 8, 10 * 16, 0, scene->getCoffre(12, 0), TI_CARTE_DONJON));
        addObject(new Coffre(69 * 16 + 8, 52 * 16, 0, scene->getCoffre(12, 1), TI_BOUSSOLE));
        addObject(new Coffre(289 * 16 + 8, 19 * 16, 0, scene->getCoffre(12, 2), TI_CLE_BOSS));
        if (scene->getCoffre(12, 2) == 2)
            ouvrePorte(309, 43, 0);

        addObject(new Coffre(69 * 16, 63 * 16 + 8, 1, scene->getCoffre(12, 27), link->getTunique() == 1 ? TI_TUNIQUE_BLEUE : TI_TUNIQUE_ROUGE));

        addObject(new Coffre(9 * 16 + 8, 51 * 16, 0, scene->getCoffre(12, 4), TI_CLE, 4));
        addObject(new Coffre(69 * 16 + 8, 2 * 16, 0, scene->getCoffre(12, 5), TI_CLE, 5));
        addObject(new Coffre(69 * 16 + 8, 77 * 16, 0, scene->getCoffre(12, 6), TI_CLE, 6));
        addObject(new Coffre(129 * 16 + 8, 51 * 16, 0, scene->getCoffre(12, 7), TI_CLE, 7));
        addObject(new Coffre(329 * 16 + 8, 19 * 16, 0, scene->getCoffre(12, 8), TI_CLE, 8));

        if (scene->getCoffre(12, 9))
            ouvrePorte(29, 43, 0);
        if (scene->getCoffre(12, 10))
            ouvrePorte(58, 96, 1);
        if (scene->getCoffre(12, 11))
            ouvrePorte(78, 96, 1);
        if (scene->getCoffre(12, 12))
            ouvrePorte(109, 43, 0);
        if (scene->getCoffre(12, 13))
            ouvrePorte(289, 28, 0);
        if (scene->getCoffre(12, 14))
            ouvrePorte(9, 58, 0);
        if (scene->getCoffre(12, 15))
            ouvrePorte(29, 58, 0);
        if (scene->getCoffre(12, 16))
            ouvrePorte(49, 88, 0);
        if (scene->getCoffre(12, 17))
            ouvrePorte(58, 21, 1);
        if (scene->getCoffre(12, 18))
            ouvrePorte(69, 28, 0);
        if (scene->getCoffre(12, 19))
            ouvrePorte(69, 13, 0);
        if (scene->getCoffre(12, 20))
            ouvrePorte(78, 21, 1);
        if (scene->getCoffre(12, 21))
            ouvrePorte(89, 58, 0);
        if (scene->getCoffre(12, 22))
            ouvrePorte(89, 88, 0);
        if (scene->getCoffre(12, 23))
            ouvrePorte(109, 58, 0);
        if (scene->getCoffre(12, 24))
            ouvrePorte(118, 21, 1);
        if (scene->getCoffre(12, 25))
            ouvrePorte(58, 66, 1);
        if (scene->getCoffre(12, 26))
            ouvrePorte(78, 66, 3);

        addObject(new Interrupteur(16 * 16, 67 * 16, 0, scene->getCoffre(12, 14), map));
        addObject(new Interrupteur(36 * 16, 52 * 16, 0, scene->getCoffre(12, 15), map));
        addObject(new Interrupteur(55 * 16, 85 * 16, 0, scene->getCoffre(12, 16), map));
        addObject(new Interrupteur(52 * 16, 18 * 16, 0, scene->getCoffre(12, 17), map));
        addObject(new Interrupteur(63 * 16, 22 * 16, 0, scene->getCoffre(12, 18), map));
        addObject(new Interrupteur(76 * 16, 22 * 16, 0, scene->getCoffre(12, 19), map));
        addObject(new Interrupteur(87 * 16, 26 * 16, 0, scene->getCoffre(12, 20), map));
        addObject(new Interrupteur(87 * 16, 71 * 16, 0, scene->getCoffre(12, 21), map));
        addObject(new Interrupteur(96 * 16, 82 * 16, 0, scene->getCoffre(12, 22), map));
        addObject(new Interrupteur(103 * 16, 52 * 16, 0, scene->getCoffre(12, 23), map));
        addObject(new Interrupteur(112 * 16, 26 * 16, 0, scene->getCoffre(12, 24), map));
        addObject(new Interrupteur(76 * 16, 67 * 16, 0, scene->getCoffre(12, 25), map));

        addObject(new PiegeMain(62 * 16, 47 * 16));
        addObject(new PiegeMain(62 * 16, 32 * 16));
        addObject(new PiegeMain(62 * 16, 2 * 16));
        addObject(new PiegeMain(42 * 16, 32 * 16));
        addObject(new PiegeMain(22 * 16, 47 * 16));
        addObject(new PiegeMain(102 * 16, 47 * 16));

        addObject(new PiegeDemi(2 * 16, 32 * 16));
        addObject(new PiegeDemi(2 * 16, 42 * 16));
        addObject(new PiegeDemi(39 * 16 + 8, 94 * 16));
        addObject(new PiegeDemi(100 * 16, 94 * 16));
        addObject(new PiegeDemi(9 * 16 + 8, 67 * 16));
        addObject(new PiegeDemi(82 * 16, 47 * 16));
        addObject(new PiegeDemi(97 * 16, 47 * 16));
        addObject(new PiegeDemi(99 * 16 + 8, 20 * 16));

        addEnnemi(new Ennemi016(49 * 16 + 8, 37 * 16 - 8));
        addEnnemi(new Ennemi016(38 * 16 + 8, 20 * 16));
        addEnnemi(new Ennemi016(40 * 16, 22 * 16 - 8));
        addEnnemi(new Ennemi016(41 * 16 + 8, 23 * 16));
        addEnnemi(new Ennemi016(29 * 16 + 8, 52 * 16 - 8));
        addEnnemi(new Ennemi016(69 * 16 + 8, 22 * 16 - 8));
        addEnnemi(new Ennemi016(109 * 16 + 8, 52 * 16 - 8));
        addEnnemi(new Ennemi016(89 * 16 + 8, 52 * 16 - 8));
        addEnnemi(new Ennemi016(98 * 16 + 8, 35 * 16 - 8));
        addEnnemi(new Ennemi016(100 * 16, 37 * 16 - 8));
        addEnnemi(new Ennemi016(101 * 16 + 8, 39 * 16 - 8));

        addEnnemi(new Ennemi056(65 * 16 - 1, 94 * 16 - 1));
        addEnnemi(new Ennemi056(74 * 16 - 1, 94 * 16 - 1));
        addEnnemi(new Ennemi056(29 * 16 - 1 + 8, 97 * 16 - 1));
        addEnnemi(new Ennemi056(49 * 16 - 1 + 8, 97 * 16 - 1));
        addEnnemi(new Ennemi056(89 * 16 - 1 + 8, 97 * 16 - 1));
        addEnnemi(new Ennemi056(109 * 16 - 1 + 8, 97 * 16 - 1));
        addEnnemi(new Ennemi056(30 * 16 - 1, 69 * 16 - 1));
        addEnnemi(new Ennemi056(51 * 16 - 1, 69 * 16 - 1));
        addEnnemi(new Ennemi056(40 * 16 - 1, 82 * 16 - 1));
        addEnnemi(new Ennemi056(11 * 16 - 1, 81 * 16 - 1));
        addEnnemi(new Ennemi056(7 * 16 - 1, 50 * 16 - 1));
        addEnnemi(new Ennemi056(12 * 16 - 1, 50 * 16 - 1));
        addEnnemi(new Ennemi056(65 * 16 - 1, 80 * 16 - 1));
        addEnnemi(new Ennemi056(74 * 16 - 1, 80 * 16 - 1));
        addEnnemi(new Ennemi056(11 * 16 - 1, 23 * 16 - 1));
        addEnnemi(new Ennemi056(29 * 16 - 1 + 8, 38 * 16 - 1));
        addEnnemi(new Ennemi056(49 * 16 - 1, 6 * 16 - 1));
        addEnnemi(new Ennemi056(90 * 16 - 1, 6 * 16 - 1));
        addEnnemi(new Ennemi056(30 * 16 - 1, 7 * 16 - 1));
        addEnnemi(new Ennemi056(89 * 16 - 1 + 8, 82 * 16 - 1));
        addEnnemi(new Ennemi056(85 * 16 - 1, 65 * 16 - 1));
        addEnnemi(new Ennemi056(94 * 16 - 1, 65 * 16 - 1));
        addEnnemi(new Ennemi056(108 * 16 - 1, 73 * 16 - 1));
        addEnnemi(new Ennemi056(115 * 16 - 1, 85 * 16 - 1));
        addEnnemi(new Ennemi056(122 * 16 - 1, 68 * 16 - 1));
        addEnnemi(new Ennemi056(130 * 16 - 1, 80 * 16 - 1));
        addEnnemi(new Ennemi056(127 * 16 - 1, 50 * 16 - 1));
        addEnnemi(new Ennemi056(132 * 16 - 1, 50 * 16 - 1));
        addEnnemi(new Ennemi056(109 * 16 - 1, 8 * 16 - 1));
        addEnnemi(new Ennemi056(90 * 16 - 1, 23 * 16 - 1));
        addEnnemi(new Ennemi056(109 * 16 - 1, 23 * 16 - 1));
        addEnnemi(new Ennemi056(289 * 16 - 1, 37 * 16 - 1));
        addEnnemi(new Ennemi056(329 * 16 - 1, 37 * 16 - 1));

        addEnnemi(new Ennemi062(49 * 16 + 4, 51 * 16, false));
        addEnnemi(new Ennemi062(6 * 16 + 4, 37 * 16, false));
        addEnnemi(new Ennemi062(129 * 16 + 4, 22 * 16, false));
        addEnnemi(new Ennemi062(129 * 16 + 4, 37 * 16, false));

        addObject(new Jarre(22 * 16, 34 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(25 * 16, 34 * 16, 1, TI_BOMBE, map));
        addObject(new Jarre(34 * 16, 34 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(37 * 16, 34 * 16, 1, TI_RUBIS_ROUGE, map));
        addObject(new Jarre(56 * 16, 71 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(57 * 16, 71 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(134 * 16, 80 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(135 * 16, 80 * 16, 1, TI_FLECHE, map));
        addObject(new Jarre(136 * 16, 80 * 16, 1, TI_NO_ITEM, map));
        addObject(new Jarre(137 * 16, 80 * 16, 1, TI_NO_ITEM, map));
        break;
    case 27:
        if (!inventory->hasCoeur(12))
        {
            addEnnemi(new Ennemi076(28 * 16 + 2, 47 * 16 - 3));
        }

        addObject(new Coffre(170 * 16, 67 * 16, 0, scene->getCoffre(13, 0), TI_CARTE_DONJON));
        addObject(new Coffre(149 * 16 + 8, 52 * 16, 0, scene->getCoffre(13, 1), TI_BOUSSOLE));
        addObject(new Coffre(9 * 16 + 8, 7 * 16, 0, scene->getCoffre(13, 2), TI_CLE_BOSS));
        if (scene->getCoffre(13, 2) == 2)
            ouvrePorte(29, 58, 0);

        addObject(new Coffre(29 * 16, 36 * 16 + 8, 1, inventory->hasObject(ARC_FEE), TI_ARC_FEE));

        addObject(new Coffre(9 * 16, 67 * 16, 0, scene->getCoffre(13, 4), TI_CLE, 4));
        addObject(new Coffre(9 * 16, 127 * 16, 0, scene->getCoffre(13, 5), TI_CLE, 5));
        addObject(new Coffre(29 * 16 + 8, 82 * 16, 0, scene->getCoffre(13, 6), TI_CLE, 6));
        addObject(new Coffre(149 * 16 + 8, 82 * 16, 0, scene->getCoffre(13, 7), TI_CLE, 7));

        if (scene->getCoffre(13, 8))
            ouvrePorte(38, 126, 1);
        if (scene->getCoffre(13, 9))
            ouvrePorte(89, 103, 0);
        if (scene->getCoffre(13, 10))
            ouvrePorte(109, 43, 0);
        if (scene->getCoffre(13, 11))
            ouvrePorte(158, 66, 1);
        if (scene->getCoffre(13, 12))
            ouvrePorte(29, 73, 0);
        if (scene->getCoffre(13, 13))
            ouvrePorte(29, 118, 0);
        if (scene->getCoffre(13, 14))
            ouvrePorte(38, 66, 1);
        if (scene->getCoffre(13, 15))
            ouvrePorte(38, 111, 1);
        if (scene->getCoffre(13, 16))
            ouvrePorte(109, 58, 2);
        if (scene->getCoffre(13, 17))
            ouvrePorte(149, 58, 2);
        if (scene->getCoffre(13, 18))
            ouvrePorte(149, 73, 2);

        addObject(new Interrupteur(26 * 16, 71 * 16, 0, scene->getCoffre(13, 12), map));
        addObject(new Interrupteur(26 * 16, 116 * 16, 0, scene->getCoffre(13, 13), map));
        addObject(new Interrupteur(43 * 16, 71 * 16, 0, scene->getCoffre(13, 14), map));
        addObject(new Interrupteur(56 * 16, 108 * 16, 0, scene->getCoffre(13, 15), map));

        addObject(new PiegeDemi(22 * 16, 47 * 16));
        addObject(new PiegeDemi(37 * 16, 47 * 16));

        addEnnemi(new Ennemi044(25 * 16 - 3, 124 * 16 - 10));
        addEnnemi(new Ennemi044(34 * 16 - 3, 124 * 16 - 10));
        addEnnemi(new Ennemi044(13 * 16 - 3, 123 * 16 - 10));
        addEnnemi(new Ennemi044(13 * 16 - 3, 131 * 16 - 10));
        addEnnemi(new Ennemi044(13 * 16 - 3, 63 * 16 - 10));
        addEnnemi(new Ennemi044(13 * 16 - 3, 71 * 16 - 10));
        addEnnemi(new Ennemi044(52 * 16 - 3, 130 * 16 - 10));
        addEnnemi(new Ennemi044(47 * 16 - 3, 112 * 16 - 10));
        addEnnemi(new Ennemi044(70 * 16 - 3, 116 * 16 - 10));
        addEnnemi(new Ennemi044(94 * 16 - 3, 112 * 16 - 10));
        addEnnemi(new Ennemi044(24 * 16 - 3, 97 * 16 - 10));
        addEnnemi(new Ennemi044(29 * 16 - 3, 101 * 16 - 10));
        addEnnemi(new Ennemi044(35 * 16 - 3, 97 * 16 - 10));
        addEnnemi(new Ennemi044(36 * 16 - 3, 5 * 16 - 10));
        addEnnemi(new Ennemi044(44 * 16 - 3, 5 * 16 - 10));
        addEnnemi(new Ennemi044(25 * 16 - 3, 14 * 16 - 10));
        addEnnemi(new Ennemi044(35 * 16 - 3, 14 * 16 - 10));
        addEnnemi(new Ennemi044(44 * 16 - 3, 14 * 16 - 10));
        addEnnemi(new Ennemi044(54 * 16 - 3, 14 * 16 - 10));
        addEnnemi(new Ennemi044(35 * 16 - 3, 24 * 16 - 10));
        addEnnemi(new Ennemi044(44 * 16 - 3, 24 * 16 - 10));
        addEnnemi(new Ennemi044(49 * 16 - 3, 67 * 16 - 10));
        addEnnemi(new Ennemi044(78 * 16 - 3, 63 * 16 - 10));
        addEnnemi(new Ennemi044(84 * 16 - 3, 67 * 16 - 10));
        addEnnemi(new Ennemi044(78 * 16 - 3, 70 * 16 - 10));
        addEnnemi(new Ennemi044(100 * 16 - 3, 97 * 16 - 10));
        addEnnemi(new Ennemi044(109 * 16 - 3 + 8, 67 * 16 - 10));
        addEnnemi(new Ennemi044(105 * 16 - 3, 50 * 16 - 10));
        addEnnemi(new Ennemi044(114 * 16 - 3, 50 * 16 - 10));
        addEnnemi(new Ennemi044(164 * 16 - 3, 63 * 16 - 10));
        addEnnemi(new Ennemi044(164 * 16 - 3, 71 * 16 - 10));
        addEnnemi(new Ennemi044(134 * 16 - 3, 67 * 16 - 10));
        addEnnemi(new Ennemi044(149 * 16 - 3, 67 * 16 - 10));
        addEnnemi(new Ennemi044(77 * 16 - 3, 22 * 16 - 10));
        addEnnemi(new Ennemi044(98 * 16 - 3, 37 * 16 - 10));
        break;
    case 28:
        if (!scene->getCoffre(14, 13))
        {
            addEnnemi(new Ennemi031(49 * 16, 122 * 16));
        }
        addEnnemi(new Ennemi050(149 * 16 - 10, 109 * 16 - 4 + 8));

        addObject(new Coffre(29 * 16 + 8, 111 * 16 + 8, 0, scene->getCoffre(14, 0), TI_CARTE_DONJON));
        addObject(new Coffre(109 * 16 + 8, 37 * 16, 0, scene->getCoffre(14, 1), TI_BOUSSOLE));
        addObject(new Coffre(149 * 16 + 8, 37 * 16, 0, scene->getCoffre(14, 2), TI_CLE_BOSS));
        if (scene->getCoffre(14, 2) == 2)
            ouvrePorte(49, 133, 0);

        addObject(new Coffre(69 * 16 + 8, 111 * 16 + 8, 0, scene->getCoffre(14, 4), TI_CLE, 4));
        addObject(new Coffre(189 * 16 + 8, 37 * 16, 0, scene->getCoffre(14, 6), TI_CLE, 6));

        if (scene->getCoffre(14, 7))
            ouvrePorte(49, 58, 0);
        if (scene->getCoffre(14, 8))
            ouvrePorte(78, 96, 1);
        if (scene->getCoffre(14, 9))
            ouvrePorte(138, 66, 1);
        if (scene->getCoffre(14, 10))
            ouvrePorte(58, 66, 1);
        if (scene->getCoffre(14, 11))
            ouvrePorte(58, 141, 1);
        if (scene->getCoffre(14, 12))
            ouvrePorte(158, 51, 1);
        if (scene->getCoffre(14, 13))
            ouvrePorte(49, 118, 0);

        addObject(new Interrupteur(72 * 16, 69 * 16, 0, scene->getCoffre(14, 10), map));
        addObject(new Interrupteur(69 * 16, 146 * 16, 0, scene->getCoffre(14, 11), map));
        addObject(new Interrupteur(163 * 16, 55 * 16, 0, scene->getCoffre(14, 12), map));

        addObject(new PiegeDemi(34 * 16, 17 * 16));
        addObject(new PiegeDemi(65 * 16, 17 * 16));
        addObject(new PiegeDemi(44 * 16, 57 * 16));
        addObject(new PiegeDemi(55 * 16, 57 * 16));

        addEnnemi(new Ennemi046(45 * 16 - 3, 138 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(54 * 16 - 3, 138 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(29 * 16 - 3 + 8, 142 * 16 - 11));
        addEnnemi(new Ennemi046(15 * 16 - 3, 126 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(24 * 16 - 3, 126 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(6 * 16 - 3, 103 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(13 * 16 - 3, 103 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(29 * 16 - 3 + 8, 95 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(28 * 16 - 3, 80 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(51 * 16 - 3, 95 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(51 * 16 - 3, 82 * 16 - 11));
        addEnnemi(new Ennemi046(66 * 16 - 3, 89 * 16 + 8 - 11));
        addEnnemi(new Ennemi046(73 * 16 - 3, 89 * 16 + 8 - 11));

        addEnnemi(new Ennemi047(9 * 16 - 3 + 8, 106 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(69 * 16 - 3 + 8, 86 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(86 * 16 - 3, 104 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(93 * 16 - 3, 104 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(79 * 16 - 3, 126 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(65 * 16 - 3, 141 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(149 * 16 - 3 + 8, 67 * 16 - 11));
        addEnnemi(new Ennemi047(146 * 16 - 3, 49 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(153 * 16 - 3, 49 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(129 * 16 - 3 + 8, 52 * 16 - 11));
        addEnnemi(new Ennemi047(169 * 16 - 3 + 8, 52 * 16 - 11));
        addEnnemi(new Ennemi047(126 * 16 - 3, 27 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(133 * 16 - 3, 27 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(166 * 16 - 3, 30 * 16 + 8 - 11));
        addEnnemi(new Ennemi047(173 * 16 - 3, 30 * 16 + 8 - 11));

        addEnnemi(new Ennemi048(149 * 16 - 3 + 8, 22 * 16 - 11));
        addEnnemi(new Ennemi048(129 * 16 - 3 + 8, 32 * 16 + 8 - 11));
        addEnnemi(new Ennemi048(169 * 16 - 3 + 8, 27 * 16 + 8 - 11));
        addEnnemi(new Ennemi048(104 * 16 - 3, 37 * 16 - 11));
        addEnnemi(new Ennemi048(195 * 16 - 3, 37 * 16 - 11));
        addEnnemi(new Ennemi048(149 * 16 - 3 + 8, 5 * 16 + 8 - 11));
        addEnnemi(new Ennemi048(49 * 16 - 3 + 8, 67 * 16 - 11));
        addEnnemi(new Ennemi048(39 * 16 - 3, 51 * 16 + 8 - 11));
        addEnnemi(new Ennemi048(60 * 16 - 3, 51 * 16 + 8 - 11));
        addEnnemi(new Ennemi048(49 * 16 - 3 + 8, 22 * 16 + 8 - 11));
        addEnnemi(new Ennemi048(49 * 16 - 3 + 8, 37 * 16 - 11));
        addEnnemi(new Ennemi048(69 * 16 - 3 + 8, 67 * 16 - 11));
        addEnnemi(new Ennemi048(6 * 16 - 3, 37 * 16 - 11));
        addEnnemi(new Ennemi048(13 * 16 - 3, 37 * 16 - 11));
        addEnnemi(new Ennemi048(49 * 16 - 3 + 8, 7 * 16 - 11));
        addEnnemi(new Ennemi048(86 * 16 - 3, 37 * 16 - 11));
        addEnnemi(new Ennemi048(93 * 16 - 3, 37 * 16 - 11));
        break;
    case 29:
        addObject(new Pancarte(16 * 9, 16 * 21, 368, map));
        addObject(new Jarre(8 * 16, 27 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(8 * 16, 26 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(9 * 16, 26 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(10 * 16, 26 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(11 * 16, 26 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(11 * 16, 27 * 16, 0, TI_NO_ITEM, map));
        addObject(new Coffre(9 * 16 + 8, 37 * 16, 0, link->getBouclier(), TI_BOUCLIER_1));
        break;
    case 30:
        addObject(new Pnj(16 * 9, 16 * 4 + 8, 16, 369));
        break;
    case 31:
        if (!inventory->hasQuartCoeur(14))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 10 * 16, 4 * 16 + 8, 14));
        }
        break;
    case 32:
        addObject(new Coffre(9 * 16 + 8, 5 * 16, 0, link->getInventory()->hasObject(OCARINA), TI_OCARINA));
        break;
    case 35:
        addObject(new Coffre(9 * 16 + 8, 5 * 16, 0, link->getInventory()->hasObject(LANTERNE), TI_LANTERNE));
        break;
    case 36:
        addObject(new Coffre(9 * 16 + 8, 5 * 16, 0, link->getInventory()->hasObject(MASQUE_VIDE), TI_MASQUE_VIDE));
        break;
    case 39:
        addObject(new Pnj(16 * 9, 16 * 4 + 8, 48, 372));
        break;
    case 41:
        addObject(new Coffre(9 * 16 + 8, 19 * 16, 0, link->getInventory()->hasObject(FLACON_3), TI_FLACON_3));
        addEnnemi(new Ennemi021(67 * 16, 10 * 16 + 1));
        addEnnemi(new Ennemi021(81 * 16, 6 * 16 + 1));
        addEnnemi(new Ennemi037(49 * 16 + 8, 22 * 16 - 10));
        addEnnemi(new Ennemi037(5 * 16, 6 * 16 - 10));
        addEnnemi(new Ennemi037(14 * 16, 6 * 16 - 10));
        addEnnemi(new Ennemi038(45 * 16 - 3, 4 * 16 - 9));
        addEnnemi(new Ennemi038(54 * 16 - 3, 4 * 16 - 9));
        addEnnemi(new Ennemi039(49 * 16 - 4 + 8, 8 * 16 - 9));
        break;
    case 42:
        addObject(new Coffre(9 * 16 + 8, 5 * 16, 0, link->getInventory()->hasObject(GANTS_2), TI_GANT2));
        break;
    case 43:
        if (scene->getAvancement() == AV_PASSE_ONI)
        {
            scene->setAvancement(AV_ARMEE_DOWN);
        }
        if (scene->getAvancement() == AV_PASSE_OK)
        {
            addObject(new Pnj(16 * 13, 16 * 5, 49, 380));
            addObject(new Pnj(16 * 6, 16 * 5, 50, 381));
        }
        else
        {
            addObject(new Pnj(16 * 12, 16 * 6, 49, 380));
            addObject(new Pnj(16 * 7, 16 * 6, 50, 381));
        }
        break;
    case 44:
        if (scene->getAvancement() < AV_ZELDA_CHEZ_PIT)
        {
            addObject(new Pnj(16 * 9 + 8, 16 * 6, 47, 385));
        }
        else
        {
            addObject(new Pnj(16 * 7 + 8, 16 * 5, 47, 385));
            addObject(new Pnj(16 * 11 + 8, 16 * 5, 15, 400));
        }
        addObject(new Jarre(4 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(5 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        break;
    case 45:
        if (scene->getCoffre(0, 13) == 2)
        { // getCoffre(0, 14) -> alreadyPaid for monsters
            ouvrePorte(29, 0, 0);
        }
        addObject(new Pnj(16 * 9, 16 * 5, 8, 425));
        break;
    case 46:
        if (link->getInventory()->hasObject(BOMBES))
        {
            addObject(new Pnj(16 * 12, 16 * 8, 43, 441));
        }
        break;
    case 47:
        // coeurs 15
        addObject(new Pnj(16 * 14, 16 * 11 - 10, 20, 442));
        addObject(new Coffre(6 * 16, 6 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(8 * 16, 6 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(10 * 16, 6 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(6 * 16, 8 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(8 * 16, 8 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(10 * 16, 8 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(6 * 16, 10 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(8 * 16, 10 * 16, 0, true, TI_NO_ITEM));
        addObject(new Coffre(10 * 16, 10 * 16, 0, true, TI_NO_ITEM));
        break;
    case 48:
        addObject(new Pnj(16 * 8, 16 * 4, 18, 447));
        addObject(new TalkableArea(16 * 8, 16 * 6, 447));
        addObject(new Pnj(16 * 24, 16 * 4, 14, 449));
        addObject(new Jarre(4 * 16, 7 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(13 * 16, 4 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(20 * 16, 12 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(21 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        break;
    case 49:
        addObject(new Pnj(16 * 29 + 8, 16 * 4, 51, 450));
        break;
    case 50:
        addObject(new TalkableArea(16 * 5, 16 * 6, 456));
        addObject(new TalkableArea(16 * 8, 16 * 6, 459));
        addObject(new TalkableArea(16 * 11, 16 * 6, 461));
        addObject(new Pnj(16 * 13, 16 * 9, 12, 463));
        break;
    case 51:
        addObject(new Pnj(16 * 13, 16 * 9, 10, 463));
        addObject(new TalkableArea(16 * 7, 16 * 6, 464));
        addObject(new TalkableArea(16 * 10, 16 * 6, 466));
        if (link->getInventory()->hasObject(ARC_FEE))
        {
            map->setSol(7 * 16, 5 * 16, 4287);
        }
        break;
    case 52:
        addObject(new Pnj(16 * 9 + 7, 16 * 7, 17, 469));
        break;
    case 53:
        addObject(new Coffre(4 * 16, 2 * 16, 0, link->getInventory()->hasObject(FLACON_2), TI_FLACON_2));
        addObject(new Pnj(16 * 8, 16 * 4, 18, 447));
        addObject(new TalkableArea(16 * 8, 16 * 6, 447));
        addObject(new Pnj(16 * 13, 16 * 16 + 8, 19, 480));
        if (scene->getAvancement() >= AV_ZELDA_CHEZ_PIT && scene->getAvancement() < AV_FILLE_MAIRE_SAUVEE)
        {
            addObject(new Pnj(16 * 5, 16 * 24, 11, 231));
            addObject(new Pnj(16 * 14, 16 * 26, 35, 234));
            addObject(new Pnj(16 * 9, 16 * 9, 36, 235));
        }
        addObject(new Jarre(4 * 16, 27 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(5 * 16, 27 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(15 * 16, 2 * 16, 0, TI_RUBIS_BLEU, map));
        break;
    case 54:
        addObject(new Pnj(16 * 9, 16 * 5, 52, 483));
        break;
    case 55:
        addObject(new Pnj(16 * 29, 16 * 6, 25, 489));
        if (scene->getAvancement() >= AV_FILLE_MAIRE_SAUVEE)
        {
            addObject(new Pnj(16 * 9, 16 * 6, 45, 501));
        }
        addObject(new Jarre(16 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        addObject(new Jarre(17 * 16, 12 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(22 * 16, 12 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(23 * 16, 12 * 16, 0, TI_NO_ITEM, map));
        break;
    case 56:
        addObject(new Pnj(16 * 9 + 7, 16 * 7, 17, 469));
        break;
    case 57:
        if (scene->getAvancement() >= AV_ZELDA_CHEZ_PIT && scene->getAvancement() < AV_FILLE_MAIRE_SAUVEE)
        {
            addObject(new Pnj(16 * 11 + 8, 16 * 8, 9, 230));
        }
        addObject(new Jarre(14 * 16, 12 * 16, 0, TI_RUBIS_VERT, map));
        addObject(new Jarre(15 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        break;
    case 58:
        if (scene->getAvancement() >= AV_ZELDA_CHEZ_PIT && scene->getAvancement() < AV_FILLE_MAIRE_SAUVEE)
        {
            addObject(new Pnj(16 * 11, 16 * 7 + 4, 34, 232));
        }
        break;
    case 59:
        addObject(new TalkableArea(16 * 5, 16 * 6, 456));
        addObject(new TalkableArea(16 * 8, 16 * 6, 459));
        addObject(new TalkableArea(16 * 11, 16 * 6, 461));
        addObject(new Pnj(16 * 13, 16 * 9, 20, 463));
        break;
    case 60:
        addObject(new Pnj(16 * 13, 16 * 9, 7, 463));
        addObject(new TalkableArea(16 * 7, 16 * 6, 464));
        addObject(new TalkableArea(16 * 10, 16 * 6, 466));
        if (link->getInventory()->hasObject(ARC_FEE))
        {
            map->setSol(7 * 16, 5 * 16, 4287);
        }
        break;
    case 61:
        addObject(new Pnj(16 * 9, 16 * 8 - 3, 28, 502));
        map->setSol(16 * 9, 16 * 9, map->getSol(16 * 9, 16 * 9), MURRET);
        break;
    case 62:
        addObject(new Pnj(16 * 12, 16 * 7, 29, 504));
        break;
    case 63:
        addObject(new Pnj(16 * 8, 16 * 7, 31, 507));
        break;
    case 64:
        addObject(new Pnj(16 * 7, 16 * 8, 30, 509));
        break;
    case 65:
        addObject(new TalkableArea(16 * 5, 16 * 6, 456));
        addObject(new TalkableArea(16 * 8, 16 * 6, 459));
        addObject(new TalkableArea(16 * 11, 16 * 6, 461));
        addObject(new Pnj(16 * 13, 16 * 9, 27, 463));
        break;
    case 66:
        addObject(new Pnj(16 * 10, 16 * 6 - 1, 53, 511));
        break;
    case 67:
        addObject(new Jarre(4 * 16, 12 * 16, 0, TI_PETIT_COEUR, map));
        addObject(new Jarre(5 * 16, 12 * 16, 0, TI_MAGIE_PEU, map));
        addObject(new Pnj(16 * 8, 16 * 5, 21, 516));
        break;
    case 68:
        addObject(new Pnj(16 * 9, 16 * 7, 54, 523));
        break;
    case 69:
        addObject(new TalkableArea(16 * 5, 16 * 6, 456));
        addObject(new TalkableArea(16 * 7, 16 * 6, 459));
        addObject(new TalkableArea(16 * 9, 16 * 6, 461));
        addObject(new TalkableArea(16 * 11, 16 * 6, 464));
        addObject(new TalkableArea(16 * 13, 16 * 6, 466));
        if (link->getInventory()->hasObject(ARC_FEE))
        {
            map->setSol(11 * 16, 5 * 16, 4287);
        }
        addObject(new Pnj(16 * 13, 16 * 9, 7, 463));
        break;
    case 70:
        addObject(new Pnj(16 * 9 + 7, 16 * 7, 17, 469));
        break;
    case 71:
        addObject(new Pnj(16 * 9 + 7, 16 * 5, 55, 524));
        break;
    }
}
