#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Display.hpp"
#include "Board.hpp"

Display::Display(Board& board) : board(board), lcd(LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7) {
    state = MENU;
}

void Display::init() {
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.print("Tempo Clock");
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
            _render_time();
            break;
        case STOPPED:
            _render_stopped();
            break;
        case RED_WIN:
        case BLUE_WIN:
            _render_time();
            _render_winner();
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

void Display::_render_time() {
    lcd.setCursor(2, 0);
    lcd.print(board.get_player_time('r'));
    lcd.setCursor(16 - board.get_player_time('b').length() - 2, 1);
    lcd.print(board.get_player_time('b'));
}

void Display::_render_winner() {
    if (board.get_state() == RED_WIN) {
        lcd.setCursor(0, 0);
    } else if (board.get_state() == BLUE_WIN) {
        lcd.setCursor(15, 1);
    }
    lcd.write('W');
}

void Display::_render_stopped() {
    lcd.setCursor(2, 0);
    lcd.print("Press A/B to");
    lcd.setCursor(1, 1);
    lcd.print("select winner!");
}
