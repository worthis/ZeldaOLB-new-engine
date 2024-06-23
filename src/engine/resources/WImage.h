/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WIMAGE_H__
#define __WIMAGE_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../common/Common.h"
#include "WResource.h"

class WImage : public WResource
{
public:
    WImage(string filename, bool alpha = false);
    WImage(int w, int h, bool alpha = false);
    ~WImage();
    SDL_Surface *getImage();
    void setAlpha(int alpha); // 0 to 255
private:
    WImage();

    SDL_Surface *image;
};

#endif // WImage.h
