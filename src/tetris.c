#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"


// Parameters.
#define HEIGHT 30
#define WIDTH 40
#define ROWS 30
#define COLS 20
#define OFF_X 5
#define OFF_Y 20


// The grid.
int grid[ROWS][COLS];
int h = 0;


void init_grid() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			grid[i][j] = 0;
}


void show_grid() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (grid[i][j] != 0) {
				putcat(OFF_X + i, OFF_Y + 2*j, '[');
				putcat(OFF_X + i, OFF_Y + 2*j + 1, ']');
			}
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


void refresh() {
	cls();
	show_borders();
	show_grid();
	fflush(stdout);
}


void restore() {
	restore_terminal_mode();
	show_cursor();
}

void test_update(int x) {
	if (x > 0 && h == ROWS)
		return;
	if (x < 0 && h == 0)
		return;
	
	if (x > 0) {
		for (int i = 1; i <= x; i++)
			for (int j = 0; j < COLS; j++)
				grid[ROWS - h - i][j] = 1;
	}
	else if (x < 0) {
		for (int i = 0; i < -1*x; i++)
			for (int j = 0; j < COLS; j++)
				grid[ROWS - h + i][j] = 0;
	}

	h += x;
	if (h < 0)
		h = 0;
	else if (h > ROWS)
		h = ROWS;
}


void exiting() {
	cls();

	printf("\n\n\n\t\t\tThanks for playing! :)\n");
	printf("\n\t\t\t\t\t\t- Rajdeep\n");

	sleep(2);
	cls();
	restore();
	
	exit(0);
}

