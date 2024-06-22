/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SCENE_H__
#define __SCENE_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"

#include "../../../engine/util/time/Metronome.h"

#include "../../../engine/renderer/CircularTransition.h"

#include "../../Save.h"
#include "../../content/scene/Camera.h"
#include "../../content/scene/Map.h"
#include "../../content/scene/Hud.h"
#include "../../content/scene/AnimationInGame.h"
#include "../../content/link/Link.h"

enum SceneStep
{
    SCENE_MAIN,
    SCENE_TRANSITION_LIVE,
    SCENE_ONLY_LINK,
    SCENE_TRANSITION_BETWEEN_TWO_MAPS
};

class Scene
{
public:
    Scene();
    ~Scene();

    void init(Save *sv);

    void saveData();

    void handleActions(Action *action);
    void loop();
    void draw();

    void fixCameraBounds();

    bool checkCollisions(BoundingBox *box, Collisionable *object, bool checkEnnemis, bool ignoreNotIdle = false,
                         bool withAvoid = false, bool onlyBox = false, bool checkObjects = true,
                         int safeX = 0, int safeY = 0, int safeW = -1, int safeH = -1, bool checkDanger = false);
    bool checkCollisionsWithLink(BoundingBox *box);

    bool testDegatOnLink(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect);
    bool testDegat(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis = true);
    void testTransition();

    Map *getMap();
    Link *getLink();
    Metronome *getMetronome();
    Camera *getCamera();
    Hud *getHud();
    AnimationInGame *getAnimationInGame();

    Avancement getAvancement();
    void setAvancement(Avancement av);

    void setStep(SceneStep s);
    void setMap(Map *map);

    bool permuteBlocs(int step); // 0 = orange up - blue down

    int getCoffre(int i, int j);
    void setCoffre(int i, int j, int val);

    int getRooms(int d, int i, int j);
    void setRooms(int d, int i, int j, int val);

    int getMonsters(int i);
    void setMonsters(int i, int val = 1);

    int getTotalMonsters();
    int getMonstersSolde();
    void payForMonsters();

private:
    SceneStep step;

    Save *save;
    Map *map;
    Camera camera;
    Metronome *metronome;
    Link *link;
    Hud *hud;
    AnimationInGame animation;

    Avancement avancement;

    bool boxOnLink;

    CircularTransition transition;

    int coffres[NB_COFFRES][COFFRES_MAX_SIZE];

    int rooms[NB_DONJON][MAX_ROOMS_X][MAX_ROOMS_Y];

    int monsters[NB_MONSTERS];

    WImage *filterForest;
    WImage *filterRain[3];
    WImage *filterSky[3];

    WImage *planeAndUfo;
    WImage *lightning;

    bool displayPlane;
    bool displayUfo;
    bool displayLightning1;
    bool displayLightning2;

    int planeX;
    int lightning1X;
    int lightning2X;
    int lightning1Duration;
    int lightning2Duration;
};

#endif // Scene.h
