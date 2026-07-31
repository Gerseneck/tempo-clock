#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Board.hpp"

const int LCD_PIN_RS = 12;
const int LCD_PIN_ENABLE = 11;
const int LCD_PIN_D4 = 5;
const int LCD_PIN_D5 = 4;
const int LCD_PIN_D6 = 3;
const int LCD_PIN_D7 = 2;

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

class Display {
    public:
        Display(Board& board);
        void init();
        void render();
    private:
        Board& board;
        LiquidCrystal lcd;
        BoardState state;

        void _render_menu();
        void _render_wait();
        void _render_time();
        void _render_winner();
        void _render_stopped();
};

#endif
