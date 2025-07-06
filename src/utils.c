#include <unistd.h>
#include <termios.h>
#include <sys/select.h>


int kbhit(int usec) {
    struct timeval tv;
    fd_set readfds;
    
	tv.tv_sec = 0;
    tv.tv_usec = usec;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
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

