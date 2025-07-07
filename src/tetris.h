#ifndef INCLUDED_TETRIS_TETRIS_
#define INCLUDED_TETRIS_TETRIS_


// Directions.
typedef enum {
	UP, DOWN, LEFT, RIGHT
} dir;



// Show the cell ([]) at the y'th column in the x'th row.
void show_cell(int x, int y);

// Hide the cell at the y'th column in the x'th row.
void hide_cell(int x, int y);

// Initialize the falling block wtih the block type b.
void init_block(int b);

// Show the cells that make up the block.
void show_block();

// Hides the cells that make up the block.
void hide_block();

// Is the cell at (x, y) part of the current block?
int in_block(int x, int  y);

// Is the cell at (x, y) in bounds?
int in_bounds(int x, int y);

// Is the cell at (x, y) empty (in the grid)?
int is_empty(int x, int y);

// Is the cell at (x, y) occupied (in the grid)?
int is_occupied(int x, int y);

// Tells if making a move in the direction d is valid (no obstacles).
int valid_move(dir d);

// Hide the current block, move it in the direction d and then
// show the new block.
// NOTE:	Assumes that the move is valid.
void refresh_block(dir d);

// Drop the block down as far as it can go.
void drop_block();

// Update the grid with the cells that make up the block.
// NOTE:	Also checks for game over condtion.
void add_block_to_grid();

// Generate a new block.
void make_new_block();

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

// Refreshes the grid.
void refresh_grid();

// Restoring the terminal state.
void restore();

// The "Game Over" screen.
void game_over();


#endif
