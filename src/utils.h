#ifndef INCLUDED_TETRIS_UTILS_
#define INCLUDED_TETRIS_UTILS_


// Clear the screen using an ANSI escape sequence.
void cls();

// Put the character c at (x, y) - in the y'th column in the x'th row.
void putcat(int x, int y, char c);

// Hide the cursor.
void hide_cursor();

// Show the cursor.
void show_cursor();

// Returns 1 if some key has been pressed. Waits for usec microseconds before
// determining that no key has been pressed.
int kp(int usec);

// Set the terminal mode to make it such that
//	1. The typed input is not echoed.
//	2. The typed input is made available as it is typed (there is no
//	   need to hit RETURN).
void set_terminal_mode();

// Sets the terminal mode to make it such that
//	1. The typed input IS echoed.
//	2. RETURN needs to be pressed to make the input available to the
//	   program.
void restore_terminal_mode();

// Returns a random integer in the interval [a, b].
int randint(int a, int b);


#endif
