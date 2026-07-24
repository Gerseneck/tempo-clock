#include <Arduino.h>
#include <LiquidCrystal.h>

#include <set>

#include "Board.hpp"

Board::Board() {
    state = MENU;
    preset = ONE_ZERO;
    time = get_clock_time();
    last_press = millis();
    held = false;
    red = Player{0, 0, 0, 0};
    blue = Player{0, 0, 0, 0};
}

BoardState Board::get_state() { return state; }

Preset Board::get_preset() { return preset; }

arduino::String Board::get_preset_string() {
    switch (preset) {
        case ONE_ZERO: 
            return "1+0";
        case TWO_ZERO: 
            return "2+0";
        case THREE_ZERO: 
            return "3+0";
        case THREE_TWO: 
            return "3+2";
        case FIVE_ZERO: 
            return "5+0";
        case FIVE_THREE: 
            return "5+3";
        case TEN_ZERO: 
            return "10+0";
        case TEN_FIVE: 
            return "10+5";
        case FIFTEEN_TEN: 
            return "15+10";
        case THIRTY_ZERO: 
            return "30+0";
        case THIRTY_TWENTY: 
            return "30+20";
        case THIRTY_TWENTY_D: 
            return "30|20d";
        case CUSTOM:
            return "Custom";
    };
}

ClockTime Board::get_clock_time() {
    switch (preset) {
        case ONE_ZERO: 
            return ClockTime{1 * 60 * 1000, 0, 0};
        case TWO_ZERO: 
            return ClockTime{2 * 60 * 1000, 0, 0};
        case THREE_ZERO: 
            return ClockTime{3 * 60 * 1000, 0, 0};
        case THREE_TWO: 
            return ClockTime{3 * 60 * 1000, 2 * 1000, 0};
        case FIVE_ZERO: 
            return ClockTime{5 * 60 * 1000, 0, 0};
        case FIVE_THREE: 
            return ClockTime{5 * 60 * 1000, 3 * 1000, 0};
        case TEN_ZERO: 
            return ClockTime{10 * 60 * 1000, 0, 0};
        case TEN_FIVE: 
            return ClockTime{10 * 60 * 1000, 5 * 1000, 0};
        case FIFTEEN_TEN: 
            return ClockTime{15 * 60 * 1000, 10 * 1000, 0};
        case THIRTY_ZERO: 
            return ClockTime{30 * 60 * 1000, 0, 0};
        case THIRTY_TWENTY: 
            return ClockTime{30 * 60 * 1000, 20 * 1000, 0};
        case THIRTY_TWENTY_D: 
            return ClockTime{30 * 60 * 1000, 0, 20 * 1000};
        case CUSTOM:
            return time;
    }
}

arduino::String Board::get_clock_time_string() {
    return arduino::String((std::to_string(time.time / 60000) + "+" + std::to_string(time.increment / 1000) + "|" + std::to_string(time.delay / 1000) + "d").c_str());
}

void Board::_next_preset(bool previous) {
    int preset_int = static_cast<int>(preset);

    if (previous) {
        preset_int--;

        if (preset_int < ONE_ZERO) { return; }
    } else {
        preset_int++;

        if (preset_int > CUSTOM) { return; }
    }

    preset = static_cast<Preset>(preset_int);
    time = preset != CUSTOM ? get_clock_time() : ClockTime{0, 0, 0};
}

void Board::event_listener() {
    int button_presses[4] = {
        digitalRead(BUTTON_A_PIN),
        digitalRead(BUTTON_B_PIN),
        digitalRead(BUTTON_C_PIN),
        digitalRead(BUTTON_D_PIN),
    };

    std::set<int> button_volt(button_presses, button_presses + 4);
    bool pressed = button_volt.size() > 1;

    if (pressed) {
        if (millis() - 200 < last_press) { return; }

        if (!held && millis() - 750 < last_press) { return; }

        if (millis() - 2000 > last_press) { held = true; }

        last_press = millis();
    } else {
        held = false;
        last_press = 0;
    }

    switch (state) {
        case MENU:
        case CUSTOM_T:
        case CUSTOM_I:
        case CUSTOM_D:
            _menu_event_listener(button_presses);
            break;
    }
}

void Board::_inc_time(bool dec) {
    if (state == CUSTOM_T) {
        time.time += dec ? -60000 : 60000;
    } else if (state == CUSTOM_I) {
        time.increment += dec ? -1000 : 1000;
    } else if (state == CUSTOM_D) {
        time.delay += dec ? -1000 : 1000;
    }
}

void Board::_start_game() {
    state = IN_GAME;

    unsigned long start_time = millis();
    red.start_time = start_time;
    blue.start_time = start_time;
}

void Board::_toggle_custom_states() {
    if (preset != CUSTOM) { return; }

    if (state == MENU) {
        state = CUSTOM_T;
    } else if (state == CUSTOM_T) {
        state = CUSTOM_I;
    } else if (state == CUSTOM_I) {
        state = CUSTOM_D;
    } else if (state == CUSTOM_D) {
        _start_game();
    } else {
        state = CUSTOM_T;
    }
}

void Board::_menu_event_listener(int* presses) {
    if (presses[0]) { 
        if (state == MENU) {
            _next_preset(false);
            return;
        }
        _inc_time(false);
    };
    if (presses[1]) {
        if (preset == CUSTOM) {
            _toggle_custom_states();
            return;
        }
        _start_game();
    }
    if (presses[2]) {}
    if (presses[3]) {
        if (state == MENU) {
            _next_preset(true);
            return;
        }
        _inc_time(true);
    };
}
