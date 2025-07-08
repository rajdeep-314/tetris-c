#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "utils.h"
#include "tetris.h"


// Parameters.
#define HEIGHT 20
#define WIDTH 24
#define ROWS 20
#define COLS 12
#define OFF_X 4
#define OFF_Y 15


// The grid.
int grid[ROWS][COLS];

// The one falling block.
int block[4][2];
int n_block_types = 7;
int block_type;
int ori;


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


void show_cell_char(int x, int y, char c1, char c2) {
	if (!(in_bounds(x, y)))
		return;
	putcat(OFF_X + x, OFF_Y + 2*y, c1);
	putcat(OFF_X + x, OFF_Y + 2*y + 1, c2);
}


void show_cell(int x, int y) {
	show_cell_char(x, y, '[', ']');
}

void erase(int x, int y) {
	show_cell_char(x, y, ' ', ' ');
}


void remove_rows(int lim) {
	int count = 0;

	for (int i = ROWS - 1; i >= 0; i--) {
		if (count >= lim)
			break;
		// Is row i full?
		int full = 1;
		for (int j = 0; j < COLS; j++)
			if (grid[i][j] == 0) {
				full = 0;
				break;
			}
		
		// If it's full, drop down everything above it by one row.
		if (full) {
			count++;
			for (int k = i - 1; k >= 0; k--)
				for (int l = 0; l < COLS; l++)
					grid[k + 1][l] = grid[k][l];

			i++;		// To check the new row.
			refresh_grid();
		}
	}
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


int steps_to_drop() {
	int steps = INT_MAX;

	int x, y, j;
	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];

		for (j = x; j < ROWS; j++)
			if (grid[j][y] != 0)
				break;
		
		steps = steps <= j - x - 1 ? steps : j - x - 1;
	}

	return steps;
}


void show_block() {
	for (int i = 0; i < 4; i++)
		show_cell(block[i][0], block[i][1]);
}


void hide_block() {
	int x, y;
	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];
		erase(x, y);
	}
}


void show_shadow() {
	int steps = steps_to_drop();

	int x, y;
	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];

		show_cell_char(x + steps, y, '(', ')');
	}
}


void hide_shadow() {
	int steps = steps_to_drop();
	
	int x, y;
	for (int i = 0; i < 4; i++) {
		x = block[i][0];
		y = block[i][1];

		erase(x + steps, y);
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
	hide_shadow();
	hide_block();

	int dx, dy;

	dx = dir_to_dx(d);
	dy = dir_to_dy(d);

	// Updating the block.
	for (int i = 0; i < 4; i++) {
		block[i][0] += dx;
		block[i][1] += dy;
	}

	show_shadow();
	show_block();
	fflush(stdout);
}


void drop_block() {
	while (valid_move(DOWN))
		refresh_block(DOWN);
}


// Was very painful to write this.
int* rot_delta(int btype, int ori) {
	if (0 >= btype || btype > n_block_types || ori < 0 || ori >= 4)
		return NULL;

	int* arr = (int*) malloc(8 * sizeof(int));

	if (btype == 1)
		for (int i = 0; i < 8; i++)	arr[i] = 0;

	else if (btype == 2) {
		if (ori == 0) {
			arr[0] = 1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = -1;
			arr[6] = -2;
			arr[7] = -2;
		}
		else if (ori == 1) {
			arr[0] = 1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = 1;
			arr[6] = -2;
			arr[7] = 2;
		}
		else if (ori == 2) {
			arr[0] = -1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = 1;
			arr[6] = 2;
			arr[7] = 2;
		}
		else {
			arr[0] = -1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = -1;
			arr[6] = 2;
			arr[7] = -2;
		}
	}

	else if (btype == 3) {
		if (ori == 0) {
			arr[0] = 0;
			arr[1] = 0;
			arr[2] = 1;
			arr[3] = -1;
			arr[4] = -1;
			arr[5] = -1;
			arr[6] = -2;
			arr[7] = 0;
		}
		else if (ori == 1) {
			arr[0] = 0;
			arr[1] = 0;
			arr[2] = -1;
			arr[3] = -1;
			arr[4] = -1;
			arr[5] = 1;
			arr[6] = 0;
			arr[7] = 2;
		}
		else if (ori == 2) {
			arr[0] = 0;
			arr[1] = 0;
			arr[2] = -1;
			arr[3] = 1;
			arr[4] = 1;
			arr[5] = 1;
			arr[6] = 2;
			arr[7] = 0;
		}
		else {
			arr[0] = 0;
			arr[1] = 0;
			arr[2] = 1;
			arr[3] = 1;
			arr[4] = 1;
			arr[5] = -1;
			arr[6] = 0;
			arr[7] = -2;
		}
	}

	else if (btype == 4) {
		if (ori == 0) {
			arr[0] = -1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = -1;
			arr[6] = 0;
			arr[7] = -2;
		}
		else if (ori == 1) {
			arr[0] = 1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = 1;
			arr[6] = -2;
			arr[7] = 0;
		}
		else if (ori == 2) {
			arr[0] = 1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = 1;
			arr[6] = 0;
			arr[7] = 2;
		}
		else {
			arr[0] = -1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = -1;
			arr[6] = 2;
			arr[7] = 0;
		}
	}

	else if (btype == 5) {
		if (ori == 0) {
			arr[0] = 1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = -1;
			arr[6] = 0;
			arr[7] = -2;
		}
		else if (ori == 1) {
			arr[0] = 1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = 1;
			arr[6] = -2;
			arr[7] = 0;
		}
		else if (ori == 2) {
			arr[0] = -1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = 1;
			arr[6] = 0;
			arr[7] = 2;
		}
		else {
			arr[0] = -1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = -1;
			arr[6] = 2;
			arr[7] = 0;
		}
	}

	else if (btype == 6) {
		if (ori == 0) {
			arr[0] = 1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = -1;
			arr[6] = -2;
			arr[7] = 0;
		}
		else if (ori == 1) {
			arr[0] = 1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = 1;
			arr[6] = 0;
			arr[7] = 2;
		}
		else if (ori == 2) {
			arr[0] = -1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = 1;
			arr[6] = 2;
			arr[7] = 0;
		}
		else {
			arr[0] = -1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = -1;
			arr[6] = 0;
			arr[7] = -2;
		} }

	else if (btype == 7) {
		if (ori == 0) {
			arr[0] = -1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = -1;
			arr[6] = -1;
			arr[7] = -1;
		}
		else if (ori == 1) {
			arr[0] = 1;
			arr[1] = 1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = -1;
			arr[6] = -1;
			arr[7] = 1;
		}
		else if (ori == 2) {
			arr[0] = 1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = -1;
			arr[5] = 1;
			arr[6] = 1;
			arr[7] = 1;
		}
		else {
			arr[0] = -1;
			arr[1] = -1;
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = 1;
			arr[5] = 1;
			arr[6] = 1;
			arr[7] = -1;
		}
	}

	return arr;
}

int valid_rotation() {
	if (block_type == 1)
		return 0;

	int* rd = rot_delta(block_type, ori);
	
	int x, y;
	int nblock[4][2];
	
	for (int i = 0; i < 4; i++) {
		nblock[i][0] = block[i][0] + rd[2*i];
		nblock[i][1] = block[i][1] + rd[2*i + 1];
	}

	// Checking if each of the new blocks is inside the bounds
	// and in an empty cell.
	for (int i = 0; i < 4; i++) {
		x = nblock[i][0];
		y = nblock[i][1];
		if (!(in_bounds(x, y) && is_empty(x, y))) {
			free(rd);
			return 0;
		}
	}

	free(rd);
	return 1;
}


void rotate() {
	hide_block();
	hide_shadow();
	
	if (block_type == 1)
		return;

	int* rd = rot_delta(block_type, ori);

	for (int i = 0; i < 4; i++) {
		block[i][0] += rd[2*i];
		block[i][1] += rd[2*i + 1];
	}

	free(rd);

	// Updating the orientation.
	ori = (ori + 1) % 4;

	show_shadow();
	show_block();
	fflush(stdout);
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

	remove_rows(4);
}


void make_new_block() {
	block_type = randint(1, n_block_types);
	init_block(block_type);
	ori = 0;
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


void paused() {
	cls();
	show_borders();
	setc(OFF_X + ROWS/2 - 3, OFF_Y + COLS/2 + 2);
	printf("PAUSED");
	setc(OFF_X + ROWS/2 - 1, OFF_Y + 3);
	printf("Press P to resume.");
	setc(OFF_X + ROWS/2, OFF_Y + 3);
	printf("Press X to exit.");
	fflush(stdout);

	char input;
	
	while (1) {
		if (kp(500)) {
			input = lowercase(getchar());

			if (input == 'x')
				exiting();

			else if (input == 'p') {
				cls();
				refresh_grid();
				show_shadow();
				show_block();
				fflush(stdout);
				return;
			}
		}
	}
}


void game_over() {
	cls();
	
	printf("\n\nGAME OVER!!\n\n");
	sleep(2);

	exiting();
}

