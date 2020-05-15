#include "screenDisplay.h"

void screenDisplay::Load(const char *path)
{
    temp = TextureManager::LoadTexture(path);
}

void screenDisplay::setDimension(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
{
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;

    dest.x = x2;
    dest.y = y2;
    dest.w = w2;
    dest.h = h2;
}

void screenDisplay::Draw()
{
    TextureManager::Draw(temp, src, dest, SDL_FLIP_NONE);
}