#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Board.hpp"

Board::Board() {
    state = MENU;
    preset = ONE_ZERO;
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

void Board::set_state(BoardState state) { state = state; }

void Board::next_preset() { }

void Board::event_listener() {

}
