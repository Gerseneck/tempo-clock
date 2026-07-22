#include <Arduino.h>
#include <LiquidCrystal.h>

#include <cstddef>

#include "Display.hpp"
#include "Board.hpp"

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
    lcd->setCursor(0, 0);
    if (board->get_preset() != NULL) {
        lcd->print("Select Mode:");
        lcd->setCursor(0, 1);
        lcd->print(preset_strings[board->get_preset()]);
    } else {
        lcd->print("Custom");
        // more logic here to determine mode
        lcd->setCursor(0, 1);
    }
}
