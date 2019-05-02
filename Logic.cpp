#include "pch.h"
#include "Logic.h"
#include "Game.h"

#include <cstring>

/*bool check_X(game_t *game, int i, int j) {
	if (i >= 0 && i < N && j >= 0 && j < N) {
		if (game->board[i * N + j] == PLAYER_X);
			return true;
		return false;
	}
	return false;
}*/

/*bool check_X(game_t *game, int i, int j) {
	if (i >= 0 && i < N && j >= 0 && j < N) {
		if (game->board[i * N + j] == PLAYER_O)
			return true;
		return false;
	}
	return false;
}*/

void switch_player(game_t *game) {
	if (game->player == PLAYER_X)
		game->player = PLAYER_O;
	else if (game->player == PLAYER_O)
		game->player = PLAYER_X;
}

/*int check_player_won(bool(*point)(int, int)) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// Check row
			if (point(i, j) == true && point(i + 1, j) == true && point(i + 2, j) == true && point(i + 3, j) == true && point(i + 4, j) == true) {
				return 1;
			}

			// Check column
			if (point(i, j) == true && point(i, j + 1) == true && point(i, j + 2) == true && point(i, j + 3) == true && point(i, j + 4) == true) {
				return 1;
			}

			// Check diagonal from upper left to lower right
			if (point(i, j) == true && point(i + 1, j + 1) == true && point(i + 2, j + 2) == true && point(i + 3, j + 3) == true && point(i + 4, j + 4) == true) {
				return 1;
			}

			// Check diagonal from upper right to lower left
			if (point(i, j) == true && point(i - 1, j + 1) == true && point(i - 2, j + 2) == true && point(i - 3, j + 3) == true && point(i - 4, j + 4) == true) {
				return 1;
			}
		}
	}
	return 0;
}*/

/*Coord check_block(Coord coord, game_t *game, int player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// Check row
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j] == player && game->board[(i + 2) * N + j] == player) {
				coord.next_row = i + 3;
				coord.next_column = j;
				return coord;
			}

			// Check column
			if (game->board[i * N + j] == player && game->board[i * N + j + 1] == player && game->board[i * N + j + 2] == player) {
				coord.next_row = i;
				coord.next_column = j + 3;
				return coord;
			}

			// Check diagonal from upper left to lower right
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j + 1] == player && game->board[(i + 2) * N + j + 2] == player) {
				coord.next_row = i + 3;
				coord.next_column = j + 3;
				return coord;
			}

			// Check diagonal from upper right to lower left
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j + 1] == player && game->board[(i - 2) * N + j + 2] == player) {
				coord.next_row = i - 3;
				coord.next_column = j + 3;
				return coord;
			}
		}
	}
	return coord;
}*/

int check_3(next *_next, game_t *game, int player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// Check row
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j] == player && game->board[(i + 2) * N + j] == player) {
				_next->next_row = i + 3;
				_next->next_column = j;
				return 1;
			}

			// Check column
			if (game->board[i * N + j] == player && game->board[i* N + j + 1] == player && game->board[i * N + j + 2] == player) {
				_next->next_row = i;
				_next->next_column = j + 3;
				return 1;
			}
			
			// Check diagonal from upper left to lower right
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j + 1] == player && game->board[(i + 2) * N + j + 2] == player) {
				_next->next_row = i + 3;
				_next->next_column = j + 3;
				return 1;
			}

			// Check diagonal from lower right to upper left
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j - 1] == player && game->board[(i - 2) * N + j - 2] == player) {
				_next->next_row = i - 3;
				_next->next_column = j - 3;
				return 1;
			}

			// Check diagonal from upper right to lower left
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j - 1] == player && game->board[(i + 2) * N + j - 2] == player) {
				_next->next_row = i + 3;
				_next->next_column = j - 3;
				return 1;
			}

			// Check diagonal from lower left to upper right
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j + 1] == player && game->board[(i - 2) * N + j + 2] == player) {
				_next->next_row = i - 3;
				_next->next_column = j + 3;
				return 1;
			}
		}
	}
	return 0;
}

/*int check_3_block(next *_next, game_t *game, int player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// Check row
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j] == player && game->board[(i + 2) * N + j] == player && game->board[(i - 1) * N + j] == player) {
				_next->next_row = i + 3;
				_next->next_column = j;
				return 1;
			}

			// Check row
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j] == player && game->board[(i + 2) * N + j] == player && game->board[(i + 3) * N + j] == player) {
				_next->next_row = i - 1;
				_next->next_column = j;
				return 1;
			}

			// Check column
			if (game->board[i * N + j] == player && game->board[i * N + j + 1] == player && game->board[i * N + j + 2] == player && game->board[i * N + j - 1] == player) {
				_next->next_row = i;
				_next->next_column = j + 3;
				return 1;
			}

			// Check column
			if (game->board[i * N + j] == player && game->board[i* N + j + 1] == player && game->board[i * N + j + 2] == player && game->board[i * N + j + 3] == player) {
				_next->next_row = i;
				_next->next_column = j - 1;
				return 1;
			}

			// Check diagonal from upper left to lower right
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j + 1] == player && game->board[(i + 2) * N + j + 2] == player && game->board[(i - 1) * N + j - 1] == player) {
				_next->next_row = i + 3;
				_next->next_column = j + 3;
				return 1;
			}

			// Check diagonal from upper left to lower right
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j + 1] == player && game->board[(i + 2) * N + j + 2] == player && game->board[(i + 3) * N + j + 3] == player) {
				_next->next_row = i - 1;
				_next->next_column = j - 1;
				return 1;
			}

			// Check diagonal from lower right to upper left
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j - 1] == player && game->board[(i - 2) * N + j - 2] == player && game->board[(i + 1) * N + j + 1] == player) {
				_next->next_row = i - 3;
				_next->next_column = j - 3;
				return 1;
			}

			// Check diagonal from lower right to upper left
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j - 1] == player && game->board[(i - 2) * N + j - 2] == player && game->board[(i - 3) * N + j - 3] == player) {
				_next->next_row = i + 1;
				_next->next_column = j + 1;
				return 1;
			}

			// Check diagonal from upper right to lower left
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j - 1] == player && game->board[(i + 2) * N + j - 2] == player && game->board[(i - 1) * N + j + 1] == player) {
				_next->next_row = i + 3;
				_next->next_column = j - 3;
				return 1;
			}

			// Check diagonal from upper right to lower left
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j - 1] == player && game->board[(i + 2) * N + j - 2] == player && game->board[(i + 3) * N + j - 3] == player) {
				_next->next_row = i - 1 ;
				_next->next_column = j + 1;
				return 1;
			}

			// Check diagonal from lower left to upper right
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j + 1] == player && game->board[(i - 2) * N + j + 2] == player && game->board[(i + 1) * N + j - 1] == player) {
				_next->next_row = i - 3;
				_next->next_column = j + 3;
				return 1;
			}
			// Check diagonal from lower left to upper right
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j + 1] == player && game->board[(i - 2) * N + j + 2] == player && game->board[(i - 3) * N + j + 3] == player) {
				_next->next_row = i + 1;
				_next->next_column = j - 1;
				return 1;
			}
		}
	}
	return 0;
}*/

int check_player_won(game_t *game, int player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// Check row
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j] == player && game->board[(i + 2) * N + j] == player && game->board[(i + 3) * N + j] == player && game->board[(i + 4) * N + j] == player)
				return 1;

			// Check column
			if (game->board[i * N + j] == player && game->board[i* N + j + 1] == player && game->board[i * N + j + 2] == player && game->board[i * N + j + 3] == player && game->board[i * N + j + 4] == player)
				return 1;

			// Check diagonal from upper left to lower right
			if (game->board[i * N + j] == player && game->board[(i + 1) * N + j + 1] == player && game->board[(i + 2) * N + j + 2] == player && game->board[(i + 3) * N + j + 3] == player && game->board[(i + 4) * N + j + 4] == player)
				return 1;

			// Check diagonal from upper right to lower left
			if (game->board[i * N + j] == player && game->board[(i - 1) * N + j + 1] == player && game->board[(i - 2) * N + j + 2] == player && game->board[(i - 3) * N + j + 3] == player && game->board[(i - 4) * N + j + 4] == player)
				return 1;
		}
	}
	return 0;
}

/*int check_playerX_won(game_t *game, int player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// Check row
			if (game->board[i * N + j] == PLAYER_X && game->board[(i + 1) * N + j] == PLAYER_X && game->board[(i + 2) * N + j] == PLAYER_X && game->board[(i + 3) * N + j] == PLAYER_X && game->board[(i + 4) * N + j] == PLAYER_X)
				return 1;

			// Check column
			if (game->board[i * N + j] == PLAYER_X && game->board[i* N + j + 1] == PLAYER_X && game->board[i * N + j + 2] == PLAYER_X && game->board[i * N + j + 3] == player && game->board[i * N + j + 4] == PLAYER_X)
				return 1;

			// Check diagonal from upper left to lower right
			if (game->board[i * N + j] == PLAYER_X && game->board[(i + 1) * N + j + 1] == PLAYER_X && game->board[(i + 2) * N + j + 2] == PLAYER_X && game->board[(i + 3) * N + j + 3] == PLAYER_X  && game->board[(i + 4) * N + j + 4] == PLAYER_X)
				return 1;

			// Check diagonal from upper right to lower left
			if (game->board[i * N + j] == PLAYER_X && game->board[(i - 1) * N + j + 1] == PLAYER_X && game->board[(i - 2) * N + j + 2] == PLAYER_X && game->board[(i - 3) * N + j + 3] == PLAYER_X && game->board[(i - 4) * N + j + 4] == PLAYER_X)
				return 1;
		}
	}
	return 0;
}*/

int count_cells(const int *board, int cell) {
	int count = 0;
	for (int i = 0; i < N * N; ++i) {
		if (board[i] == cell)
			count++;
	}
	return count;
}

bool gameover_condition(game_t *game) {
	if (check_player_won(game, PLAYER_X)) {
		game->state = PLAYER_X_WON_STATE;
		return 1;
	}
	else if (check_player_won(game, PLAYER_O)) {
		game->state = PLAYER_O_WON_STATE;
		return 1;
	}
	else if (count_cells(game->board, EMPTY) == 0) {
		game->state = TIE_STATE;
		return 1;
	}
	return 0;
}

void player_turn(game_t *game, int row, int column) {
	if (game->board[row * N + column] == EMPTY) {
		game->board[row * N + column] = game->player;
		switch_player(game);
		gameover_condition(game);
	}
}

void reset_game(game_t *game) {
	game->player = PLAYER_X;
	game->state = RUNNING_STATE;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		game->board[i * N + j] = EMPTY;
}

void click_on_cell(game_t *game, int row, int column) {
	if (game->state == RUNNING_STATE) {
		player_turn(game, row, column);
	}
	else {
		reset_game(game);
	}
}