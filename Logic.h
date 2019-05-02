#pragma once
#ifndef LOGIC_H
#define LOGIC_H

#include "Game.h"

/*struct Coord {
	int next_row;
	int next_column;

	Coord check_block(Coord coord, game_t *game, int player);
};*/

//int check_playerX_won(game_t *game, int player);
int check_3(next *_next, game_t *game, int player);
//int check_3_block(next *_next, game_t *game, int player);
void click_on_cell(game_t *game, int row, int column);

#endif //LOGIC_H