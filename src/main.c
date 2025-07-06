#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"
#include "tetris.h"



int main() {
	// Setting up a signal handler for SIGINT.
	signal(SIGINT, exiting);

	startup();
	load_board();

	sleep(1);

	exiting();

	return 0;
}

