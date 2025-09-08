// main.c  (SSD1306_BUFFERED must be 0)
#define F_CPU 3333333UL
#include <util/delay.h>
#include <avr/io.h>
#include "ssd1306.h"
#include "ssd1306_hal.h"

// (from your Solution B)

int main(void)
{
    PORTB_DIRSET = PIN2_bm;
    if (!ssd1306_begin()) while (1) { }

    // --- Static UI once (no display() needed in streamed mode)
    ssd1306_clear();
    ssd1306_set_cursor(0,0); ssd1306_write_string("Sri Lanka 2025");
    ssd1306_set_cursor(0,2); ssd1306_write_string("CHAMINDA 9477");
    ssd1306_set_cursor(0,6); ssd1306_write_string("VAL:");

    // --- Moving bar on page 4 (no flicker)
    uint8_t col = 0, prev = SSD1306_WIDTH - 1;

    // changing value
    int val = 0;
    int k = 0;

    for (;;)
    {    /*
        // 1) update the moving bar (only 2 columns)
        ssd1306_write_column(4, prev, 0x00);      // erase previous column
        ssd1306_write_column(4, col,  0xFF);      // draw new column
        prev = col;
        col  = (uint8_t)((col + 1) % SSD1306_WIDTH);*/

        // 2) update the changing value (erase + print small area only)
        ssd1306_set_cursor(30, 6);                 // fixed spot for the number
        ssd1306_write_string("     ");             // clear old value (5 spaces)
        ssd1306_set_cursor(30, 6);
        ssd1306_write_int(val); // or use snprintf ? ssd1306_write_string(buf)
        
        
          ssd1306_set_cursor(50, 4);                 // fixed spot for the number
        ssd1306_write_string("     ");             // clear old value (5 spaces)
        ssd1306_set_cursor(50, 4);
        ssd1306_write_string("count");
        
        
         ssd1306_set_cursor(50, 5);                 // fixed spot for the number
        ssd1306_write_string("     ");             // clear old value (5 spaces)
        ssd1306_set_cursor(50, 5);
        ssd1306_write_int(k);
        
        
        
        
        k += 1;
        if(k > 100) {
            k = 0;
        PORTB_OUTTGL = PIN2_bm;
        }
        

        val++;
        if (val > 99999) val = 0;                  // keep it short

       // _delay_ms(1);
    }
}

