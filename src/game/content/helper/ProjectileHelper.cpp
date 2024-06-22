#include "ProjectileHelper.h"

#include "../../MainController.h"

#include "../projectiles/ProjArrow.h"
#include "../projectiles/ProjBaguetteFeu.h"
#include "../projectiles/ProjBaguetteGlace.h"
#include "../projectiles/ProjFeuLong.h"
#include "../projectiles/ProjBouleFeu.h"
#include "../projectiles/ProjBouleDemi.h"
#include "../projectiles/ProjBouleColere.h"
#include "../projectiles/ProjBouleMort.h"
#include "../projectiles/ProjArcMagique.h"
#include "../projectiles/ProjBigFeu.h"
#include "../projectiles/ProjBigGlace.h"
#include "../projectiles/ProjUltime.h"
#include "../projectiles/ProjBoulet.h"
#include "../projectiles/ProjLapin.h"
#include "../projectiles/ProjEclair.h"

ProjectileHelper ProjectileHelper::instance = ProjectileHelper();

ProjectileHelper::ProjectileHelper()
{
}

ProjectileHelper::~ProjectileHelper()
{
}

ProjectileHelper *ProjectileHelper::getInstance()
{
    return &instance;
}

void ProjectileHelper::addProjectile(TypeProjectile type, int x, int y, Direction dir)
{

    Projectile *proj;

    switch (type)
    {
    case TP_ARROW:
        proj = new ProjArrow(x, y, dir, 1);
        break;
    case TP_ARROW_2:
        proj = new ProjArrow(x, y, dir, 2);
        break;
    case TP_BAGUETTE_FEU:
        proj = new ProjBaguetteFeu(x, y, dir);
        break;
    case TP_BAGUETTE_GLACE:
        proj = new ProjBaguetteGlace(x, y, dir);
        break;
    case TP_FEU_LONG_ENN:
        proj = new ProjFeuLong(x, y, dir, false);
        break;
    case TP_ARC_MAGIQUE:
        proj = new ProjArcMagique(x, y, dir);
        break;
    case TP_BOULET:
        proj = new ProjBoulet(x, y, dir);
        break;
    case TP_ECLAIR:
        proj = new ProjEclair(x, y);
        break;
    default:
        return;
    }

    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addProjectile(proj);
}

void ProjectileHelper::addProjectile(TypeProjectile type, int x, int y, double dx, double dy, BoundingBox *safeBox)
{

    Projectile *proj;

    switch (type)
    {
    case TP_BOULE_FEU:
        proj = new ProjBouleFeu(x, y, dx, dy, safeBox);
        break;
    case TP_BOULE_DEMI:
        proj = new ProjBouleDemi(x, y, dx, dy, safeBox);
        break;
    case TP_BOULE_COLERE:
        proj = new ProjBouleColere(x, y, dx, dy, safeBox);
        break;
    case TP_BOULE_MORT:
        proj = new ProjBouleMort(x, y, dx, dy, safeBox);
        break;
    case TP_BIG_FEU:
        proj = new ProjBigFeu(x, y, dx, dy);
        break;
    case TP_BIG_GLACE:
        proj = new ProjBigGlace(x, y, dx, dy);
        break;
    case TP_LAPIN:
        proj = new ProjLapin(x, y, dx, dy);
        break;
    default:
        return;
    }

    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addProjectile(proj);
}
void ProjectileHelper::addProjectile(TypeProjectile type, int x, int y, Link *link)
{

    Projectile *proj;

    switch (type)
    {
    case TP_BOULE_ULTIME:
        proj = new ProjUltime(x, y, link);
        break;
    default:
        return;
    }

    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addProjectile(proj);
}
