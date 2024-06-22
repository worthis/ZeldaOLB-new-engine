/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __LOOPABLE_H__
#define __LOOPABLE_H__

#include "../CommonGame.h"

#include "Drawable.h"

class Loopable : public Drawable
{
public:
    Loopable();
    virtual ~Loopable() = 0;

    virtual void loop() = 0;
};

#endif // Loopable.h
