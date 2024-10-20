#ifndef DISPLAY_H
#define DISPLAY_H

#include "GameState.h"

#include <SDL2/SDL.h>

class Display {
    public:
        Display(size_t nTilesX, size_t nTilesY);
        ~Display();

        void update(GameState &gameState);
        bool pollEvents();

    private:
        const static int TILES2PX = 10;

        SDL_Window *window;
        SDL_Renderer* renderer;
};

#endif
