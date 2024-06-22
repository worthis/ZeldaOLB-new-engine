/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ANIMATIONINGAME_H__
#define __ANIMATIONINGAME_H__

#include "../link/Link.h"
#include "../scene/Map.h"
#include "../scene/Camera.h"

#include "../../../engine/renderer/SimpleTransition.h"
#include "../../../engine/renderer/CircularTransition.h"

class AnimationInGame
{
public:
    AnimationInGame();
    ~AnimationInGame();

    void testAnim(); // startAnim if needed
    void startAnim(int id);
    void loop();
    void draw();
    void drawAfterHud();

    bool isRunning();

    int getSpecialMusicId();

    bool loopMap();
    bool loopCamera();
    bool loopLink();

    void stop();

private:
    int id;
    int anim;

    bool running;

    bool lmap;
    bool lcamera;
    bool llink;

    Link *link;
    Link *oniLink;
    Map *map;
    Camera *camera;

    WImage *image;

    SimpleTransition transition;
    CircularTransition circularTransition;
};

#endif // AnimationInGame.h
