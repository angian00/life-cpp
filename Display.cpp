
#include "Display.h"
#include "GameState.h"


const int FRAME_DELAY = 250;

const char * WINDOW_TITLE = "Game of Life";


struct Color {
    u_char r;
    u_char g;
    u_char b;
};

const Color emptyColor = { 0xcc, 0xcc, 0xff };
const Color aliveColor = { 0xff, 0x33, 0x33 };


Display::Display(size_t nTilesX, size_t nTilesY) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        //TODO: throw
        printf("[ERROR] SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return;
    }
    
    size_t screenWidth = nTilesX * TILES2PX;
    size_t screenHeight = nTilesY * TILES2PX;
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("[ERROR] Window could not be created! SDL Error: %s\n", SDL_GetError());
        return;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("[ERROR] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return;
    }
}


Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Display::update(GameState & gameState) {
    for (size_t x=0; x < gameState.width; x++) {
        for (size_t y=0; y < gameState.height; y++) {
            Color currColor;
            if (gameState.getValue(x, y)) {
                currColor = aliveColor;
            } else {
                currColor = emptyColor;
            }

            SDL_SetRenderDrawColor(renderer, currColor.r, currColor.g, currColor.b, 255);
            
            SDL_Rect cellRect;
            cellRect.x = x * TILES2PX;
            cellRect.y = y * TILES2PX;
            cellRect.w = TILES2PX;
            cellRect.h = TILES2PX;

            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    SDL_RenderPresent(renderer);
}


bool Display::pollEvents() {
    SDL_Event sdlEvent;

    while(SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_WINDOWEVENT_CLOSE:
                return true;

        default:
            //SDL_Log("Window %d got unknown event %d\n", wEvent.window.windowID, wEvent.window.event);
            break;
        }
    }

    SDL_Delay(FRAME_DELAY);
    return false;
}