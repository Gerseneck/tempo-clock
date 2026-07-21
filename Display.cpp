#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Display.hpp"

Display::Display(Board* board, LiquidCrystal* lcd) {
    board = board;
    lcd = lcd;
}

void Display::render() {
    switch (board->get_state()) {
        case MENU:
            _render_menu();
            break;
    }
}

void Display::_render_menu() {
    lcd->setCursor(0, 1);
    lcd->print("Select Mode");
}
