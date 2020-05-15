#pragma once

#include "Game.h"

class TextureManager
{

public:
    static SDL_Texture *LoadTexture(const char *fileName);          //load the specified text texture on screen
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip); //virtual function to draw specific object
};