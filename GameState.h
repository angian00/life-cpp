#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <cstddef>
#include <cstdio>

class GameState {
    public:
        GameState(const size_t width, const size_t height): width(width), height{height} {
            cells = new bool[width * height] {};
            old_cells = new bool[width * height] {};
        }

        inline bool getValue(size_t x, size_t y) {
            //printf("getValue(%lu, %lu) \n", x, y);
            return cells[x * height + y];
        }



        void evolve();
        void dump();

        void init_random();

        void init_test();
        void init_beehive(size_t x, size_t y);
        void init_beacon(size_t x, size_t y);
        void init_glider(size_t x, size_t y);

        const size_t width;
        const size_t height;


    private:
        inline void setValue(size_t x, size_t y, bool value) {
            //printf("setValue(%lu, %lu) \n", x, y);
            cells[x * height + y] = value;
        }


        bool *cells;
        bool *old_cells;
};

#endif
