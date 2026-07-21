#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Board.hpp"

Board::Board() {
    state = MENU;
    preset = ONE_ZERO;
}

BoardState Board::get_state() { return state; }

Preset Board::get_preset() { return preset; }

ClockTime Board::get_clock_time() { return time; }

void Board::set_state(BoardState state) { state = state; }

void Board::next_preset() {

}

void Board::event_listener() {

}
