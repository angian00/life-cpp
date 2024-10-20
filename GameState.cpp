#include "GameState.h"

#include <random>

bool randomBool();


void GameState::init_random() {
    for (size_t x=0; x < width; x++) {
        for (size_t y=0; y < height; y++) {
            setValue(x, y, randomBool());
        }
    }
}

void GameState::init_test() {
    init_beehive(5, 5);
    init_beacon(15, 10);
    init_glider(20, 15);
}

void GameState::init_beehive(size_t x, size_t y) {
    setValue(x+1, y, true);
    setValue(x+2, y, true);
    setValue(x, y+1, true);
    setValue(x+3, y+1, true);
    setValue(x+1, y+2, true);
    setValue(x+2, y+2, true);
}

void GameState::init_beacon(size_t x, size_t y) {
    setValue(x, y, true);
    setValue(x+1, y, true);
    setValue(x, y+1, true);
    setValue(x+1, y+1, true);

    setValue(x+2, y+2, true);
    setValue(x+3, y+2, true);
    setValue(x+2, y+3, true);
    setValue(x+3, y+3, true);
}

void GameState::init_glider(size_t x, size_t y) {
    setValue(x+2, y, true);
    setValue(x, y+1, true);
    setValue(x+2, y+1, true);
    setValue(x+1, y+2, true);
    setValue(x+2, y+2, true);
}


void GameState::evolve() {
    bool *new_cells = old_cells;
    old_cells = cells;
    cells = new_cells;

    for (size_t x=0; x < width; x++) {
        for (size_t y=0; y < height; y++) {

            uint n_live_neighbours = 0;

            for (int dx=-1; dx <= 1; dx++) {
                for (int dy=-1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0)
                        continue;

                    int nx = (x + dx);
                    if (nx < 0)
                        nx += width;
                    else if ((size_t)nx >= width)
                        nx -= width;

                    int ny = (y + dy);
                    if (ny < 0)
                        ny += height;
                    else if ((size_t)ny >= height)
                        ny -= height;

                    if (old_cells[nx * height + ny])
                        n_live_neighbours ++;
                }
            }

            // -- Game of Live rules [https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life] --
            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            // Any live cell with two or three live neighbours lives on to the next generation.
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

            bool is_alive = ( (n_live_neighbours == 3) || ( (n_live_neighbours == 2) && (old_cells[x * height + y])) );
            setValue(x, y, is_alive);
        }
    }
}


void GameState::dump() {
    printf("GameState dump: \n");
    for (size_t x=0; x < width; x++) {
        for (size_t y=0; y < height; y++) {
            printf(" %d", getValue(x, y));
        }

        printf("\n");
    }
    printf("\n");
}


bool randomBool() {
    return ( rand() > (RAND_MAX / 2) );
}
