#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Board.hpp"

Board::Board() {
    state = MENU;
    preset = ONE_ZERO;
    time = get_clock_time();
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
        case NONE:
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
        case NONE:
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

        if (preset_int > NONE) { return; }
    }

    preset = static_cast<Preset>(preset_int);
    time = get_clock_time();
}

void Board::event_listener() {
    int button_presses[4] = {
        digitalRead(BUTTON_A_PIN),
        digitalRead(BUTTON_B_PIN),
        digitalRead(BUTTON_C_PIN),
        digitalRead(BUTTON_D_PIN),
    };

    switch (state) {
        case MENU:
            _menu_event_listener(button_presses);
            break;
    }
}

void Board::_start_game() {}

void Board::_toggle_custom_states() {
    if (preset != NONE) { return; }

    if (state == MENU) {
        state = CUSTOM_T;
    } else if (state == CUSTOM_T) {
        state = CUSTOM_I;
    } else if (state == CUSTOM_I) {
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
        // inc time logic for custom
    };
    if (presses[1]) {
        if (preset == NONE) {
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
        // dec time logic for custom
    };

    Serial.println(get_preset_string());
    Serial.println(get_clock_time_string());
}
