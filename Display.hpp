#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Board.hpp"

class Display {
    public:
        Display(Board& board, LiquidCrystal& lcd);
        void render();
    private:
        Board& board;
        LiquidCrystal& lcd;
        BoardState state;

        void _render_menu();
        void _render_wait();
        void _render_game();
};

#endif
