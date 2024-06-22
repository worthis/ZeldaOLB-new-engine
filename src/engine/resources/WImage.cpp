#include "WImage.h"

#include "../window/WindowManager.h"

WImage::WImage(string filename, bool alpha)
{
    name = filename;

    SDL_Surface *tmp = IMG_Load(name.c_str());
    if (alpha)
    {
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 0, 0, 255));
    }
    image = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
    SDL_FreeSurface(tmp);
}

WImage::WImage(int w, int h, bool alpha)
{
    SDL_Surface *tmp = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    if (alpha)
    {
        SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, 0, 0, 255));
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 0, 0, 255));
    }
    image = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
    SDL_FreeSurface(tmp);
}

WImage::WImage()
{
}

WImage::~WImage()
{
    SDL_DestroyTexture(image);
}

SDL_Texture *WImage::getImage()
{
    return image;
}

void WImage::setAlpha(int alpha)
{
    SDL_SetTextureAlphaMod(image, alpha);
}
