// Screen utilities.

#include <stdio.h>


void cls() {
	printf("\e[2J\e[0;0H");
}

void putcat(int x, int y, char c) {
	printf("\e[%d;%dH", x, y);
	putchar(c);
}
void hide_cursor() {
	printf("\e[?25l");
}

void show_cursor() {
	printf("\e[?25h");
}

