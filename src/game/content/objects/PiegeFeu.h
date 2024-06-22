/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEFEU_H__
#define __PIEGEFEU_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeFeu : public Object {
    public :
        PiegeFeu(int x, int y);
        ~PiegeFeu();

        void loop();
        void draw(int offsetX, int offsetY);

    private :

        void snipe();

        Chrono chrono;

        int anim;
        int animMax;
        int vanim;
};

#endif  // PiegeFeu.h
