#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

#include "Board.hpp"
#include "Display.hpp"

Board board;
Display display(board);

void setup() {
    Serial.begin(9600);

    board.init();
    display.init();

    // loading screen timer
    delay(1000);
}

void loop() {
    display.render();
    board.event_listener();

    delay(BOARD_REFRESH_DELAY);
}
