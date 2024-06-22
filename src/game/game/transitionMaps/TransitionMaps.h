/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRANSITIONMAPS_H__
#define __TRANSITIONMAPS_H__

#include "../../content/CommonGame.h"
#include "../../content/scene/Map.h"

class TransitionMaps {
    public :
        TransitionMaps();
        ~TransitionMaps();

        void loop();
        void draw();

        void init();

    private :

        int getOffsetXForMap(Map* map);
        int getOffsetYForMap(Map* map);
        int getSecondMapId(int x, int y);

        int offset;
        int offsetMax;
        int offsetX;
        int offsetY;
        Direction direction;

        Map* map1;
        Map* map2;
        BoundingBox* box1;
        BoundingBox* box2;

        WImage* filterForest;
        WImage* filterRain[3];
        int alpha;

};

#endif  // TransitionMaps.h
