//ssd_hal.h
#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Implement these for your MCU:
bool ssd1306_hal_init(void);
bool ssd1306_hal_write_cmds(const uint8_t *cmds, size_t n);
bool ssd1306_hal_write_data(const uint8_t *bytes, size_t n);
void ssd1306_hal_delay_ms(uint16_t ms);
