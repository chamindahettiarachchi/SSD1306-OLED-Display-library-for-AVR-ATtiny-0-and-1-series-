//ssd1306.h
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "ssd1306_config.h"


#ifndef SSD1306_BUFFERED
#define SSD1306_BUFFERED 1   // default if not set in config
#endif

bool ssd1306_begin(void);            // init panel + clear (does NOT draw until display(), if buffered)
void ssd1306_clear(void);            // clear framebuffer or clear screen (streamed)
void ssd1306_display(void);          // flush framebuffer to panel (no-op in streamed mode)
void ssd1306_set_contrast(uint8_t v);
void ssd1306_invert(bool on);

// Pixel & primitives (buffered updates the RAM; streamed writes immediately)
void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool on);
void ssd1306_draw_hline(uint8_t x, uint8_t y, uint8_t w, bool on);
void ssd1306_draw_vline(uint8_t x, uint8_t y, uint8_t h, bool on);
void ssd1306_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool on);
void ssd1306_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool on);

// Text (5x7 ASCII)
void ssd1306_set_cursor(uint8_t col, uint8_t page);         // page = row/8
void ssd1306_write_char(char c);
void ssd1306_write_string(const char *s);
void ssd1306_goto(uint8_t col, uint8_t page);
void ssd1306_write_u16(uint16_t v);
void ssd1306_write_s16(int16_t v);
void ssd1306_write_hex8(uint8_t v);
void ssd1306_write_fixed2(int16_t v_x100);
void ssd1306_write_int(int value);
void ssd1306_write_column(uint8_t page, uint8_t col, uint8_t pattern);
