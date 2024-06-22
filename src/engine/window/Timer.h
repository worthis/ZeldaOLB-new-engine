/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();
    ~Timer();

    void reset();
    int getElapsedTime();

private:
    Uint32 lastAnimTime;
};

#endif // Timer.h
