#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Display.hpp"
#include "Board.hpp"

Display::Display(Board& board, LiquidCrystal& lcd) : board(board), lcd(lcd) {
    state = MENU;
}

void Display::render() {
    // clear lcd and redraw
    if (board.get_state() != state) {
        lcd.clear();
        state = board.get_state();
    }
    if (board.get_redraw_screen()) {
        lcd.clear();
        board.reset_redraw_screen();
    }

    switch (board.get_state()) {
        case MENU:
        case CUSTOM_T:
        case CUSTOM_I:
        case CUSTOM_D:
            _render_menu();
            break;
        case WAITING:
            _render_wait();
            break;
        case IN_GAME:
        case PAUSED:
        case RED_WIN:
        case BLUE_WIN:
            _render_game();
            break;
        case STOPPED:
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

void Display::_render_wait() {
    lcd.setCursor(2, 0);
    lcd.print("Press A/B to");
    lcd.setCursor(5, 1);
    lcd.print("start!");
}

void Display::_render_game() {
    lcd.setCursor(1, 0);
    lcd.print(board.get_player_time('r'));
    lcd.setCursor(16 - board.get_player_time('b').length() - 1, 1);
    lcd.print(board.get_player_time('b'));
}
