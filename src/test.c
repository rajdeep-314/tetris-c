// Testing keyboard interactions.

#include <stdio.h>
#include <unistd.h>
#include "utils.h"


#define UDELTA 100


// clear the screen and display the "matrix"
void display(int n, int rows) {
	cls();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < n; j++)
			putchar('.');
		putchar('\n');
	}

	fflush(stdout);
}


void starta() {
	cls();
	
	printf("Testing keyboard interactions\n");
	printf("\nControls:\n");
	printf("\tA - decrease width\n");
	printf("\tD - increase width\n");
	printf("\tS - increase height\n");
	printf("\tW - decrease height\n");
	printf("\tX - exit\n");
	printf("\n\nStarting soon...\n");

	fflush(stdout);

	sleep(2);
}


int main() {
	int n = 5;
	int rows = 1;

	starta();

	set_terminal_mode();
	hide_cursor();

	// need to display outside the loop once because the
	// other "refreshes" only happen during keyboard interactions
	display(n, rows);

	char c;
	while (1) {
		if (kp(UDELTA)) {
			scanf("%c", &c);

			if (c == 'a' || c == 'A') {
				n = n <= 0 ? 0 : n - 1;
				display(n, rows);
			}
			else if (c == 'd' || c == 'D') {
				n = n >= 40 ? 40 : n + 1;
				display(n, rows);
			}
			else if (c == 's' || c == 'S') {
				rows = rows >= 20 ? 20 : rows + 1;
				display(n, rows);
			}
			else if (c == 'w' || c == 'W') {
				rows = rows <= 0 ? 0 : rows - 1;
				display(n, rows);
			}
			
			else if (c == 'x' || c == 'X')
					break;
		}

		usleep(UDELTA);		// delay
	}
	
	restore_terminal_mode();
	show_cursor();

	return 0;
}

