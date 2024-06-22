/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGECOLERE_H__
#define __PIEGECOLERE_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeColere : public Object {
    public :
        PiegeColere(int x, int y);
        ~PiegeColere();

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

#endif  // PiegeColere.h
