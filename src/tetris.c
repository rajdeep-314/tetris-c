#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "utils.h"
#include "tetris.h"


// Parameters.
#define HEIGHT 22
#define WIDTH 30
#define ROWS 22
#define COLS 15
#define OFF_X 3
#define OFF_Y 15


// The grid.
int grid[ROWS][COLS];
int h = 0;

// The one falling block.
int block[4][2];
int n_block_types = 7;
int block_type;


void show_cell(int x, int y) {
	if (x < 0 || x > ROWS - 1)	return;
	if (y < 0 || y > COLS - 1)	return;
	putcat(OFF_X + x, OFF_Y + 2*y, '[');
	putcat(OFF_X + x, OFF_Y + 2*y + 1, ']');
}


void hide_cell(int x, int y) {
	if (x < 0 || x > ROWS - 1)	return;
	if (y < 0 || y > COLS - 1)	return;
	putcat(OFF_X + x, OFF_Y + 2*y, ' ');
	putcat(OFF_X + x, OFF_Y + 2*y + 1, ' ');
}


void init_block(int b) {
	// Top-left corner.
	int x, y;
	// [][]
	// [][]

	if (b == 1) {
		x = -1;
		y = randint(3, COLS - 5);

		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x;
		block[1][1] = y + 1;
		block[2][0] = x + 1;
		block[2][1] = y;
		block[3][0] = x + 1;
		block[3][1] = y + 1;
	}

	// []
	// []
	// []
	// []
	else if (b == 2) {
		x = -1;
		y = randint(3, COLS - 4);
		
		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x + 1;
		block[1][1] = y;
		block[2][0] = x + 2;
		block[2][1] = y;
		block[3][0] = x + 3;
		block[3][1] = y;
		
	}

	//   [][]
	// [][]
	else if (b == 3) {
		x = -1;
		y = randint(4, COLS - 5);

		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x;
		block[1][1] = y + 1;
		block[2][0] = x + 1;
		block[2][1] = y;
		block[3][0] = x + 1;
		block[3][1] = y - 1;
	}

	// [][]
	//   [][]
	else if (b == 4) {
		x = -1;
		y = randint(3, COLS - 6);

		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x;
		block[1][1] = y + 1;
		block[2][0] = x + 1;
		block[2][1] = y + 1;
		block[3][0] = x + 1;
		block[3][1] = y + 2;
	}

	// []
	// []
	// [][]
	else if (b == 5) {
		x = -1;
		y = randint(3, COLS - 5);
		
		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x + 1;
		block[1][1] = y;
		block[2][0] = x + 2;
		block[2][1] = y;
		block[3][0] = x + 2;
		block[3][1] = y + 1;
	}

	//   []
	//   []
	// [][]
	else if (b == 6) {
		x = -1;
		y = randint(4, COLS - 4);

		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x + 1;
		block[1][1] = y;
		block[2][0] = x + 2;
		block[2][1] = y;
		block[3][0] = x + 2;
		block[3][1] = y - 1;
	}

	// [][][]
	//   []
	else if (b == 7) {
		x = -1;
		y = randint(4, COLS - 5);

		block[0][0] = x;
		block[0][1] = y;
		block[1][0] = x;
		block[1][1] = y + 1;
		block[2][0] = x;
		block[2][1] = y + 2;
		block[3][0] = x + 1;
		block[3][1] = y + 1;
	}
}


void show_block() {
	int x, y;
	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];
		show_cell(x, y);
	}
}


void hide_block() {
	int x, y;
	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];
		hide_cell(x, y);
	}
}

int dir_to_dx(dir d) {
	if (d == LEFT || d == RIGHT)
		return 0;
	if (d == UP)
		return -1;
	if (d == DOWN)
		return 1;
	return -1;
}


int dir_to_dy(dir d) {
	if (d == UP || d == DOWN)
		return 0;
	if (d == LEFT)
		return -1;
	if (d == RIGHT)
		return 1;
	return -1;
}


int in_block(int x, int  y) {
	for (int i = 0; i < 4; i++)
		if (grid[i][0] == x && grid[i][1] == y)
			return 1;

	return 0;
}


int in_bounds(int x, int y) {
	return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}

int is_empty(int x, int y) {
	return (grid[x][y] == 0);
}

int is_occupied(int x, int y) {
	return (!(is_empty(x, y)));
}


int valid_move(dir d) {
	int x, y, dx, dy;

	dx = dir_to_dx(d);
	dy = dir_to_dy(d);

	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];

		// Coordinates after moving in d.
		x += dx;
		y += dy;

		// All of the new coordinates must be inside the bound and there
		// shouldn't be a cell already present at them.
		if (!(in_bounds(x, y) && is_empty(x, y)))
			return 0;
	}

	return 1;
}


// NOTE:	This function assumes that a move in direction d
// is possible.
void refresh_block(dir d) {
	hide_block();

	int dx, dy;

	dx = dir_to_dx(d);
	dy = dir_to_dy(d);

	// Updating the block.
	for (int i = 0; i < 4; i++) {
		block[i][0] += dx;
		block[i][1] += dy;
	}

	show_block();
	fflush(stdout);
}


void drop_block() {
	while (valid_move(DOWN))
		refresh_block(DOWN);
}


void add_block_to_grid() {
	int x, y;

	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];

		if (!(in_bounds(x, y)))
			game_over();

		grid[x][y] = 1;
	}
}


void make_new_block() {
	init_block(randint(1, n_block_types));
}


void init_grid() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			grid[i][j] = 0;
}


void show_grid() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (grid[i][j] != 0)
				show_cell(i, j);
		}
	}
}


void startup() {
	set_terminal_mode();
	hide_cursor();

	cls();

	char* text[5] =
		{ " _____    _        _",
		  "|_   _|__| |_ _ __(_)___",
		  "  | |/ _ \\ __| '__| / __|",
		  "  | |  __/ |_| |  | \\__ \\",
		  "  |_|\\___|\\__|_|  |_|___/" };
	int dt = 5000;

	char* iter;
	for (int i = 0; i < 5; i++) {
		iter = text[i];
		while (*iter != '\0') {
			putchar(*(iter++));
			fflush(stdout);
			usleep(dt);
		}
		putchar('\n');
	}

	puts("\nLoading...\n");
	sleep(2);
}


void show_borders() {
	// Side lines.
	for (int i = 0; i < HEIGHT; i++) {
		putcat(OFF_X + i, OFF_Y - 2, '|');
		putcat(OFF_X + i, OFF_Y - 3, '<');
		putcat(OFF_X + i, OFF_Y + WIDTH + 1, '|');
		putcat(OFF_X + i, OFF_Y + WIDTH + 2, '>');
	}

	// Bottom line.
	for (int i = 0; i < WIDTH + 2; i++) {
		putcat(OFF_X + HEIGHT, OFF_Y - 1 + i, '-');
		putcat(OFF_X + HEIGHT + 1, OFF_Y + WIDTH - i, '^');
	}
}


void load_board() {
	int dt = 31415;

	cls();
	
	// Side lines.
	for (int i = 0; i < HEIGHT; i++) {
		putcat(OFF_X + i, OFF_Y - 2, '|');
		putcat(OFF_X + i, OFF_Y - 3, '<');
		putcat(OFF_X + i, OFF_Y + WIDTH + 1, '|');
		putcat(OFF_X + i, OFF_Y + WIDTH + 2, '>');
		fflush(stdout);
		usleep(dt);
	}

	// Bottom line.
	for (int i = 0; i < WIDTH + 2; i++) {
		putcat(OFF_X + HEIGHT, OFF_Y - 1 + i, '-');
		putcat(OFF_X + HEIGHT + 1, OFF_Y + WIDTH - i, '^');
		fflush(stdout);
		usleep(dt/2);
	}
}


void refresh_grid() {
	cls();
	show_borders();
	show_grid();
	fflush(stdout);
}


void restore() {
	restore_terminal_mode();
	show_cursor();
}


void exiting() {
	cls();

	printf("\n\n\n\t\t\tThanks for playing! :)\n");
	printf("\n\t\t\t\t\t\t- Rajdeep\n");

	sleep(1);
	cls();
	restore();
	
	exit(0);
}

void game_over() {
	cls();
	
	printf("\n\nGAME OVER!!\n\n");
	sleep(2);

	exiting();
}

