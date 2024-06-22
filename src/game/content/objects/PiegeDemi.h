/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEDEMI_H__
#define __PIEGEDEMI_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeDemi : public Object {
    public :
        PiegeDemi(int x, int y);
        ~PiegeDemi();

        void loop();
        void draw(int offsetX, int offsetY);

        void disable();

    private :

        void snipe();

        Chrono chrono;

        int anim;
        int animMax;
        int vanim;

        bool enable;
};

#endif  // PiegeDemi.h
