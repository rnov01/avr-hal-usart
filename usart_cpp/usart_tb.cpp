#include "usart.h"
#include <stdint.h>
#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>

#define USART0_tx PE1
#define USART0_rx PE0

int main() {

    USART USART0(USART0_tx, USART0_rx, UCSR0A, UCSR0B, UBRR0);
}