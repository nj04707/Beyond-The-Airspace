#pragma once
#include "TextureManager.h"

class Background
{
private:
    SDL_Rect src, dest;
    const char *path;
    SDL_Texture *temp;

public:
    Background();

    void update(); //moves the background backward on the screen

    void Draw(); //draws the background on the screen

    void Load(); //loads the background that is displayed
};