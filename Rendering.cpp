#pragma warning
#pragma once

#include "pch.h"
#include "Rendering.h"
#include "Game.h"

#include <SDL_image.h>
#include <cmath>
#include <cstdint>

const SDL_Color GRID_COLOR = { 255, 255, 255 , 255 };
const SDL_Color PLAYER_X_COLOR = { 255, 165, 0, 255 };
const SDL_Color PLAYER_O_COLOR = { 50, 100, 255 ,255 };
const SDL_Color TIE_COLOR = { 100, 100, 100, 255 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
	for (int i = 1; i < N; ++i) {
		SDL_RenderDrawLine(renderer, i * cell_width, 0, i * cell_width, SCREEN_HEIGHT);
		SDL_RenderDrawLine(renderer, 0, i * cell_height, SCREEN_WIDTH, i * cell_height);
	}
}

void render_x(SDL_Renderer *renderer, int row, int column, const SDL_Color *color) {
	const float half_box_size = fmin(cell_width, cell_height) * 0.25; // Size of the X box
	const float center_x = cell_width * 0.5 + column * cell_width;
	const float center_y = cell_height * 0.5 + row * cell_height;
	SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
	SDL_RenderDrawLine(renderer, center_x - half_box_size, center_y - half_box_size, center_x + half_box_size, center_y + half_box_size);
	SDL_RenderDrawLine(renderer, center_x + half_box_size, center_y - half_box_size, center_x - half_box_size, center_y + half_box_size);
}

void SDL_RenderDrawCircle(SDL_Renderer *renderer, int32_t _x, int32_t _y, int32_t radius) {
	int32_t x = radius - 1;
	int32_t y = 0;
	int32_t dx = 1;
	int32_t dy = 1;
	int32_t err = dx - (radius << 1);

	while (x >= y) {
		SDL_RenderDrawPoint(renderer, _x + x, _y - y);
		SDL_RenderDrawPoint(renderer, _x + x, _y + y);
		SDL_RenderDrawPoint(renderer, _x - x, _y - y);
		SDL_RenderDrawPoint(renderer, _x - x, _y + y);
		SDL_RenderDrawPoint(renderer, _x + y, _y - x);
		SDL_RenderDrawPoint(renderer, _x + y, _y + x);
		SDL_RenderDrawPoint(renderer, _x - y, _y - x);
		SDL_RenderDrawPoint(renderer, _x - y, _y + x);

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0) {
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}

void render_o(SDL_Renderer *renderer, int row, int column, const SDL_Color *color) {
	const float half_box_size = fmin(cell_width, cell_height) * 0.25; // Size of the X box
	const float center_x = cell_width * 0.5 + column * cell_width;
	const float center_y = cell_height * 0.5 + row * cell_height;
	SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
	SDL_RenderDrawCircle(renderer, center_x, center_y, half_box_size);
}

void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
	player_x_color = &PLAYER_X_COLOR;
	player_o_color = &PLAYER_O_COLOR;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			switch (board[i * N + j]) {
			case PLAYER_X:
				render_x(renderer, i, j, player_x_color); 
				break;

			case PLAYER_O:
				render_o(renderer, i, j, player_o_color);
				break;

			default: {}
			}
		}
	}
}

void render_running_state(SDL_Renderer *renderer, const game_t *game) {
	render_grid(renderer, &GRID_COLOR);
	render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_O_COLOR);
}

void render_gameover_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color) {
	render_grid(renderer, color);
	render_board(renderer, game->board, color, color);
}

void render_game(SDL_Renderer *renderer, const game_t *game) {
	switch (game->state) {
	case RUNNING_STATE:
		render_running_state(renderer, game);
		break;

	case PLAYER_X_WON_STATE:
		render_gameover_state(renderer, game, &PLAYER_X_COLOR);
		break;

	case PLAYER_O_WON_STATE:
		render_gameover_state(renderer, game, &PLAYER_O_COLOR);
		break;

	case TIE_STATE:
		render_gameover_state(renderer, game, &TIE_COLOR);
		break;

	default: {}
	}
}