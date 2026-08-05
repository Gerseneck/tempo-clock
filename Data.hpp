#ifndef DATA_HPP
#define DATA_HPP

#include <Arduino.h>
#include <EEPROM.h>

#include "Board.hpp"

const unsigned int STATE_ADDR = 0;
const unsigned int C_TIME_ADDR = STATE_ADDR + sizeof(BoardState);
const unsigned int PRESET_ADDR = C_TIME_ADDR + sizeof(ClockTime);
const unsigned int RED_ADDR = PRESET_ADDR + sizeof(Preset);
const unsigned int BLUE_ADDR = PRESET_ADDR + sizeof(Player);

void check_and_initialize_data();

#endif
