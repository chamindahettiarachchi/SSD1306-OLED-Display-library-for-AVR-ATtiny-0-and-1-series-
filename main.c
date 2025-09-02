#define F_CPU 3333333UL
#include <util/delay.h>
#include <avr/io.h>

#include "twi0_bare.h"
#include "ssd1306.h"
#include "ssd1306_hal.h"
int kroll = 725;
int main(void)
{
    if (!ssd1306_begin()) while (1) { }   // init I2C + OLED
// Unsigned integer
ssd1306_set_cursor(0,0);
ssd1306_write_string("kroll: ");
ssd1306_write_u16(kroll);

// Signed integer
ssd1306_set_cursor(0,2);
ssd1306_write_string("ALT: ");
ssd1306_write_s16(-57);

// Hex byte
ssd1306_set_cursor(0,3);
ssd1306_write_string("ID: 0x");
ssd1306_write_hex8(0xA5);

// Fixed-point (x100 -> 2 decimals)
ssd1306_set_cursor(0,6);
ssd1306_write_string("TEMP: ");
ssd1306_write_fixed2(2325);  // prints 23.25


#if SSD1306_BUFFERED
    ssd1306_display();    // flush when buffered
#endif

    // --- Moving bar on page 4 (streamed-friendly) ---
    uint8_t col  = 0;
    uint8_t prev = SSD1306_WIDTH - 1;

#if !SSD1306_BUFFERED
    // Clear page 4 once so the bar starts clean
    ssd1306_goto(0, 4);
    uint8_t zero = 0x00;
    for (uint8_t i = 0; i < SSD1306_WIDTH; i++) ssd1306_hal_write_data(&zero, 1);

    uint8_t off = 0x00;   // blank column
    uint8_t on  = 0xFF;   // solid vertical column (8 pixels high)
#endif

    for (;;) {
#if SSD1306_BUFFERED
        // erase previous bar
        for (uint8_t r = 0; r < 8; r++) {
            ssd1306_draw_pixel(prev, 4*8 + r, false);
        }
        // draw new bar
        for (uint8_t r = 0; r < 8; r++) {
            ssd1306_draw_pixel(col, 4*8 + r, true);
        }
        ssd1306_display();
#else
        // move to previous column in page 4 and erase it
        ssd1306_goto(prev, 4);
        ssd1306_hal_write_data(&off, 1);

        // move to new column in page 4 and draw it
        ssd1306_goto(col, 4);
        ssd1306_hal_write_data(&on, 1);
#endif
        prev = col;
        col  = (col + 1) % SSD1306_WIDTH;
        _delay_ms(15);
    }
}
