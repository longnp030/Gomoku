#pragma once
#ifndef GAME_H
#define GAME_H

const int  N = 12; // rows and columns
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 720
const float cell_width = SCREEN_WIDTH / N;
const float cell_height = SCREEN_HEIGHT / N;

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2

#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4

//static int player_X_score = 0, player_O_score = 0;

struct game_t {
	int board[N * N];
	int player;
	int state;
};

struct next {
	int next_row;
	int next_column;
};

#endif //GAME_H