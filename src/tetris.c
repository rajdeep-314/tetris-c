#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"


// Parameters.
#define ROWS 30
#define COLS 40				// 20 x 2 chars per block
#define OFF_X 5				// x offset (vertical)
#define OFF_Y 20			// y offset (horizontal)


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


void display_borders() {
	// Side lines.
	for (int i = 0; i < ROWS; i++) {
		putcat(OFF_X + i, OFF_Y - 1, '|');
		putcat(OFF_X + i, OFF_Y - 2, '<');
		putcat(OFF_X + i, OFF_Y + COLS + 1, '|');
		putcat(OFF_X + i, OFF_Y + COLS + 2, '>');
	}

	// Bottom line.
	for (int i = 0; i < COLS; i++) {
		putcat(OFF_X + ROWS, OFF_Y + i, '_');
		putcat(OFF_X + ROWS + 1, OFF_Y + COLS - 1 - i, '^');
	}
}


void load_board() {
	int dt = 31415;

	cls();
	
	// Side lines.
	for (int i = 0; i < ROWS; i++) {
		putcat(OFF_X + i, OFF_Y - 1, '|');
		putcat(OFF_X + i, OFF_Y - 2, '<');
		putcat(OFF_X + i, OFF_Y + COLS + 1, '|');
		putcat(OFF_X + i, OFF_Y + COLS + 2, '>');
		fflush(stdout);
		usleep(dt);
	}

	// Bottom line.
	for (int i = 0; i < COLS; i++) {
		putcat(OFF_X + ROWS, OFF_Y + i, '_');
		putcat(OFF_X + ROWS + 1, OFF_Y + COLS - 1 - i, '^');
		fflush(stdout);
		usleep(dt/2);
	}
}


void restore() {
	restore_terminal_mode();
	show_cursor();
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

