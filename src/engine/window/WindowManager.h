/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "../common/Common.h"
#include "Event.h"

#include "../resources/WImage.h"

#define DEFAULT_ALPHA_PIXEL_ROUTINE
#undef EXPERIMENTAL_ALPHA_PIXEL_ROUTINE
#define ALPHA_PIXEL_ADDITIVE_BLEND

class WindowManager
{
public:
    static WindowManager *getInstance();
    int init();
    int createWindow(string title, string icon, bool full);
    bool isOpened();
    Event *getEvent();
    void close();
    void display();

    void draw(WImage *image, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int alpha = 255);
    void draw(SDL_Surface *object, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int alpha = 255);
    void draw(SDL_Surface *object);

    int nbJoysticks();

    void setFullScreen(bool b);
    bool isFullScreen();

    void exit();

    int filledEllipseRGBA(SDL_Surface *dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
    WindowManager();
    ~WindowManager();
    static WindowManager instance;

    int filledEllipseColor(SDL_Surface *dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color);
    int vlineColor(SDL_Surface *dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color);
    int hlineColor(SDL_Surface *dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color);
    int _VLineAlpha(SDL_Surface *dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color);
    int _HLineAlpha(SDL_Surface *dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color);
    int filledRectAlpha(SDL_Surface *dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
    int _filledRectAlpha(SDL_Surface *dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha);

    bool fullScreen;
    string name;
    Event *event;
    SDL_Joystick *joystick;

    SDL_Surface *window;
    SDL_Surface *windowTmp;

    Uint32 lastAnimTime;
    bool open;

    bool buttonA;
    bool buttonB;
    bool buttonX;
    bool buttonY;
    bool buttonStart;
    bool buttonSelect;
    bool buttonLB;
    bool buttonRB;
    bool buttonLS;
    bool buttonRS;
};

#endif // WindowManager.h
