#include "Simple_HD44780.h"

// default global settings, can be overridden via two methods
// METHOD 1: Give a Config_1602 struct to the constructor
// METHOD 2: call disable_x or enable_x functions in order to change the global_config struct
HD44780::Config_1602 global_config = {
    .db7 = 4,
    .db6 = 3,
    .db5 = 2,
    .db4 = 1,
    .rw  = 5,
    .rs  = 6,
    .en  = 7,
    .display_on       = 0,
    .cursor_on        = 0,
    .blinking_cursor  = 0,
    .data_length      = 0,
    .display_line     = 0,
    .char_font        = 0,
};

HD44780::HD44780() {}
HD44780::HD44780(Config_1602 config_data) {
    // update global_config data with user-defined preferences
    global_config.db7 = config_data.db7;
    global_config.db6 = config_data.db6;
    global_config.db5 = config_data.db5;
    global_config.db4 = config_data.db4;
    global_config.db3 = config_data.db3;
    global_config.db2 = config_data.db2;
    global_config.db1 = config_data.db1;
    global_config.db0 = config_data.db0;
    global_config.rw  = config_data.rw;
    global_config.rs  = config_data.rs;
    global_config.en  = config_data.en;
    global_config.display_on       = config_data.display_on;
    global_config.cursor_on        = config_data.cursor_on;
    global_config.blinking_cursor  = config_data.blinking_cursor;
    global_config.data_length      = config_data.data_length;
    global_config.display_line     = config_data.display_line;
    global_config.char_font        = config_data.char_font;
}

void HD44780::write_byte(unsigned char cmd) {}

void HD44780::disable_cursor() {}
void HD44780::enable_cursor() {}

void HD44780::disable_blinking() {}
void HD44780::enable_blinking() {}

void HD44780::disable_display() {}
void HD44780::enable_display() {}

void HD44780::shift_display() {}

void HD44780::write_char() {}
void HD44780::write_string() {}