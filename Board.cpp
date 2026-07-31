#include <Arduino.h>
#include <LiquidCrystal.h>

#include <set>
#include <climits>

#include "Board.hpp"

Board::Board() {
    state = MENU;
    preset = ONE_ZERO;
    time = get_clock_time();
    last_press = millis();
    held = false;
    red = Player{0, 0, 0, 0};
    blue = Player{0, 0, 0, 0};
    redraw_screen = false;
}

BoardState Board::get_state() { return state; }

Preset Board::get_preset() { return preset; }

bool Board::get_redraw_screen() { return redraw_screen; }
void Board::reset_redraw_screen() { redraw_screen = false; }

arduino::String Board::get_preset_string() {
    switch (preset) {
        case ONE_ZERO: 
            return arduino::String("1+0");
        case TWO_ZERO: 
            return arduino::String("2+0");
        case THREE_ZERO: 
            return arduino::String("3+0");
        case THREE_TWO: 
            return arduino::String("3+2");
        case FIVE_ZERO: 
            return arduino::String("5+0");
        case FIVE_THREE: 
            return arduino::String("5+3");
        case TEN_ZERO: 
            return arduino::String("10+0");
        case TEN_FIVE: 
            return arduino::String("10+5");
        case FIFTEEN_TEN: 
            return arduino::String("15+10");
        case THIRTY_ZERO: 
            return arduino::String("30+0");
        case THIRTY_TWENTY: 
            return arduino::String("30+20");
        case THIRTY_TWENTY_D: 
            return arduino::String("30|20d");
        case CUSTOM:
            return arduino::String("Custom");
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

arduino::String Board::get_player_time(char player) {
    // single digit seconds we do tenth of second
    // else print full 
    Player *p;
    if (player == 'r') {
        p = &red;
    } 
    if (player == 'b') {
        p = &blue;
    }

    unsigned int t = p->time_left;
    unsigned short h = p->time_left / 3600000;
    unsigned short m = (p->time_left - h * 3600000) / 60000;
    unsigned short s = (p->time_left - h * 3600000 - m * 60000) / 1000;
    unsigned short ds = (p->time_left - h * 360000 - m * 60000 - s * 1000) / 100;

    std::string player_time = "";

    if (h > 0) {
        player_time.append(std::to_string(h) + ":");
    }
    if (m > 0 || h > 0) {
        std::string min = std::to_string(m);
        if (m < 10 && h > 0) {
            min.insert(0, 1, '0');
        }
        player_time.append(min.append(":"));
    }
    std::string sec = std::to_string(s);
    if ((h > 0 || m > 0) && s < 10) {
        sec.insert(0, 1, '0');
    }
    player_time.append(sec);
    if (h < 1 && m < 1) {
        player_time.append("." + std::to_string(ds));
    }

    return arduino::String(player_time.c_str());
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
    switch (state) {
        case IN_GAME:
            _game_event_listener();
            break;
        default:
            break;
    }

    _button_listener();
}

void Board::_button_listener() {
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
        redraw_screen = true;
    } else {
        held = false;
        last_press = 0;
    }

    switch (state) {
        case MENU:
        case CUSTOM_T:
        case CUSTOM_I:
        case CUSTOM_D:
            _menu_button_listener(button_presses);
            break;
        case WAITING:
            _wait_button_listener(button_presses);
            break;
        case IN_GAME:
            _game_button_listener(button_presses);
            break;
        case PAUSED:
            _paused_button_listener(button_presses);
            break;
        case STOPPED:
            _stopped_button_listener(button_presses);
            break;
        case BLUE_WIN:
        case RED_WIN:
            _win_button_listener(pressed);
            break;
    }
}

void Board::_inc_clock(bool dec) {
    if (state == CUSTOM_T) {
        time.time += dec ? -60000 : 60000;
    } else if (state == CUSTOM_I) {
        time.increment += dec ? -1000 : 1000;
    } else if (state == CUSTOM_D) {
        time.delay += dec ? -1000 : 1000;
    }
}

void Board::_start_game() {
    state = WAITING;
    
    red.time_left = time.time;
    blue.time_left = time.time;
    red.delay = time.delay;
    blue.delay = time.delay;
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

void Board::_menu_button_listener(int* presses) {
    if (presses[0]) { 
        if (state == MENU) {
            _next_preset(false);
            return;
        }
        _inc_clock(false);
    };
    if (presses[1]) {
        if (preset == CUSTOM) {
            _toggle_custom_states();
            return;
        }
        _start_game();
    }
    if (presses[2]) {
        if (preset == CUSTOM) {
            state = MENU;
            _next_preset(false);
        }
    }
    if (presses[3]) {
        if (state == MENU) {
            _next_preset(true);
            return;
        }
        _inc_clock(true);
    };
}


void Board::_wait_button_listener(int* presses) {
    if (presses[0]) {
        state = IN_GAME;
        red.is_turn = true;
        blue.is_turn = false;
    } else if (presses[3]) {
        state = IN_GAME;
        red.is_turn = false;
        blue.is_turn = true;
    }
    if (presses[2]) {
        state = MENU;
    }
}

void Board::_paused_button_listener(int* presses) {
    if (presses[1]) {
        state = IN_GAME;
    }
    if (presses[2]) {
        state = STOPPED;
    }
}

void Board::_win_button_listener(bool key_pressed) {
    if (!key_pressed) {
        return;
    }

    state = MENU;
}

void Board::_game_button_listener(int* presses) {
    if (presses[0]) {
        if (red.is_turn) {
            red.is_turn = false;
            blue.is_turn = true;
            red.turn_number++;
            _add_inc(&red);
        }
    }
    if (presses[1]) {
        state = PAUSED;
    }
    if (presses[2]) {
        state = STOPPED;
    }
    if (presses[3]) {
        if (blue.is_turn) {
            red.is_turn = true;
            blue.is_turn = false;
            blue.turn_number++;
            _add_inc(&blue);
        }
    }
}

void Board::_stopped_button_listener(int* presses) {
    if (presses[0]) {
        state = RED_WIN;
    } else if (presses[3]) {
        state = BLUE_WIN;
    }
    if (presses[1]) {
        state = IN_GAME;
    }
    if (presses[2]) {
        state = PAUSED;
    }
}

void Board::_game_event_listener() {
    Player *p;
    if (red.is_turn) {
        p = &red;
    }
    if (blue.is_turn) {
        p = &blue;
    }

    if (p->delay != 0 && p->delay - BOARD_REFRESH_DELAY < p->delay) {
        p->delay -= BOARD_REFRESH_DELAY;
        return;
    }

    if (p->time_left - BOARD_REFRESH_DELAY > p->time_left) {
        state = red.is_turn ? BLUE_WIN : RED_WIN;
        return;
    }
    
    // redraw screen logic (redraw every minute)
    if ((p->time_left - BOARD_REFRESH_DELAY) % 60000 > p->time_left % 60000) {
        redraw_screen = true;
    }

    p->time_left -= BOARD_REFRESH_DELAY;
}

void Board::_add_inc(Player *p) {
    if (p->time_left + time.increment < p->time_left) {
        p->time_left = UINT_MAX;
        return;
    }

    p->time_left += time.increment;
}


