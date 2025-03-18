#ifndef SIMPLE_HD44780_H_
#define SIMPLE_HD44780_H_

class HD44780 {
    
public:

    // struct to hold config data for a 1602 LCD display
    // 16 characters per line
    // 2 lines
    typedef struct Config_1602 {
        // map all pins to a GPIO 
        unsigned char db7;
        unsigned char db6;
        unsigned char db5;
        unsigned char db4;
        unsigned char db3;
        unsigned char db2;
        unsigned char db1;
        unsigned char db0;
        unsigned char rw;
        unsigned char rs;
        unsigned char en;
        // true means display is on, false means display is off
        unsigned char display_on;
        // true means the cursor is on screen, false means cursor is hidden
        unsigned char cursor_on;
        // true means the cursor will blink, false means a static cursor sprite
        unsigned char blinking_cursor;
        // 1 means 8 bit data mode, 0 means 4 bit data mode
        unsigned char data_length;
        // 1 means 2 rows of LCD screen will be use, 0 means only 1 row operation
        unsigned char display_line;
        // 1 means 5x10 char font, 0 means 5x8 char font 
        unsigned char char_font; 
    } config;

    // default settings enabled if user does not define settings
    HD44780::HD44780();
    // if user has desired settings, implement this constructor
    HD44780::HD44780(Config_1602 config_data);
        // IF display_shift = true ;
        // true means increment , false means decrement 
        // IF display_shift = false ;
        // nothing happens
        bool incr;
        // true means display shifts, false means no shifting! 
        bool display_shift;

    // configuration settings
    static const unsigned char DISABLE_CURSOR = 1;
    static const unsigned char ENABLE_CURSOR = 0;
    static const unsigned char ENABLE_BLINKING = 1;
    static const unsigned char DISABLE_BLINKING = 0;
    static const unsigned char ENABLE_DISPLAY = 1;
    static const unsigned char DISABLE_DISPLAY = 0;
    static const unsigned char EIGHT_BIT_DATA_LENGTH = 1;
    static const unsigned char FOUR_BIT_DATA_LENGTH = 0;
    static const unsigned char FIVE_BY_TEN_FONT = 0;
    static const unsigned char FIVE_BY_EIGHT_FONT = 1;
    static const unsigned char TWO_ROW_LCD_DISPLAY = 1;
    static const unsigned char ONE_ROW_LCD_DISPLAY = 0;
    void disable_cursor();
    void enable_cursor();

    void enable_blinking();
    void disable_blinking(); 

    void disable_display();
    void enable_display();

    void shift_display();

    void write_char();
    void write_string();

    // ready-to-go commands for the HD44780
    const unsigned char CMD_CLEAR_DISPLAY       = 0x01;
    const unsigned char CMD_RETURN_CURSOR_HOME  = 0x02; 

    // bit positions for all configuration settings
    const unsigned char POS_INCR_DECR               = 0x02;
    const unsigned char POS_DISPLAY_SHIFT           = 0x01;
    const unsigned char POS_DISPLAY_ON_OFF          = 0x04;
    const unsigned char POS_CURSOR_ON_OFF           = 0x02;
    const unsigned char POS_BLINKING_CURSOR         = 0x01;
    const unsigned char POS_CURSOR_OR_DISPLAY_SHIFT = 0x08;
    const unsigned char POS_SHIFT_RIGHT_LEFT        = 0x04;
    const unsigned char POS_DATA_LENGTH             = 0x10;
    const unsigned char POS_DISPLAY_LINE            = 0x08;
    const unsigned char POS_CHARACTER_FONT          = 0x04;

private:

    // create a private version of the config struct to keep
    // track of user-defined changes
    Config_1602 global_config;

    void write_byte(unsigned char command);

};


#endif