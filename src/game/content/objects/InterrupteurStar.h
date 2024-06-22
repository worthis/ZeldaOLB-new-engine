/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2022  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __INTERRUPTEURSTAR_H__
#define __INTERRUPTEURSTAR_H__

#include "../types/Object.h"
#include "../scene/Map.h"

class InterrupteurStar : public Object {
    public :
        InterrupteurStar(int x, int y, bool used, Map* map, bool usable = true);
        ~InterrupteurStar();

        void loop();
        void draw(int offsetX, int offsetY);

        bool isResetable();
        void reset();

        void displayOnMap();

        void switchMode();

    private :

        bool used;
        Map* map;
        bool wasUsable;
        bool usable;
};

#endif  // InterrupteurStar.h
