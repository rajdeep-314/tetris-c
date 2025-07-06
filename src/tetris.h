#ifndef INCLUDED_TETRIS_TETRIS_
#define INCLUDED_TETRIS_TETRIS_


// The startup sequence.
void startup();

// Display the boarders (instantaneously, no animation).
void display_borders();

// Animation sequence for loading the board.
void load_board();

// The exit screen and restoring the terminal state.
void exiting();

// Restoring the terminal state.
void restore();


#endif
