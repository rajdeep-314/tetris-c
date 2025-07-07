#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"
#include "tetris.h"


#define UPOLL 750					// Polling interval in microseconds.
#define CFT   314					// Fall time in number of while loop cycles.


int main() {
	// Initializations
	signal(SIGINT, exiting);					// Signal handler for SIGINT.
	init_grid();								// Initialize the grid to empty.
	srand(time(0));								// Random seed.
	make_new_block();							// The first block.
	int time = 0;

	// Starting animations.
	startup();				// The starting screen.
	load_board();			// Board loading animation.
	show_block();			// Display the initial block.


	int paused = 0;
	char input;

	// Loop.
	while (1) {
		// If it's time for a new block to arrive (add here).
		if (!(valid_move(DOWN))) {
			add_block_to_grid();
			make_new_block();
		}

		// If a key is pressed.
		if (kp(UPOLL)) {
			input = getchar();
			input = 65 <= input && input <= 90 ? input ^ 32 : input;

			// Spacebar : Pause.
			if (input == ' ')
				paused = 1 - paused;

			// A - Left.
			else if (input == 'a') {
				if (valid_move(LEFT))
					refresh_block(LEFT);
			}

			// D - Right.
			else if (input == 'd') {
				if (valid_move(RIGHT))
					refresh_block(RIGHT);
			}

			// S - Down.
			else if (input == 's') {
				if (valid_move(DOWN))
					refresh_block(DOWN);
			}

			// Z - Drop down.
			else if (input == 'z') {
				drop_block();
			}

			// R - Restart.
			else if (input == 'r') {
				init_grid();
				make_new_block();
				refresh_grid();
			}

			// X : Exit.
			else if (input == 'x')
				exiting();

		}

		// If it's time for the block to fall.
		if (time >= CFT) {
			time -= CFT;
			if (valid_move(DOWN))			// Should always be true (I think).
				refresh_block(DOWN);
		}
		

		usleep(UPOLL);		// Delay.
		time++;
	}

	exiting();				// The exiting screen.

	return 0;
}

