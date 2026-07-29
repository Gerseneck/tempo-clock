#ifndef BOARD_HPP
#define BOARD_HPP

#include <Arduino.h>
#include <LiquidCrystal.h>

const int BOARD_REFRESH_DELAY = 100;

enum BoardState : int {
    MENU,
    CUSTOM_T,
    CUSTOM_I,
    CUSTOM_D,
    WAITING,
    IN_GAME,
    PAUSED,
    STOPPED, // get screen to choose winner
    BLUE_WIN,
    RED_WIN,
};

struct ClockTime {
    // time in milliseconds
    unsigned int time;
    unsigned int increment;
    unsigned int delay;
};

struct Player {
    unsigned int time_left;
    unsigned int delay;
    bool is_turn;
    unsigned int turn_number;
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
        arduino::String get_player_time(char player);
        void set_state(BoardState state);
    private:
        BoardState state;
        ClockTime time;
        Preset preset;

        unsigned long last_press;
        bool held;

        Player red;
        Player blue;
        bool paused;

        // button listeners
        void _button_listener();
        void _menu_button_listener(int* presses);
        void _wait_button_listener(int* presses);
        void _game_button_listener(int* presses);
        void _paused_button_listener(int* presses);
        void _win_button_listener(int* presses);
        // menu functions
        void _next_preset(bool previous);
        void _start_game();
        void _toggle_custom_states();
        void _inc_clock(bool dec);
        // game functions
        void _game_event_listener();
        void _add_inc(Player *p);
};

#endif
