// AssPhalt96.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Logic.h"
#include "Rendering.h"

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Fuck it !" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Window *window = SDL_CreateWindow("XO Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cerr << "Fuck it !" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		std::cerr << "Fuck it !" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Surface *surface = IMG_Load("menu.png");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Event event;
	while (1) {
		int flag = 0;
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		while (SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_d:
					flag = 1;
					break;
				case SDLK_s:
					flag = 2;
					break;
				}
			default: {}
			}
			if (flag > 0) break;
		}

		game_t game;
		for (int i = 0; i < N * N; i++)
			game.board[i] = EMPTY;
		game.player = PLAYER_X;
		game.state = RUNNING_STATE;

		next _next;

		while (game.state != QUIT_STATE) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					game.state = QUIT_STATE;
					SDL_DestroyRenderer(renderer);
					renderer = NULL;
					SDL_DestroyWindow(window);
						window = NULL;
						SDL_Quit();
					break;

				case SDL_MOUSEBUTTONDOWN:
					click_on_cell(&game,
						event.button.y / cell_height,
						event.button.x / cell_width);

					if (flag == 2) {
						int row, column;
						while (1) {

							row = event.button.y / cell_height + (rand() % (2 - 0 + 1) + 0) - 1;
							column = event.button.x / cell_width + (rand() % (2 - 0 + 1) + 0) - 1;

							if (check_3(&_next, &game, PLAYER_X)) {
								std::cout << _next.next_row << ' ' << _next.next_column << std::endl;
								if (game.board[_next.next_row * N + _next.next_column] != EMPTY) {

									row = event.button.y / cell_height + (rand() % (2 - 0 + 1) + 0) - 1;
									column = event.button.x / cell_width + (rand() % (2 - 0 + 1) + 0) - 1;
									if (game.board[row * N + column] == EMPTY) {
										break;
									}
									else continue;

								}
								else {
									row = _next.next_row;
									column = _next.next_column;
									break;
								}
							}

							if (game.board[row * N + column] == EMPTY) {
								break;
							}
							else continue;
						}
						
						click_on_cell(&game, row, column);
					}

					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: 
						game.state = QUIT_STATE;
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						SDL_DestroyWindow(window);
						window = NULL;
						SDL_Quit();
						break;
					}
					break;

				default: {}
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			render_game(renderer, &game);
			SDL_RenderPresent(renderer);
		}
	}

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	//TTF_Quit();
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
