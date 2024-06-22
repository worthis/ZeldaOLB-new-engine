#include "TextArea.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

#include "../../content/link/Link.h"

TextArea::TextArea() : step(TEXT_OFF), anim(0), animMax(0), vanim(40), ready(false), text(0), id(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/texts/cadre.png", true);
    imageCoeur = ResourceManager::getInstance()->loadImage("data/images/status/coeur.png", true);
}

TextArea::~TextArea()
{
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(imageCoeur);
    delete text;
}

void TextArea::handleActions(Action *action)
{
    if (action->isAction(ACTION))
    {
        if (ready)
        {
            if (text->hasNext())
            {
                text->next();
                start();
                AudioManager::getInstance()->playSound(TS_TEXTNEXT);
            }
            else if (hasLogicalNext())
            {
                start();
                AudioManager::getInstance()->playSound(TS_TEXTNEXT);
            }
            else
            {
                stop();
                AudioManager::getInstance()->playSound(TS_TEXTEND);
            }
        }
        else
        {
            anim = animMax;
            ready = true;
        }
        return;
    }
    if (ready)
    {
        if (action->isAction(PUSH_UP))
        {
            int newId = -1;
            switch (id)
            {
            case 93:
            case 284:
                newId = id + 2;
                break;
            case 94:
            case 95:
            case 283:
            case 285:
            case 286:
            case 288:
            case 289:
            case 290:
            case 317:
            case 319:
            case 472:
            case 473:
                newId = id - 1;
                break;
            case 282:
            case 316:
            case 318:
                newId = id + 1;
                break;
            case 287:
                newId = id + 3;
                break;
            case 471:
                newId = id + 2;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_DOWN))
        {
            int newId = -1;
            switch (id)
            {
            case 93:
            case 94:
            case 282:
            case 284:
            case 285:
            case 287:
            case 288:
            case 289:
            case 316:
            case 318:
            case 471:
            case 472:
                newId = id + 1;
                break;
            case 95:
            case 286:
                newId = id - 2;
                break;
            case 283:
            case 317:
            case 319:
                newId = id - 1;
                break;
            case 290:
                newId = id - 3;
                break;
            case 473:
                newId = id - 2;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_LEFT))
        {
            int newId = -1;
            switch (id)
            {
            case 188:
            case 224:
            case 373:
            case 435:
            case 443:
            case 452:
            case 456:
            case 459:
            case 461:
            case 464:
            case 466:
            case 474:
            case 476:
            case 502:
            case 511:
                newId = id + 1;
                break;
            case 189:
            case 225:
            case 374:
            case 436:
            case 444:
            case 453:
            case 457:
            case 460:
            case 462:
            case 465:
            case 467:
            case 475:
            case 477:
            case 503:
            case 512:
                newId = id - 1;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_RIGHT))
        {
            int newId = -1;
            switch (id)
            {
            case 188:
            case 224:
            case 373:
            case 435:
            case 443:
            case 452:
            case 456:
            case 459:
            case 461:
            case 464:
            case 466:
            case 474:
            case 476:
            case 502:
            case 511:
                newId = id + 1;
                break;
            case 189:
            case 225:
            case 374:
            case 436:
            case 444:
            case 453:
            case 457:
            case 460:
            case 462:
            case 465:
            case 467:
            case 475:
            case 477:
            case 503:
            case 512:
                newId = id - 1;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
    }
}

void TextArea::loop()
{
    if (!ready)
    {
        if (chrono.getElapsedTime() >= vanim)
        {
            do
            {
                ready = (++anim == animMax);
            } while (!ready && text->charAtInBox(anim) == ' ');
            AudioManager::getInstance()->playSound(TS_TEXT, 1);
            chrono.reset();
        }
    }
}

void TextArea::draw()
{
    WindowManager::getInstance()->draw(image, 0, 0, 8, 8, 8, 16 * 9 + 8);
    WindowManager::getInstance()->draw(image, 24, 0, 8, 8, 16 * 19, 16 * 9 + 8);
    WindowManager::getInstance()->draw(image, 0, 24, 8, 8, 8, 16 * 14);
    WindowManager::getInstance()->draw(image, 24, 24, 8, 8, 16 * 19, 16 * 14);

    for (int i = 16; i < 16 * 19; i += 16)
    {
        WindowManager::getInstance()->draw(image, 8, 0, 16, 8, i, 16 * 9 + 8);
        WindowManager::getInstance()->draw(image, 8, 24, 16, 8, i, 16 * 14);
    }

    for (int j = 16 * 10; j < 16 * 14; j += 16)
    {
        WindowManager::getInstance()->draw(image, 0, 8, 8, 16, 8, j);
        WindowManager::getInstance()->draw(image, 24, 8, 8, 16, 16 * 19, j);
    }

    text->displayBox(16, 16 * 10, anim);

    drawAdditionalContent();
}

void TextArea::start()
{
    chrono.reset();
    anim = 0;
    animMax = text->getLengthInBox();
    ready = false;
}

void TextArea::stop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map *map = scene->getMap();
    Link *link = scene->getLink();
    if (link->getAnimation() == TROUVE_SIMPLE || link->getAnimation() == TROUVE_DOUBLE)
    {
        link->setAnimation(IDLE);
    }
    int tmp = 0;

    switch (id)
    {
    case 94:
        MainController::getInstance()->getGameController()->saveData();
    case 95:
        AudioManager::getInstance()->stopMusic();
        MainController::getInstance()->setStep(LOGO);
        return;
    case 119:
        map->testAnimRoom();
        break;
    case 175:
        scene->setAvancement(AV_PIT_A_VOIR);
        break;
    case 191:
        link->trouveObjet(TI_FLACON_1);
        link->getStatus()->updateRupees(-100);
        return;
    case 195:
        if (scene->getAvancement() == AV_CHERCHE_BOMBES)
        {
            scene->setAvancement(AV_CHERCHE_MINE);
        }
        break;
    case 196:
        if (scene->getAvancement() == AV_AUTORISATION_SORTIE)
        {
            scene->setAvancement(AV_CHERCHE_BOMBES);
        }
        break;
    case 197:
        if (scene->getAvancement() == AV_CHERCHE_MINE)
        {
            scene->setAvancement(AV_MINE_FERMEE);
        }
        break;
    case 199:
        if (scene->getAvancement() == AV_AUTORISATION_MINE)
        {
            scene->setAvancement(AV_MINE_OUVERTE);
        }
        break;
    case 201:
        link->getStatus()->updateRupees(-5);
        break;
    case 223:
        if (scene->getAvancement() == AV_AUTORISATION_MANOIR)
        {
            scene->setAvancement(AV_MANOIR_OUVERT);
        }
        break;
    case 226:
        link->trouveObjet(TI_BOUCLIER_2);
        link->getStatus()->updateRupees(-250);
        return;
    case 247:
        scene->setAvancement(AV_ARMEE_DOWN);
        break;
    case 276:
        scene->setCoffre(0, 16, 1);
        break;
    case 281:
    case 283:
    case 286:
    case 290:
        link->setAnimation(IDLE);
        break;
    case 282:
    case 285:
    case 288:
        link->setAnimation(JOUE_OCARINA);
        MainController::getInstance()->getGameController()->getOcarinaController()->setSong(0);
        MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
        return;
    case 284:
    case 287:
        link->setAnimation(JOUE_OCARINA);
        MainController::getInstance()->getGameController()->getOcarinaController()->setSong(1);
        MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
        return;
    case 289:
        link->setAnimation(JOUE_OCARINA);
        MainController::getInstance()->getGameController()->getOcarinaController()->setSong(2);
        MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
        return;
    case 293:
        tmp = map->getId();
        if (tmp == 3 || (tmp >= 46 && tmp <= 52))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 39 * 16, 54 * 16 + 8, S, false, true);
        }
        else if (tmp == 7 || (tmp >= 53 && tmp <= 60))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 39 * 16, 42 * 16 + 8, S, false, true);
        }
        else if (tmp == 11 || (tmp >= 62 && tmp <= 66))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 65 * 16, 44 * 16 + 8, S, false, true);
        }
        else
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 74 * 16 + 8, 23 * 16 + 8, S, false, true);
        }
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
        return;
    case 313:
        MainController::getInstance()->getGameController()->displayText(401);
        return;
    case 314:
        // 5 graals found
        link->getStatus()->setOniLinkable(false);
        scene->getAnimationInGame()->startAnim(3);
        break;
    case 315:
        map->testAnimRoom();
        break;
    case 318:
        if (map->getId() == 15)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 69 * 16 + 8, 37 * 16, S, false, true);
        else if (map->getId() == 16)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 72 * 16 + 8, 15 * 16 + 8, S, false, true);
        else if (map->getId() == 17)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 35 * 16 + 8, 20 * 16 + 8, S, false, true);
        else if (map->getId() == 18)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 26 * 16 + 8, 40 * 16, S, false, true);
        else if (map->getId() == 19)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 60 * 16, 34 * 16, S, false, true);
        else if (map->getId() == 20)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 8 * 16, 51 * 16 + 8, S, false, true);
        else if (map->getId() == 21)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 46 * 16 + 8, 30 * 16, S, false, true);
        else if (map->getId() == 22)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 39 * 16 + 8, 27 * 16, S, false, true);
        else if (map->getId() == 23)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 21 * 16 + 8, 19 * 16, S, false, true);
        else if (map->getId() == 24)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 20 * 16 + 8, 18 * 16 + 8, S, false, true);
        else if (map->getId() == 25)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 21 * 16, 8 * 16, S, false, true);
        else if (map->getId() == 26)
        {
            MainController::getInstance()->getGameController()->displayText(536);
            return;
        }
        else if (map->getId() == 27)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(45, 29 * 16 + 8, 8, S, false, true);
        else
            break;
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
        return;
    case 322:
        link->trouveObjet(TI_SAC_BOMBES);
        return;
    case 328:
        if (scene->getMap()->getBounds()->getX() == 320 * 8)
            link->trouveObjet(TI_CLE, 5);
        else if (scene->getMap()->getBounds()->getY() == 240)
            link->trouveObjet(TI_CLE, 6);
        else
            link->trouveObjet(TI_CLE, 7);
        return;
    case 331:
        link->trouveObjet(TI_ARC);
        return;
    case 341:
        link->setTunique(2);
        break;
    case 342:
        link->setTunique(3);
        break;
    case 345:
        scene->getAnimationInGame()->startAnim(4);
        break;
    case 346:
        scene->setAvancement(AV_ZELDA_CHEZ_PIT);
        break;
    case 347:
        if (link->getEpee() == 2)
        {
            link->trouveObjet(TI_EPEE_3);
        }
        else if (link->getEpee() == 3)
        {
            link->trouveObjet(TI_EPEE_4);
        }
        else
        {
            link->trouveObjet(TI_EPEE_5);
        }
        return;
    case 356:
        scene->getAnimationInGame()->startAnim(7);
        break;
    case 360:
        scene->setAvancement(AV_ARMEE_UP);
        break;
    case 364:
        MainController::getInstance()->getGameController()->saveData(true);
        MainController::getInstance()->setStep(ENDING);
        return;
    case 367:
        scene->setAvancement(AV_TUTO_OK);
        break;
    case 369:
        link->trouveObjet(TI_DOUBLE_MAGIE);
        return;
    case 373:
        link->getStatus()->updateRupees(-100);
        AudioManager::getInstance()->playSound(TS_HAPPY, 2);
        if (link->getStatus()->getMaxBombs() < 30 && (link->getStatus()->getMaxArrows() == 70 || (int)((float)rand() / RAND_MAX * 2)))
        {
            link->getStatus()->setMaxBombs(link->getStatus()->getMaxBombs() + 2);
            link->getStatus()->setBombs(link->getStatus()->getMaxBombs());
            MainController::getInstance()->getGameController()->displayText(377);
        }
        else
        {
            link->getStatus()->setMaxArrows(link->getStatus()->getMaxArrows() + 5);
            link->getStatus()->setArrows(link->getStatus()->getMaxArrows());
            MainController::getInstance()->getGameController()->displayText(378);
        }
        return;
    case 379:
        if (link->getInventory()->hasObject(OCARINA) && link->getInventory()->hasObject(CHANT_2))
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 39 * 16 + 8, 80 * 16, S, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            return;
        }
        break;
    case 382:
        scene->setAvancement(AV_PASSE_ONI);
        break;
    case 383:
        scene->setAvancement(AV_PASSE_OK);
        break;
    case 390:
        if (scene->getAvancement() == AV_PIT_A_VOIR)
        {
            scene->setAvancement(AV_PIT_VU);
        }
        break;
    case 398:
        scene->setAvancement(AV_AUTORISATION_SORTIE);
        link->trouveObjet(TI_CARTE);
        return;
    case 400:
        link->trouveObjet(TI_EPEE_2);
        return;
    case 431:
        link->getInventory()->setObject(ENCYCLOPEDIE);
        break;
    case 432:
        scene->setMonsters(75);
        break;
    case 435:
        scene->payForMonsters();
        break;
    case 438:
        scene->setCoffre(0, 13, 1);
        break;
    case 439:
        scene->setCoffre(0, 13, 2);
        map->ouvrePorte(29, 0, 0);
        break;
    case 441:
        link->getStatus()->setBombs(link->getStatus()->getMaxBombs());
        break;
    case 448:
        if (scene->getAvancement() == AV_MINE_FERMEE)
        {
            scene->setAvancement(AV_HOMME_PIEGE_MINE);
        }
        break;
    case 454:
        if (scene->getAvancement() == AV_HOMME_PIEGE_MINE)
        {
            scene->setAvancement(AV_AUTORISATION_MINE);
        }
        break;
    case 474:
        link->trouveObjet(TI_POTION_ROUGE);
        link->getStatus()->updateRupees(-60);
        return;
    case 476:
        link->trouveObjet(TI_POTION_VERTE);
        link->getStatus()->updateRupees(-40);
        return;
    case 478:
        scene->setCoffre(0, 17, 1);
        break;
    case 486:
        scene->setAvancement(AV_INFO_MAIRE_OK);
        break;
    case 494:
        scene->setAvancement(AV_AUTORISATION_MANOIR);
        break;
    case 497:
        MainController::getInstance()->getGameController()->getOcarinaController()->setSong(0);
        MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
        return;
    case 502:
        link->trouveObjet(TI_POTION_BLEUE);
        link->getStatus()->updateRupees(-160);
        return;
    case 519:
        MainController::getInstance()->getGameController()->getOcarinaController()->setSong(2);
        MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
        return;
    case 527:
        scene->setAvancement(AV_SAGE_DESERT_VU);
        break;
    case 530:
        MainController::getInstance()->getGameController()->getOcarinaController()->setSong(1);
        MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
        return;
    case 535:
        scene->setCoffre(0, 18, 1);
        break;
    default:
        break;
    }

    MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
}

void TextArea::setTextId(int textId)
{
    delete text;
    text = TextManager::getInstance()->getText(textId);
    text->setBox(16 * 18, 16 * 4);
    id = textId;
}

bool TextArea::hasLogicalNext()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    // int tmp = 0;
    int next = 0;
    switch (id)
    {
    case 89:
    case 90:
    case 102:
    case 174:
    case 320:
    case 321:
    case 329:
    case 330:
    case 343:
    case 344:
    case 351:
    case 352:
    case 353:
    case 354:
    case 355:
    case 359:
    case 361:
    case 362:
    case 374:
    case 385:
    case 386:
    case 387:
    case 388:
    case 389:
    case 391:
    case 392:
    case 393:
    case 394:
    case 395:
    case 396:
    case 397:
    case 401:
    case 402:
    case 403:
    case 404:
    case 405:
    case 406:
    case 407:
    case 408:
    case 409:
    case 416:
    case 418:
    case 419:
    case 420:
    case 421:
    case 422:
    case 426:
    case 427:
    case 428:
    case 429:
    case 430:
    case 434:
    case 437:
    case 451:
    case 470:
    case 484:
    case 485:
    case 489:
    case 490:
    case 491:
    case 492:
    case 493:
    case 496:
    case 504:
    case 507:
    case 509:
    case 513:
    case 514:
    case 516:
    case 518:
    case 524:
    case 525:
    case 526:
    case 528:
    case 529:
    case 533:
    case 534:
        next = id + 1;
        break;
    case 96:
        next = link->getInventory()->nbQuartCoeur() ? 97 : 98;
        break;
    case 104:
    case 105:
        if (scene->getMap()->getId() == 23)
        {
            scene->setCoffre(9, 27, 1);
        }
        else if (scene->getMap()->getId() == 24)
        {
            scene->setCoffre(10, 27, 1);
        }
        else if (scene->getMap()->getId() == 25)
        {
            scene->setCoffre(11, 24, 1);
        }
        next = 316;
        break;
    case 109:
        next = 316;
        break;
    case 121:
        next = 316;
        break;
    case 188:
        if (link->getStatus()->getVirtualRupees() >= 100)
        {
            next = 191;
        }
        else
        {
            next = 190;
        }
        break;
    case 224:
        if (link->getStatus()->getVirtualRupees() >= 250)
        {
            next = 226;
        }
        else
        {
            next = 190;
        }
        break;
    case 189:
    case 225:
    case 444:
    case 473:
    case 475:
    case 477:
    case 503:
    case 512:
        next = 192;
        break;
    case 314:
        if (link->getInventory()->nbGraals() == 5)
        {
            return false;
        }
        next = 316; //=> sauvegarder
        break;
    case 316:
        MainController::getInstance()->getGameController()->saveData();
    case 317:
        next = 318;
        break;
    case 323:
        next = 316;
        break;
    case 324:
        if (scene->getMap()->getBounds()->getX() == 320 * 8)
            next = 325;
        else if (scene->getMap()->getBounds()->getY() == 240)
            next = 326;
        else
            next = 327;
        break;
    case 325:
    case 326:
    case 327:
        next = 328;
        break;
    case 332:
        scene->setAvancement(AV_FILLE_MAIRE_SAUVEE);
        next = 316;
        break;
    case 357:
        next = 351;
        break;
    case 372:
        scene->setCoffre(0, 11, 1);
        next = 373;
        break;
    case 373:
        if (link->getStatus()->getVirtualRupees() < 100)
        {
            next = 376;
            break;
        }
        return false;
    case 423:
        scene->setCoffre(0, 12, 1);
        next = 424;
        break;
    case 425:
        if (link->getStatus()->isOniLink())
        {
            next = (scene->getMonsters(75) || !link->getInventory()->hasObject(ENCYCLOPEDIE)) ? 433 : 432;
            break;
        }
        if (link->getInventory()->hasObject(ENCYCLOPEDIE))
        {
            if (!link->getStatus()->isOniLinkable() && !scene->getCoffre(0, 13))
            {
                next = 437;
                break;
            }
            if (scene->getMonsters(19) && scene->getMonsters(24) && scene->getMonsters(35) && scene->getCoffre(0, 13) != 2)
            {
                next = 439;
                break;
            }
            if (scene->getTotalMonsters() == 62)
            {
                next = 440;
                break;
            }
            if (scene->getMonstersSolde() > 0)
            {
                next = 434;
                break;
            }
            return false;
        }
        next = 426;
        break;
    case 440:
        if (scene->getMonstersSolde() > 0)
        {
            next = 434;
            break;
        }
        return false;
    case 443:
        if (link->getStatus()->getVirtualRupees() >= 10)
        {
            next = 446;
            scene->getMap()->closeChests();
            link->getStatus()->updateRupees(-10);
        }
        else
        {
            next = 190;
        }
        break;
    case 452:
        if (link->getStatus()->getVirtualRupees() >= 10)
        {
            next = 454;
            link->getStatus()->updateRupees(-10);
        }
        else
        {
            next = 455;
        }
        break;
    case 456:
        if (link->getStatus()->getVirtualRupees() >= 2)
        {
            next = 446;
            link->getStatus()->updateRupees(-2);
            link->getStatus()->updateLife(2);
        }
        else
        {
            next = 190;
        }
        break;
    case 459:
        if (link->getStatus()->getVirtualRupees() >= 10)
        {
            next = 446;
            link->getStatus()->updateRupees(-10);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 8);
        }
        else
        {
            next = 190;
        }
        break;
    case 461:
        if (link->getStatus()->getVirtualRupees() >= 20)
        {
            next = 446;
            link->getStatus()->updateRupees(-20);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 4);
        }
        else
        {
            next = 190;
        }
        break;
    case 464:
        if (link->getStatus()->getVirtualRupees() >= 20)
        {
            next = 446;
            link->getStatus()->updateRupees(-20);
            link->getStatus()->setArrows(link->getStatus()->getArrows() + 10);
        }
        else
        {
            next = 190;
        }
        break;
    case 466:
        if (link->getStatus()->getVirtualRupees() >= 30)
        {
            next = 446;
            link->getStatus()->updateRupees(-30);
            link->getStatus()->setBombs(link->getStatus()->getBombs() + 5);
        }
        else
        {
            next = 190;
        }
        break;
    case 471:
        next = 474;
        break;
    case 472:
        next = 476;
        break;
    case 474:
        if (link->getStatus()->getVirtualRupees() < 60)
        {
            next = 190;
            break;
        }
        return false;
    case 476:
        if (link->getStatus()->getVirtualRupees() < 40)
        {
            next = 190;
            break;
        }
        return false;
    case 487:
        if (scene->getCoffre(0, 16))
        {
            next = 488;
            break;
        }
        return false;
    case 502:
        if (link->getStatus()->getVirtualRupees() < 160)
        {
            next = 190;
            break;
        }
        return false;
    case 511:
        if (link->getStatus()->getVirtualRupees() < 10)
        {
            next = 190;
            break;
        }
        link->getStatus()->updateRupees(-10);
        next = 513;
        break;
    default:
        return false;
    }
    setTextId(next);
    return true;
}

void TextArea::drawAdditionalContent()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    int tmp;
    switch (id)
    {
    case 96:
        tmp = link->getInventory()->nbQuartCoeur();
        if (tmp == 0)
            tmp = 4;
        WindowManager::getInstance()->draw(imageCoeur, 16 * tmp, 0, 16, 16, 16 * 9 + 8, 16 * 12);
        break;
    default:
        break;
    }
}
