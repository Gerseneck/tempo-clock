#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Display.hpp"
#include "Board.hpp"

Display::Display(Board& board, LiquidCrystal& lcd) : board(board), lcd(lcd) {
    state = MENU;
}

void Display::render() {
    if (board.get_state() != state) {
        // clear lcd when state changes and redraw
        lcd.clear();
        state = board.get_state();
    }

    switch (board.get_state()) {
        case MENU:
        case CUSTOM_T:
        case CUSTOM_I:
        case CUSTOM_D:
            _render_menu();
            break;
    }
}

void Display::_render_menu() {
    lcd.setCursor(0, 0);
    if (board.get_state() == MENU) {
        lcd.print("Select Mode:");
        lcd.setCursor(0, 1);
        lcd.print(board.get_preset_string());
    } else {
        lcd.print("Custom ");
        switch (board.get_state()) {
            case CUSTOM_T:
                lcd.print("Time");
                break;
            case CUSTOM_I:
                lcd.print("Inc");
                break;
            case CUSTOM_D:
                lcd.print("Delay");
                break;
            default:
                break;
        }
        lcd.setCursor(0, 1);
        lcd.print(board.get_clock_time_string());
    }
    lcd.display();
}
