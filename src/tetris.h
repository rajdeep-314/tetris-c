#ifndef INCLUDED_TETRIS_TETRIS_
#define INCLUDED_TETRIS_TETRIS_


// Directions.
typedef enum {
	UP, DOWN, LEFT, RIGHT
} dir;


// Is the cell at (x, y) part of the current block?
int in_block(int x, int  y);

// Is the cell at (x, y) in bounds?
int in_bounds(int x, int y);

// Is the cell at (x, y) empty (in the grid)?
int is_empty(int x, int y);

// Is the cell at (x, y) occupied (in the grid)?
int is_occupied(int x, int y);

// Show a cell at y'th column in the x'th row with the left and right
// characters being c1 and c2, respectively.
void show_cell_char(int x, int y, char c1, char c2);

// Show [] at (x, y).
void show_cell(int x, int y);

// Erase at (x, y).
void erase(int x, int y);

// Remove up to lim ful rows and manipulate the rest of the grid accordingly.
void remove_rows(int lim);

// Initialize the falling block wtih the block type b.
void init_block(int b);

// The number of steps for the current block to drops down.
int steps_to_drop();

// Show the cells that make up the block.
void show_block();

// Hides the cells that make up the block.
void hide_block();

// Shows the block's shadow (where it will drop to).
void show_shadow();

// Erases the block's shadow.
void erase_shadow();

// Tells if making a move in the direction d is valid (no obstacles).
int valid_move(dir d);

// Hide the current block, move it in the direction d and then
// show the new block.
// NOTE:	Assumes that the move is valid.
void refresh_block(dir d);

// Drop the block down as far as it can go.
void drop_block();

// Is it possible to rotate the current block clockwise by 90 degrees?
int valid_rotation();

// Rotate the current block clockwise by 90 degrees.
void rotate();

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

// The pause screen.
void paused();

// The "Game Over" screen.
void game_over();


#endif
