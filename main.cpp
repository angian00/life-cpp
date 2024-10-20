#include "Display.h"
#include "GameState.h"

const int N_TILES_X = 80;
const int N_TILES_Y = 60;


int main(int argc, char* args[]) {
    GameState gameState { N_TILES_X, N_TILES_Y };
    gameState.init_random();
    //gameState.init_test();
    
    //gameState.dump();

    Display display(N_TILES_X, N_TILES_Y);
    
    bool mustQuit = false;
    while (!mustQuit) {
        gameState.evolve();
        display.update(gameState);

        mustQuit = display.pollEvents();
    }
}