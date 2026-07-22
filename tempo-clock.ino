#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

#include "Board.hpp"
#include "Display.hpp"

const int LCD_PIN_RS = 12;
const int LCD_PIN_ENABLE = 11;
const int LCD_PIN_D4 = 5;
const int LCD_PIN_D5 = 4;
const int LCD_PIN_D6 = 3;
const int LCD_PIN_D7 = 2;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

Board board;
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
Display display(&board, &lcd);

void setup() {
    Serial.begin(9600);
    lcd.begin(LCD_COLS, LCD_ROWS);

    pinMode(BUTTON_A_PIN, INPUT);
    pinMode(BUTTON_B_PIN, INPUT);
    pinMode(BUTTON_C_PIN, INPUT);
    pinMode(BUTTON_D_PIN, INPUT);
}

void loop() {
    // Serial.println(board.get_preset_string());
    // tone(8, 220);
    board.event_listener();
    display.render();

    delay(100);
}
