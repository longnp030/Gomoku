#pragma once
#ifndef RENDERING_H
#define RENDERING_h

#include "Game.h"

#include <SDL.h>

void render_gameover_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color);
void render_game(SDL_Renderer *renderer, const game_t *game); 
// Call const game_t to render, not modify the state of the game 

#endif //RENDERING_H