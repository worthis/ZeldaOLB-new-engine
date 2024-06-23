/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __EVENT_H__
#define __EVENT_H__

#include <SDL/SDL.h>

enum Keys
{
    kA,
    kZ,
    kE,
    kR,
    kT,
    kY,
    kU,
    kI,
    kO,
    kP,
    kQ,
    kS,
    kD,
    kF,
    kG,
    kH,
    kJ,
    kK,
    kL,
    kM,
    kW,
    kX,
    kC,
    kV,
    kB,
    kN,
    kComma,
    kSemicol,
    kEscape,
    kTab,
    kLShift,
    kRShift,
    kLCtrl,
    kRCtrl,
    kLAlt,
    kRAlt,
    kSpace,
    kReturn,
    kBackspace,
    k0,
    k1,
    k2,
    k3,
    k4,
    k5,
    k6,
    k7,
    k8,
    k9,
    kUp,
    kDown,
    kLeft,
    kRight,
    kF1,
    QUIT_FORCED,
    QUIT,
    RESIZE,
    mouseUp,
    mouseDown,
    jUp,
    jDown,
    jLeft,
    jRight,
    jLUp,
    jLDown,
    jLLeft,
    jLRight,
    jRUp,
    jRDown,
    jRLeft,
    jRRight,
    jSelect,
    jStart,
    jA,
    jB,
    jX,
    jY,
    jLB,
    jLT,
    jRB,
    jRT,
    jLS,
    jRS,
    NB_KEYS
};

class Event
{
public:
    Event();
    ~Event();

    void update(const Uint8 *keys, bool capslock);

    bool isDown(Keys key);
    bool isPushed(Keys key);

    int getMouseX();
    int getMouseY();

    void setEvent(Keys key, bool b);

    void setMouseX(int mx);
    void setMouseY(int my);

private:
    bool current[NB_KEYS];
    bool past[NB_KEYS];

    int mouseX;
    int mouseY;
};

#endif // Event.h
