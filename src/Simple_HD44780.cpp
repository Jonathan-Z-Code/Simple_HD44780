#include "Simple_HD44780.h"
#include <Arduino.h>

// Here are the default global settings, can be overridden via two methods
// METHOD 1: Give a Config_1602 struct to the constructor
// METHOD 2: call disable_x or enable_x functions in order to change the global_config struct
HD44780::HD44780() {
    global_config.db7 = 7;
    global_config.db6 = 6;
    global_config.db5 = 5;
    global_config.db4 = 4;
    global_config.rw  = 5;
    global_config.rs  = 6;
    global_config.en  = 3;
    global_config.display_on       = HD44780::ENABLE_DISPLAY;
    global_config.cursor_on        = HD44780::ENABLE_CURSOR;
    global_config.blinking_cursor  = HD44780::ENABLE_BLINKING;
    global_config.data_length      = HD44780::FOUR_BIT_DATA_LENGTH;
    global_config.display_line     = HD44780::TWO_LINE_LCD_DISPLAY;
    global_config.char_font        = HD44780::FIVE_BY_EIGHT_FONT;
}

HD44780::HD44780(Config_1602 config_data) {
    // update global_config data with user-defined preferences
    global_config.db7 = config_data.db7;
    global_config.db6 = config_data.db6;
    global_config.db5 = config_data.db5;
    global_config.db4 = config_data.db4;
    // global_config.db3 = config_data.db3;
    // global_config.db2 = config_data.db2;
    // global_config.db1 = config_data.db1;
    // global_config.db0 = config_data.db0;
    global_config.rw  = config_data.rw;
    global_config.rs  = config_data.rs;
    global_config.en  = config_data.en;
    global_config.display_on       = config_data.display_on;
    global_config.cursor_on        = config_data.cursor_on;
    global_config.blinking_cursor  = config_data.blinking_cursor;
    //global_config.data_length      = config_data.data_length;
    global_config.display_line     = config_data.display_line;
    global_config.char_font        = config_data.char_font;
}

// starts the initialization process of display
void HD44780::begin(void) {
    
    // init all GPIO pins as necessary
    pinMode(global_config.db7, OUTPUT);
    pinMode(global_config.db6, OUTPUT);
    pinMode(global_config.db5, OUTPUT);
    pinMode(global_config.db4, OUTPUT);
    pinMode(global_config.rs, OUTPUT);
    pinMode(global_config.rw, OUTPUT);
    pinMode(global_config.en, OUTPUT);

    // wait for GPIO data bus to settle
    delayMicroseconds(250);

    // set configuration bits as necessary
    if(global_config.data_length)       cmd_function_set |= DATA_LENGTH_MSK;
    if(global_config.display_line)      cmd_function_set |= DISPLAY_LINE_MSK;
    if(global_config.char_font)         cmd_function_set |= CHARACTER_FONT_MSK;

    if(global_config.display_on)        cmd_display_control |= DISPLAY_ON_OFF_MSK;
    if(global_config.cursor_on)         cmd_display_control |= CURSOR_ON_OFF_MSK;
    if(global_config.blinking_cursor)   cmd_display_control |= BLINKING_CURSOR_MSK;
    
    #if HD44780_PRINT_DEBUG_INFO
        Serial.println(cmd_function_set, HEX);
        Serial.println(cmd_display_control, HEX);
    #endif

    // write initialization bytes to the HD44780
    //write_nibble(0);
    write_byte(cmd_function_set);
    write_byte(cmd_display_control);
    write_byte(cmd_clear_display);
    write_byte(cmd_return_home);

}

// toggles the enable pin in order to register data to LCD
void HD44780::set_data(void) {
    digitalWrite(global_config.en, HIGH);
    delayMicroseconds(1000); // delay time can be optimized
    digitalWrite(global_config.en, LOW);
    delayMicroseconds(1000);
}

// reset the data bits to start a write_byte command
void HD44780::reset_gpio(void) {
    digitalWrite(global_config.db7, LOW);
    digitalWrite(global_config.db6, LOW);
    digitalWrite(global_config.db5, LOW);
    digitalWrite(global_config.db4, LOW);
}

// writes one byte to the HD44780 controller
void HD44780::write_byte(unsigned char cmd) {
    // break cmd down into two seperate 4-bit values
    unsigned char lower_nibble = (cmd & 0x0F);
    unsigned char upper_nibble = (cmd & 0xF0) >> 4;
    // reset data line and register the upper_nibble to the LCD
    reset_gpio();
    if(upper_nibble & 0x08) digitalWrite(global_config.db7, HIGH);
    if(upper_nibble & 0x04) digitalWrite(global_config.db6, HIGH);
    if(upper_nibble & 0x02) digitalWrite(global_config.db5, HIGH);
    if(upper_nibble & 0x01) digitalWrite(global_config.db4, HIGH);
    set_data();
    // reset data line again and register the lower_nibble to the LCD
    reset_gpio();
    if(lower_nibble & 0x08) digitalWrite(global_config.db7, HIGH);
    if(lower_nibble & 0x04) digitalWrite(global_config.db6, HIGH);
    if(lower_nibble & 0x02) digitalWrite(global_config.db5, HIGH);
    if(lower_nibble & 0x01) digitalWrite(global_config.db4, HIGH);
    set_data();
}

void HD44780::write_nibble(unsigned char nibble) {
    reset_gpio();
    digitalWrite(global_config.db7, LOW);
    digitalWrite(global_config.db6, LOW);
    digitalWrite(global_config.db5, HIGH);
    digitalWrite(global_config.db4, LOW);
    set_data();
}

void HD44780::disable_cursor(void) {}
void HD44780::enable_cursor(void) {}

void HD44780::disable_blinking(void) {}
void HD44780::enable_blinking(void) {}

void HD44780::disable_display(void) {}
void HD44780::enable_display(void) {}

void HD44780::shift_display(void) {}

void HD44780::write_char(void) {}
void HD44780::write_string(void) {}