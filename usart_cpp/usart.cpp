#include "../include/usart.h"

USART::USART(
    uint8_t tx_x, //tx pin
        uint8_t rx_x,   //rx pin
        volatile uint8_t *ucsrnA, 
        volatile uint8_t *ucsrnB,
        volatile uint16_t *ubrrn)
    :   tx_pin(tx_x),
        rx_pin(rx_x),
        UCSRnA(ucsrnA),
        UCSRnB(ucsrnB),
        UBRRn(ubrrn){}
    
    
    
        /*{
        tx_pin = tx_x;
        rx_pin = rx_x;
        *UCSRnA = *ucsrnA;
        *UCSRnB = *ucsrnB;
        *UBRRn = *ubrrn;
    }*/

//USART USART0(USART0_tx, USART0_rx, UCSR0A, UCSR0B, UBRR0);

void USART::init(unsigned long baud_rate, 
                rx_int_mode rxInt, 
                tx_int_mode txInt, 
                data_int_mode datInt,
                rx_mode rxEn,
                tx_mode txEn,
                spd_mode speed) {
    
    if (rxInt == rx_int_mode::en)
        *UCSRnB |= (1<<RXCIE0);
    else 
        *UCSRnB &= ~(1<<RXCIE0);
    
    if (txInt == tx_int_mode::en)
        *UCSRnB |= (1<<TXCIE0);
    else 
        *UCSRnB &= ~(1<<TXCIE0);

    if (datInt == data_int_mode::en)
        *UCSRnB |= (1<<UDRIE0);
    else
        *UCSRnB &= ~(1<<UDRIE0);

    if (rxEn == rx_mode::en)
        *UCSRnB |= (1<<RXEN0);
    else 
        *UCSRnB &= ~(1<<RXEN0);

    if (txEn == tx_mode::en)
        *UCSRnB |= (1<<TXEN0);
    else 
        *UCSRnB &= ~(1<<TXEN0);

    if (speed == spd_mode::doub)
        *UCSRnA |= (1<<U2X0);
    else if (speed == spd_mode::norm)
        *UCSRnA &= ~(1<<U2X0);
}

bool USART::ready(void) {
    return (*UCSRnA & (1 << UDRE0));
}

volatile void USART::write(const uint8_t data) {
    while (!(*UCSRnA & (1 << UDRE0)));
    *UDRn = data; 
}

uint8_t USART::receive(void) {
    while (!(*UCSRnA & (1<<RXC0)));
    return *UDRn;
}

void USART::putc(uint8_t c) {
    while(!(*UCSRnA & (1 << UDRE0)));
    *UDRn = c;
}

void USART::put_string(char str[], uint8_t STR_LEN) {
    for (int i=0; i<STR_LEN; i++) {
        while (!ready());
        write(str[i]);
    }
    clr_array_char(str, STR_LEN);
}

void USART::put_stringP(PGM_P str) {
    while(1) {
        uint8_t b = pgm_read_byte_near(str++);
        if(!b)
        break;
        putc(b);
    }
}