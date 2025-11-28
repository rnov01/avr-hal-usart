#pragma once

#include <stdint.h>
#include <avr/io.h>

struct pin {
    volatile uint8_t *DDR;
    volatile uint8_t *PORT;
    volatile uint8_t *PIN;
    uint8_t bit_number;
};

constexpr pin PIN_E1 = {&DDRE, &PORTE, &PINE, PE1};
constexpr pin PIN_E0 = {&DDRE, &PORTE, &PINE, PE0};