#ifndef Game_h
#define Game_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#endif

class mainmenu;
class TextManager;
class AssetManager;
class ColliderComponent;

class Game
{
public:
   Game();
   ~Game();

   bool lev_com = false;    //
   bool gam_over = false;   //
   bool gam_paused = false; //
   //mainmenu *main_m;
   bool menu_flag = true;       //used to determine the current game state
   bool help = false;           //
   Uint32 pause_time = 0;       //
   Uint32 level_start = 0;      //
   Uint32 pause_start_time = 0; //

   void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
   void handleEvents();
   void update(); //update the game objects
   void render(); //determine the objects that will render on screen
   void clean();  //deallocates memory
   bool getGameState();
   static TextManager *tex;
   static SDL_Renderer *renderer;
   static SDL_Event event;
   static std::vector<ColliderComponent *> colliders;
   static AssetManager *assets;
   enum groupLabels : std::size_t
   {
      groupMap,
      groupPlayers,
      groupEnemies,
      groupColliders,
      groupBullets,
      groupScoreUps,
      groupPowerUps,
      groupExplosions,
      groupMissiles
   };

   bool running()
   {
      return isRunning;
   }

private:
   int cnt = 0;
   bool isRunning;
   SDL_Window *window;
};

#endif // Game_Class_h
