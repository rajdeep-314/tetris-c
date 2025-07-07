/* utils.c
*
* Various utility functions, mostly related to handling output on the screen and
* keyboard interactions. For more info about what each function does, check out
* the corresponding header file.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>


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


int kp(int usec) {
	struct timeval tv;
	fd_set fds;

	tv.tv_sec = 0;
	tv.tv_usec = usec;

	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);

	return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}


void set_terminal_mode() {
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


void restore_terminal_mode() {
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


int randint(int a, int b) {
	return (a + random() % (b - a + 1));
}

