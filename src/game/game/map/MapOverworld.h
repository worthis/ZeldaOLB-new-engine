/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MAPOVERWORLD_H__
#define __MAPOVERWORLD_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/util/time/Chrono.h"

#include "../../keys/Action.h"

#include "../../content/CommonGame.h"

class MapOverworld
{
public:
    MapOverworld();
    ~MapOverworld();

    void handleActions(Action *action);
    void loop();
    void draw();

    void launch();

private:
    int getOffsetXForMap(int mapId);
    int getOffsetYForMap(int mapId);

    int anim;
    int animMax;
    int vanim;

    bool started;

    int xLink;
    int yLink;

    int offsetForme;
    int offsetSkin;

    WImage *imageMap;
    WImage *imageLink;

    Chrono chrono;
};

#endif // MapOverworld.h
