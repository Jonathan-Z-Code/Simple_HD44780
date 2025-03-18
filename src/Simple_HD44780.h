#ifndef SIMPLE_HD44780_H_
#define SIMPLE_HD44780_H_

// setting to print out debug information
#define HD44780_PRINT_DEBUG_INFO (1) 

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
        // unsigned char db3;
        // unsigned char db2;
        // unsigned char db1;
        // unsigned char db0;
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
    } Config_1602;

    // default settings enabled if user does not define settings
    HD44780(void);
    // if user has desired settings, implement this constructor
    HD44780(Config_1602 config_data);

    // IF display_shift = true ;
    // true means increment , false means decrement 
    // IF display_shift = false ;
    // nothing happens
    bool incr;
    // true means display shifts, false means no shifting! 
    bool display_shift;

    void begin(void);

    void disable_cursor(void);
    void enable_cursor(void);

    void enable_blinking(void);
    void disable_blinking(void); 

    void disable_display(void);
    void enable_display(void);

    void shift_display(void);

    void write_char(void);
    void write_string(void);

    // configuration macros
    static const unsigned char DISABLE_CURSOR = 0;
    static const unsigned char ENABLE_CURSOR = 1;
    static const unsigned char DISABLE_BLINKING = 0;
    static const unsigned char ENABLE_BLINKING = 1;
    static const unsigned char DISABLE_DISPLAY = 0;
    static const unsigned char ENABLE_DISPLAY = 1;
    static const unsigned char FOUR_BIT_DATA_LENGTH = 0;
    static const unsigned char EIGHT_BIT_DATA_LENGTH = 1;
    static const unsigned char FIVE_BY_EIGHT_FONT = 0;
    static const unsigned char FIVE_BY_TEN_FONT = 1;
    static const unsigned char ONE_LINE_LCD_DISPLAY = 0;
    static const unsigned char TWO_LINE_LCD_DISPLAY = 1;

private:

    /* create a private version of the config struct to keep 
       track of user-defined changes
    */
    Config_1602 global_config;

    void set_data(void);
    void reset_gpio(void);
    void write_byte(unsigned char command);
    void write_nibble(unsigned char nibble);
    
    // custom commands for initialization 
    unsigned char cmd_function_set = 0x20;
    unsigned char cmd_display_control = 0x08;

    // ready-to-go commands for the HD44780
    const unsigned char cmd_clear_display = 0x01;
    const unsigned char cmd_return_home   = 0x02; 

    // bit positions for all configuration settings
    const unsigned char INCR_DECR_MSK               = 0x02;
    const unsigned char DISPLAY_SHIFT_MSK           = 0x01;
    const unsigned char DISPLAY_ON_OFF_MSK          = 0x04;
    const unsigned char CURSOR_ON_OFF_MSK           = 0x02;
    const unsigned char BLINKING_CURSOR_MSK         = 0x01;    
    const unsigned char CURSOR_OR_DISPLAY_SHIFT_MSK = 0x08;
    const unsigned char SHIFT_RIGHT_LEFT_MSK        = 0x04;
    const unsigned char DATA_LENGTH_MSK             = 0x10;
    const unsigned char DISPLAY_LINE_MSK            = 0x08;
    const unsigned char CHARACTER_FONT_MSK          = 0x04;

};


#endif