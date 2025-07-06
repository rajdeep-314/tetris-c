#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "utils.h"


void show_bar(int n) {
	for (int i = 0; i < n; i++)
		putchar('.');
}

void show_bars(int bars[], int n) {
	for (int i = 0; i < n; i++) {
		show_bar(bars[i]);
		putchar('\n');
		fflush(stdout);
	}
}

int main() {
	printf("Tetris - Testing\n");
	printf("\nSome animation.\n");

	sleep(1);
	hide_cursor();

	int nbars = 20,
		lim = 20;

	int bars[nbars],
		ds[nbars];

	for (int i = 0; i < nbars; i++) {
		bars[i] = i;
		ds[i] = 2*(i % 2) - 1;
	}


	char c;
	while (1) {
		cls();
		c = getch();
		if (c == 'x')
			break;

		// updating  the bars
		for (int i = 0; i < nbars; i++) {
			bars[i] += ds[i];
			if ((bars[i] > lim) || (bars[i] < 0)) {
				ds[i] *= -1;
				bars[i] += ds[i];
			}
		}

		show_bars(bars, nbars);

		usleep(20000);		// delay
	}

	show_cursor();

	return 0;
}

