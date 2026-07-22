#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Game.hpp"

enum BoardState {
    MENU,
    WAITING,
    IN_GAME,
    PAUSED,
    BLUE_WIN,
    RED_WIN,
};

struct ClockTime {
    // time in milliseconds
    unsigned long time;
    unsigned long increment;
    unsigned long delay;
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
    NONE,
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
        Preset get_preset();
        arduino::String get_preset_string();
        void set_state(BoardState state);
        void next_preset();
    private:
        BoardState state;
        ClockTime time;
        Preset preset;
        Game game;

        void _menu_event_listener(int* presses);
};

#endif
