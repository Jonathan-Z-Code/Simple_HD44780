#include <Arduino.h>
#include "Simple_HD44780.h"

/* choose either default configuration
 HD44780 lcd;
 or go for a more detailed configuration
*/
HD44780 lcd;
/* Reminder: all elements in struct that
  are uninitialized are set to ZERO!
*/

/* The only supported LCD display layout in this library
  are 1602 displays (16 chars per line, 2 lines)
*/
/*
HD44780::Config_1602 data_config {
  .cursor_on = HD44780::ENABLE_CURSOR,
  .blinking_cursor = HD44780::ENABLE_BLINKING,
  .char_font = HD44780::FIVE_BY_EIGHT_FONT,
};
*/

// confirm new settings with the constructor
// HD44780 lcd(&data_config);

void setup(void) {
  Serial.begin(9600);
  lcd.begin();
}

void loop(void) {
}