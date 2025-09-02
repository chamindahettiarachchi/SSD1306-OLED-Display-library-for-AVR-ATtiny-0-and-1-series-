//ssd1306_hal.c
#ifndef F_CPU
#define F_CPU 3333333UL   // or 20000000UL if you run at 20 MHz
#endif

#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "twi0_bare.h"    // must exist in your project (add .c and .h)
#include "ssd1306.h"      // defines SSD1306_ADDR (or pulls from ssd1306_config.h)

// --- HAL API implementations ---

void ssd1306_hal_init(void)
{
    TWI0_bare_init_100k();  // I2C master init (PB0=SDA, PB1=SCL by default)
}

void ssd1306_hal_delay_ms(uint16_t ms)
{
    while (ms--) _delay_ms(1);
}

bool ssd1306_hal_write_cmds(const uint8_t *cmds, uint8_t n)
{
    if (!TWI0_bare_start_write(SSD1306_ADDR)) return false;
    if (!TWI0_bare_write(0x00)) { TWI0_bare_stop(); return false; } // control=commands
    for (uint8_t i = 0; i < n; i++) {
        if (!TWI0_bare_write(cmds[i])) { TWI0_bare_stop(); return false; }
    }
    TWI0_bare_stop();
    return true;
}

bool ssd1306_hal_write_data(const uint8_t *data, uint16_t n)
{
    if (!TWI0_bare_start_write(SSD1306_ADDR)) return false;
    if (!TWI0_bare_write(0x40)) { TWI0_bare_stop(); return false; } // control=data
    for (uint16_t i = 0; i < n; i++) {
        if (!TWI0_bare_write(data[i])) { TWI0_bare_stop(); return false; }
    }
    TWI0_bare_stop();
    return true;
}
