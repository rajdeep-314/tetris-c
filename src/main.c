#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"
#include "tetris.h"


#define UPOLL 750                   // Polling interval in microseconds.
#define CDT   145                   // Number of cycles for each CFT reduction.
#define CFTD  1                     // CFT reduction per reduction.
#define MIN_CFT 150                 // Minimum CFT (max difficulty).


extern int CFTI, CFT;
extern unsigned long long acc;


int main() {
    // Initializations
    signal(SIGINT, exiting);        // Signal handler for SIGINT.
    srand(time(0));                 // Random seed.
    init_params();                  // Initialize CFT and the grid.
    make_new_block();               // The first block.
    int time = 0;                   // Initialize the time.

    // Starting animations.
    startup();                      // The starting screen.
    load_board();                   // Board loading animation.
    show_shadow();                  // Display the initial block's shadow.
    show_block();                   // Display the initial block.
    show_score();                   // Display the score.


    char input;
    int wcount = 0;


    // Loop.
    while (1) {
        acc++;
        wcount++;

        // Increasing the difficulty.
        if (wcount >= CDT && CDT >= CFTD + MIN_CFT) {
            wcount -= CDT;
            CFT -= CFTD;
        }

        // If it's time for a new block to arrive (add here).
        if (!(valid_move(DOWN))) {
            add_block_to_grid();
            make_new_block();
            show_score(acc / 100);
        }

        // If a key is pressed.
        if (kp(UPOLL)) {
            input = lowercase(getchar());

            // P : Pause.
            if (input == 'p')
                paused();

            // A - Left.
            else if (input == 'a') {
                if (valid_move(LEFT))
                    refresh_block(LEFT);
            }

            // D - Right.
            else if (input == 'd') {
                if (valid_move(RIGHT))
                    refresh_block(RIGHT);
            }

            // S - Down.
            else if (input == 's') {
                if (valid_move(DOWN))
                    refresh_block(DOWN);
            }

            // A - Rotate clockwise.
            else if (input == 'w') {
                if (valid_rotation())
                    rotate();
            }

            // Spacebar - Drop down.
            else if (input == ' ') {
                drop_block();
            }

            // R - Restart.
            else if (input == 'r') {
                restart();
            }

            // T - Refresh.
            else if (input == 't') {
                cls();
                refresh_grid();
            }

            // X : Exit.
            else if (input == 'x')
                exiting();

        }

        // If it's time for the block to fall.
        if (time >= CFT) {
            time -= CFT;
            if (valid_move(DOWN))            // Should always be true (I think).
                refresh_block(DOWN);
        }
        

        usleep(UPOLL);      // Delay.
        time++;
    }

    exiting();              // The exiting screen.

    return 0;
}

