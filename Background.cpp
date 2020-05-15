#include "Background.h"

Background::Background()
{
    src.x = src.y = 0;
    src.w = 1920;
    src.h = 1082;

    dest.x = dest.y = 0;
    dest.w = 1280;
    dest.h = 720;

    path = "assets/bgstitch.png";
    this->Load();
}

void Background::update()
{
    if (src.x == 1920)
    {
        src.x = 0;
    }
    src.x += 2;
}

void Background::Draw()
{

    //temp = TextureManager::LoadTexture(path);

    TextureManager::Draw(temp, src, dest, SDL_FLIP_NONE);
}

void Background::Load()
{
    temp = TextureManager::LoadTexture(path);
}