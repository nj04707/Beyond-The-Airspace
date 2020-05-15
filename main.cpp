
#include "Game.h"
#include "TextureManager.h"
#include "mainmenu.h"
#include "Time.h"

Game *game = nullptr;
SDL_Event evt;
Time t;
int main(int argc, char *argv[])
{
	mainmenu menu_m;

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Aasman ki Unchaiyoun Me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

	menu_m.LT("assets/MAINbackground.png", "assets/buttons.png", "assets/buttons.png", "assets/buttons.png", "assets/instructions.png");

	while (game->menu_flag != false)
	{
		SDL_PollEvent(&evt);

		if (game->menu_flag == true) //run the game once the user clicks on start button
		{
			SDL_RenderClear(game->renderer);

			menu_m.render();
			game->menu_flag = !menu_m.checkstart();
			menu_m.checkhelp();

			if (menu_m.showhelp == true)
			{
				SDL_RenderClear(game->renderer);
				menu_m.renderhelp();
				//SDL_RenderPresent(game->renderer);
			}
			if (evt.type == SDL_KEYDOWN)
			{
				switch (evt.key.keysym.sym)
				{
				case SDLK_b:
					menu_m.showhelp = false;
					break;
				default:
					break;
				}
			}

			SDL_RenderPresent(game->renderer);
		}
	}

	game->level_start = t.get_Time();

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		while (game->gam_paused)
		{

			game->handleEvents();
		}
		game->handleEvents();
		game->update();

		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	game = nullptr;

	return 0;
}
