#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Time.h"
#include "Background.h"
#include "ECS/Components.h"

static SDL_Texture *playerTx;
static SDL_Rect srcR, destR;

static Background bg;
static Time time;

static Manager manager;
auto &player(manager.addEntity());
