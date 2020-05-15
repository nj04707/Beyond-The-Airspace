#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#endif
//static bool help;
class mainmenu
{
public:
    SDL_Texture *temp;          //background
    SDL_Texture *temp2;         //start button
    SDL_Texture *temp3;         //Quit button
    SDL_Texture *temp4;         //Help button
    SDL_Texture *temp5;         //instructions screen
    bool showhelp = false;

    mainmenu();
    ~mainmenu();
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Rect src, dest;
    const char *path;
    void render();
    void renderhelp();
    void clean();
    bool checkstart();
    void draw(SDL_Renderer *, SDL_Event, int *);        //show the main menu
    SDL_Texture *loadTexture(std::string path);
    void checkhelp();          //display instructions
    void LT(const char *path1, const char *path2, const char *path3, const char *path4, const char *path5);     //loads textures
};
