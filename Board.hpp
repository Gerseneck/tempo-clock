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

enum Preset {
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

const std::map<Preset, std::string> preset_strings = {
    {ONE_ZERO, "1+0"},
    {TWO_ZERO, "2+0"},
    {THREE_ZERO, "3+0"},
    {THREE_TWO, "3+2"},
    {FIVE_ZERO, "5+0"},
    {FIVE_THREE, "5+3"},
    {TEN_ZERO, "10+0"},
    {TEN_FIVE, "10+5"},
    {FIFTEEN_TEN, "15+10"},
    {THIRTY_ZERO, "30+0"},
    {THIRTY_TWENTY, "30+20"},
    {THIRTY_TWENTY_D, "30|20d"},
};

const std::map<Preset, ClockTime> preset_vals = {
    {ONE_ZERO, ClockTime{1 * 60 * 1000, 0, 0}},
    {TWO_ZERO, ClockTime{2 * 60 * 1000, 0, 0}},
    {THREE_ZERO, ClockTime{3 * 60 * 1000, 0, 0}},
    {THREE_TWO, ClockTime{3 * 60 * 1000, 2 * 1000, 0}},
    {FIVE_ZERO, ClockTime{5 * 60 * 1000, 0, 0}},
    {FIVE_THREE, ClockTime{5 * 60 * 1000, 3 * 1000, 0}},
    {TEN_ZERO, ClockTime{10 * 60 * 1000, 0, 0}},
    {TEN_FIVE, ClockTime{10 * 60 * 1000, 5 * 1000, 0}},
    {FIFTEEN_TEN, ClockTime{15 * 60 * 1000, 10 * 1000, 0}},
    {THIRTY_ZERO, ClockTime{30 * 60 * 1000, 0, 0}},
    {THIRTY_TWENTY, ClockTime{30 * 60 * 1000, 20 * 1000, 0}},
    {THIRTY_TWENTY_D, ClockTime{30 * 60 * 1000, 0, 20 * 1000}},
};


class Board {
    public:
        Board();
        void event_listener();
        BoardState get_state();
        ClockTime get_clock_time();
        Preset get_preset();
        void set_state(BoardState state);
        void next_preset();
    private:
        BoardState state;
        ClockTime time;
        Preset preset;
        Game game;
};

#endif
