/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __COMMONGAME_H__
#define __COMMONGAME_H__

#define MAX_CASE_X 400
#define MAX_CASE_Y 400

#define ANIM_REFRESH 120 // intervale entre les anims

#define NB_QUART_COEUR 16
#define NB_FLACON 3
#define NB_GRAALS 5
#define NB_COFFRES 15
#define COFFRES_MAX_SIZE 60
#define NB_COEUR 13
#define NB_DONJON 14
#define NB_MONSTERS 77
#define MAX_ROOMS_X 20
#define MAX_ROOMS_Y 20

#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../../config/AudioHelper.h"

using namespace std;

enum Direction
{
    N,
    S,
    W,
    E
};

enum Animation
{
    IDLE,
    WALK,
    PUSH,
    TOUCHE,
    FLOTTE,
    NAGE,
    COULE,
    CHUTE,
    HIT_EPEE,
    SPIN_EPEE,
    NOYE,
    MORT,
    TROUVE_SIMPLE,
    TROUVE_DOUBLE,
    TIR_ARC,
    PORTE,
    TRANSPORTE,
    THROW,
    SOULEVE,
    TIR_GRAPPIN,
    TIR_BAGUETTE_FEU,
    TIR_BAGUETTE_GLACE,
    TIR_LANTERNE,
    TIR_MARTEAU,
    BOIT_POTION,
    JOUE_OCARINA,
    ELECTRIC
};

enum Collision
{
    TROU = -1,
    HERBE = 0,
    HERBE_HAUTE,
    TERRE,
    GLACE,
    MURRET,
    MUR,
    EAU,
    EAU_PROF,
    MUR_H,
    MUR_B,
    MUR_G,
    MUR_D,
    MUR_HG,
    MUR_HD,
    MUR_BG,
    MUR_BD,
    BOIS,
    SABLE,
    NEIGE,
    PIERRE,
    SOL_BOIS,
    TAPIS,
    DANGER,
    DANGER_BAS,
    GRAND_MUR
};

enum Equipment
{
    ARC,
    ARC_FEE,
    PALMES,
    BOMBES,
    LANTERNE,
    GRAPPIN,
    BAGUETTE_FEU,
    BAGUETTE_GLACE,
    MARTEAU,
    MASQUE,
    MASQUE_VIDE,
    FLACON_1,
    FLACON_2,
    FLACON_3,
    GANTS,
    GANTS_2,
    OCARINA,
    CHANT_1,
    CHANT_2,
    CHANT_3,
    BOTTES,
    ENCYCLOPEDIE,
    CARTE,
    TRIFORCE,
    NB_EQPMT
};

enum TypeAttack
{
    TA_PHYSIC,
    TA_MAGIC,
    TA_SWORD,
    TA_SWORD_HOLD,
    TA_ARROW,
    TA_EXPLO,
    TA_GRAPPIN,
    TA_MARTEAU,
    TA_MASSIF,
    TA_NB_MAX
};

enum TypeEffect
{
    TE_NORMAL,
    TE_FEU,
    TE_GLACE,
    TE_GRAVITE,
    TE_QUASI_MORT,
    TE_MORT,
    TE_ELECTRIC,
    TE_LAPIN,
    TE_COLERE,
    TE_NB_MAX
};

enum TypeItem
{
    TI_PETIT_COEUR,
    TI_QUART_COEUR,
    TI_FLECHE,
    TI_BOMBE,
    TI_MAGIE_PEU,
    TI_MAGIE_BEAUCOUP,
    TI_RUBIS_VERT,
    TI_RUBIS_BLEU,
    TI_RUBIS_ROUGE,
    TI_FLACON_1,
    TI_FLACON_2,
    TI_FLACON_3,
    TI_BOUCLIER_1,
    TI_BOUCLIER_2,
    TI_BOUCLIER_3,
    TI_TUNIQUE_BLEUE,
    TI_TUNIQUE_ROUGE,
    TI_CHANT_1,
    TI_CHANT_2,
    TI_CHANT_3,
    TI_SAC_BOMBES,
    TI_EPEE_1,
    TI_EPEE_2,
    TI_EPEE_3,
    TI_EPEE_4,
    TI_EPEE_5,
    TI_GANT,
    TI_GANT2,
    TI_ARC,
    TI_ARC_FEE,
    TI_COEUR,
    TI_PALMES,
    TI_OCARINA,
    TI_MARTEAU,
    TI_LANTERNE,
    TI_MASQUE,
    TI_MASQUE_VIDE,
    TI_POTION_ROUGE,
    TI_POTION_VERTE,
    TI_POTION_BLEUE,
    TI_CARTE,
    TI_CARTE_DONJON,
    TI_BOUSSOLE,
    TI_CLE_BOSS,
    TI_CLE,
    TI_DOUBLE_MAGIE,
    TI_GRAPPIN,
    TI_BAGUETTE_FEU,
    TI_BAGUETTE_GLACE,
    TI_BOTTES,
    TI_INTERRUPTEUR,
    TI_GRAAL,
    TI_TRIFORCE,
    TI_NO_ITEM,
    TI_NB_MAX
};

enum TypeProjectile
{
    TP_ARROW,
    TP_ARROW_2,
    TP_BAGUETTE_FEU,
    TP_BAGUETTE_GLACE,
    TP_FEU_LONG_ENN,
    TP_BOULE_FEU,
    TP_ARC_MAGIQUE,
    TP_BOULET,
    TP_LAPIN,
    TP_ECLAIR,
    TP_BIG_FEU,
    TP_BIG_GLACE,
    TP_BOULE_DEMI,
    TP_BOULE_ULTIME,
    TP_BOULE_COLERE,
    TP_BOULE_MORT,
    TP_NB_MAX
};

enum Avancement
{
    AV_START,
    AV_INTRO_OK,
    AV_TUTO_OK,
    AV_PIT_A_VOIR,
    AV_PIT_VU,
    AV_AUTORISATION_SORTIE,
    AV_CHERCHE_BOMBES,
    AV_CHERCHE_MINE,
    AV_MINE_FERMEE,
    AV_HOMME_PIEGE_MINE,
    AV_AUTORISATION_MINE,
    AV_MINE_OUVERTE,
    AV_MAIRE_VU,
    AV_INFO_MAIRE_OK,
    AV_AUTORISATION_MANOIR,
    AV_MANOIR_OUVERT,
    AV_ONI_LINK_FREE,
    AV_ZELDA_CHEZ_PIT,
    AV_FILLE_MAIRE_SAUVEE,
    AV_SAGE_DESERT_VU,
    AV_GANON_VU,
    AV_ARMEE_UP,
    AV_ARMEE_DOWN,
    AV_PASSE_ONI,
    AV_PASSE_OK
};

#endif // CommonGame.h
