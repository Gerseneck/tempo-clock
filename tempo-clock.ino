#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

#include "Board.hpp"
#include "Logger.hpp"
#include "Display.hpp"

Logger logger;
Board board(logger);
Display display(board);

void setup() {
    logger.init();
    board.init();
    logger.log("Board Ready!");
    display.init();
    logger.log("Display Ready!");

    // loading screen timer
    delay(1000);
}

void loop() {
    display.render();
    board.event_listener();

    delay(BOARD_REFRESH_DELAY);
}
