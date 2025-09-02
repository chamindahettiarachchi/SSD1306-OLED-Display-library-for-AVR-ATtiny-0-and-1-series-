
//twi0_bare.h
#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef F_CPU
#define F_CPU 3333333UL
#endif

void TWI0_bare_init_100k(void);
bool TWI0_bare_start_write(uint8_t addr7);
bool TWI0_bare_write(uint8_t byte);
void TWI0_bare_stop(void);
