#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"
#include "tetris.h"


// Polling interval.
#define UPOLL 1000


int main() {
	// Initializations
	signal(SIGINT, exiting);		// Signal handler for SIGINT.
	init_grid();					// Initialize the grid to empty.

	// Starting animations.
	startup();				// The starting screen.
	load_board();			// Board loading animation.


	int paused = 0;
	char input;

	// Loop.
	while (1) {
		// If a key is pressed.
		if (kp(UPOLL)) {
			input = getchar();
			input = 65 <= input && input <= 90 ? input ^ 32 : input;

			// Spacebar : Pause.
			if (input == ' ')
				paused = 1 - paused;

			// X : Exit.
			else if (input == 'x')
				exiting();

			else if (input == 's') {
				test_update(-1);
				refresh();
			}

			else if (input == 'w') {
				test_update(1);
				refresh();
			}
		}

		usleep(UPOLL);		// Delay.
	}

	exiting();				// The exiting screen.

	return 0;
}

