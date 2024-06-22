/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CHRONO_H__
#define __CHRONO_H__

#include <SDL2/SDL.h>

class Chrono {
    public :
        Chrono();
        ~Chrono();

        void reset();
        int getElapsedTime();

    private :

        Uint32 lastAnimTime;
};

#endif  // Chrono.h


