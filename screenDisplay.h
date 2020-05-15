#pragma once
#include "TextureManager.h"

class screenDisplay
{
private:
    SDL_Texture *temp;
    const char *path;
    SDL_Rect src, dest;

public:
    void Load(const char *path);        //load the texture to be displayed on screen

    void setDimension(int x, int y, int w, int h, int x2, int y2, int w2, int h2);      //set the size of screen
    void Draw();        //draw the texture on screen
};