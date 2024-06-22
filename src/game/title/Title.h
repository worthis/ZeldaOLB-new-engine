/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TITLE_H__
#define __TITLE_H__

#include "../../engine/common/Common.h"
#include "../../engine/window/Event.h"
#include "../../engine/resources/WImage.h"
#include "../../engine/texts/Text.h"
#include "../../engine/util/time/Metronome.h"

class Title
{
public:
    Title();
    ~Title();

    void init();

    void handleEvents(Event *event);
    void loop();
    void draw();

private:
    int anim;
    int animMax;
    int vanim;
    Chrono chrono;

    WImage *images[4];
    WImage *logo;
    Text *text;
    int textSize;
    bool ready;
    int alpha;
    int wait;

    Metronome *metronomeText;
};

#endif // Title.h
