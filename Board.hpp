#ifndef BOARD_HPP
#define BOARD_HPP

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Game.hpp"

enum BoardState {
    MENU,
    CUSTOM_T,
    CUSTOM_I,
    CUSTOM_D,
    IN_GAME,
    PAUSED,
    BLUE_WIN,
    RED_WIN,
};

struct ClockTime {
    // time in milliseconds
    unsigned int time;
    unsigned int increment;
    unsigned int delay;
};

enum Preset : int {
    ONE_ZERO,
    TWO_ZERO,
    THREE_ZERO,
    THREE_TWO,
    FIVE_ZERO,
    FIVE_THREE,
    TEN_ZERO,
    TEN_FIVE,
    FIFTEEN_TEN,
    THIRTY_ZERO,
    THIRTY_TWENTY,
    THIRTY_TWENTY_D,
    CUSTOM,
};

const int BUTTON_A_PIN = A5;
const int BUTTON_B_PIN = A4;
const int BUTTON_C_PIN = A3;
const int BUTTON_D_PIN = A2;

class Board {
    public:
        Board();
        void event_listener();
        BoardState get_state();
        ClockTime get_clock_time();
        arduino::String get_clock_time_string();
        Preset get_preset();
        arduino::String get_preset_string();
        void set_state(BoardState state);
    private:
        BoardState state;
        ClockTime time;
        Preset preset;
        Game game;

        void _menu_event_listener(int* presses);
        void _next_preset(bool previous);
        void _start_game();
        void _toggle_custom_states();
        void _inc_time(bool dec);
};

#endif
