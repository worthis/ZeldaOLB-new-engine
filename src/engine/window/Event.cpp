#include "Event.h"

Event::Event()
{
    for (int i = 0; i < NB_KEYS; i++)
    {
        current[i] = false;
        past[i] = false;
    }
}

Event::~Event()
{
}

void Event::update(const Uint8 *keys, bool capslock)
{
    for (int i = 0; i < NB_KEYS; i++)
    {
        past[i] = current[i];
        current[i] = false;
    }

    current[kUp] = keys[SDL_SCANCODE_UP];
    current[kDown] = keys[SDL_SCANCODE_DOWN];
    current[kLeft] = keys[SDL_SCANCODE_LEFT];
    current[kRight] = keys[SDL_SCANCODE_RIGHT];

    current[kA] = keys[SDL_SCANCODE_A];
    current[kB] = keys[SDL_SCANCODE_B];
    current[kC] = keys[SDL_SCANCODE_C];
    current[kD] = keys[SDL_SCANCODE_D];
    current[kE] = keys[SDL_SCANCODE_E];
    current[kF] = keys[SDL_SCANCODE_F];
    current[kG] = keys[SDL_SCANCODE_G];
    current[kH] = keys[SDL_SCANCODE_H];
    current[kI] = keys[SDL_SCANCODE_I];
    current[kJ] = keys[SDL_SCANCODE_J];
    current[kK] = keys[SDL_SCANCODE_K];
    current[kL] = keys[SDL_SCANCODE_L];
    current[kM] = keys[SDL_SCANCODE_M];
    current[kN] = keys[SDL_SCANCODE_N];
    current[kO] = keys[SDL_SCANCODE_O];
    current[kP] = keys[SDL_SCANCODE_P];
    current[kQ] = keys[SDL_SCANCODE_Q];
    current[kR] = keys[SDL_SCANCODE_R];
    current[kS] = keys[SDL_SCANCODE_S];
    current[kT] = keys[SDL_SCANCODE_T];
    current[kU] = keys[SDL_SCANCODE_U];
    current[kV] = keys[SDL_SCANCODE_V];
    current[kW] = keys[SDL_SCANCODE_W];
    current[kX] = keys[SDL_SCANCODE_X];
    current[kY] = keys[SDL_SCANCODE_Y];
    current[kZ] = keys[SDL_SCANCODE_Z];

    current[k0] = keys[SDL_SCANCODE_0] || keys[SDL_SCANCODE_KP_0];
    current[k1] = keys[SDL_SCANCODE_1] || keys[SDL_SCANCODE_KP_1];
    current[k2] = keys[SDL_SCANCODE_2] || keys[SDL_SCANCODE_KP_2];
    current[k3] = keys[SDL_SCANCODE_3] || keys[SDL_SCANCODE_KP_3];
    current[k4] = keys[SDL_SCANCODE_4] || keys[SDL_SCANCODE_KP_4];
    current[k5] = keys[SDL_SCANCODE_5] || keys[SDL_SCANCODE_KP_5];
    current[k6] = keys[SDL_SCANCODE_6] || keys[SDL_SCANCODE_KP_6];
    current[k7] = keys[SDL_SCANCODE_7] || keys[SDL_SCANCODE_KP_7];
    current[k8] = keys[SDL_SCANCODE_8] || keys[SDL_SCANCODE_KP_8];
    current[k9] = keys[SDL_SCANCODE_9] || keys[SDL_SCANCODE_KP_9];

    current[kComma] = keys[SDL_SCANCODE_COMMA];
    current[kSemicol] = keys[SDL_SCANCODE_SEMICOLON];
    current[kEscape] = keys[SDL_SCANCODE_ESCAPE];
    current[kTab] = keys[SDL_SCANCODE_TAB];
    current[kShift] = capslock || keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT];
    current[kCtrl] = keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_RCTRL];
    current[kAlt] = keys[SDL_SCANCODE_LALT] || keys[SDL_SCANCODE_RALT];
    current[kSpace] = keys[SDL_SCANCODE_SPACE];
    current[kReturn] = keys[SDL_SCANCODE_RETURN] || keys[SDL_SCANCODE_KP_ENTER];

    current[QUIT] = false;
    current[RESIZE] = current[kCtrl] && current[kReturn];
    current[QUIT_FORCED] = current[kAlt] && keys[SDL_SCANCODE_F4];

    current[kF1] = keys[SDL_SCANCODE_F1];

    if (current[RESIZE])
    {
        current[kReturn] = false;
    }
}

bool Event::isDown(Keys key)
{
    if (current == 0)
    {
        return false;
    }
    return current[key];
}

bool Event::isPushed(Keys key)
{
    if (current == 0 || past == 0)
    {
        return false;
    }
    return current[key] && !past[key];
}

void Event::setEvent(Keys key, bool b)
{
    if (current != 0)
    {
        current[key] = b;
    }
}

int Event::getMouseX()
{
    return mouseX;
}

int Event::getMouseY()
{
    return mouseY;
}

void Event::setMouseX(int mx)
{
    mouseX = mx;
}

void Event::setMouseY(int my)
{
    mouseY = my;
}
