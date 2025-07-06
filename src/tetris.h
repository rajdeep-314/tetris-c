#ifndef INCLUDED_TETRIS_TETRIS_
#define INCLUDED_TETRIS_TETRIS_


// Initialize the grid to being completely empty.
void init_grid();

// Display the grid.
void show_grid();

// The startup sequence.
void startup();

// Display the boarders (instantaneously, no animation).
void show_borders();

// Animation sequence for loading the board.
void load_board();

// The exit screen and restoring the terminal state.
void exiting();

// Refreshes the screen.
void refresh();

// Restoring the terminal state.
void restore();

// For testing keyboard actions.
void test_update(int x);

#endif
