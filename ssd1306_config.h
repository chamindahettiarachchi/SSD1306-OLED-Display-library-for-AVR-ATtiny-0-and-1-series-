#pragma once

// Panel geometry
#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  64

// I2C address (0x3C or 0x3D)
#ifndef SSD1306_ADDR
#define SSD1306_ADDR    0x3C
#endif

// Power mode: 1 = internal charge pump, 0 = external VCC
#define SSD1306_USE_CHARGEPUMP  1

// Drawing mode:
// 1 = full RAM framebuffer (best visuals, more RAM)
// 0 = streamed drawing (minimal RAM, good for small MCUs)
#define SSD1306_BUFFERED 0
