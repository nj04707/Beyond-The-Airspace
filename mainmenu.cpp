#include "TextureManager.h"
#include "mainmenu.h"

mainmenu::mainmenu()
{
}
mainmenu::~mainmenu()
{
}
void mainmenu::LT(const char *path1, const char *path2, const char *path3, const char *path4, const char *path5)
{
    temp = TextureManager::LoadTexture(path1);
    temp2 = TextureManager::LoadTexture(path2);
    temp3 = TextureManager::LoadTexture(path3);
    temp4 = TextureManager::LoadTexture(path4);
    temp5 = TextureManager::LoadTexture(path5);
}

void mainmenu::render()
{
    SDL_Rect src, dest;
    src.x = src.y = 0;
    src.w = 1280;
    src.h = 720;
    dest.x = dest.y = 0;
    dest.w = 1280;
    dest.h = 720;
    TextureManager::Draw(temp, src, dest, SDL_FLIP_NONE);

    src.x = src.y = 0;
    src.w = 150;
    src.h = 65;
    dest.x = dest.y = 350;
    dest.w = 150;
    dest.h = 65;
    TextureManager::Draw(temp2, src, dest, SDL_FLIP_NONE);

    src.x = 698;
    src.y = 334;
    src.w = 150;
    src.h = 68;
    dest.x = 500;
    dest.y = 350;
    dest.w = 150;
    dest.h = 65;
    TextureManager::Draw(temp3, src, dest, SDL_FLIP_NONE);
    src.x = 520;
    src.y = 166;
    src.w = 150;
    src.h = 68;
    dest.x = 650;
    dest.y = 350;
    dest.w = 154;
    dest.h = 65;
    TextureManager::Draw(temp4, src, dest, SDL_FLIP_NONE);
}
void mainmenu::renderhelp()
{
    SDL_Rect src, dest;
    //temp5=TextureManager::LoadTexture("assets/instructions.png");
    src.x = 0;
    src.y = 0;
    src.w = 1280;
    src.h = 720;
    dest.x = 0;
    dest.y = 0;
    dest.w = 1280;
    dest.h = 720;
    TextureManager::Draw(temp5, src, dest, SDL_FLIP_NONE);
}
bool mainmenu::checkstart()
{
    SDL_Event e;
    int x;
    int y;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_MOUSEBUTTONDOWN:

            SDL_GetMouseState(&x, &y);
            //std::cout << "Points" << x << "-" << y;
            if (x >= 350 && x <= 498 && y >= 350 && y <= 412)
            {
                return true;
            }
            else if (x >= 500 && x <= 648 && y >= 350 and y <= 412)
            {

                SDL_DestroyRenderer(renderer);
                SDL_Quit();

                std::cout << "Game Cleaned" << std::endl;
            }
            else if ((x >= 659) && (x <= 798) && (y >= 361) && (y <= 409))
            {
                showhelp = true;
                
            }

            break;
        }
    }
    return false;
}

void mainmenu::checkhelp()
{
    SDL_Event e;
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    while (SDL_PollEvent(&e))
    {

        switch (e.type)
        {
        case SDL_MOUSEBUTTONDOWN:

            if ((x >= 659))
            {
                if (x <= 798)
                {
                    if (y >= 361)
                    {
                        if (y <= 409)
                        {
                            showhelp = true;
                        }
                    }
                }
            }
            break;
        }
    }
}