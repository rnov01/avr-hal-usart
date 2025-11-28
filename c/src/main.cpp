//#include <Arduino.h>
#include "../../usart.h"
#include <util/delay.h>

//#define UCSR0A 0xC0
//#define UCSR0B 0xC1
//#define UDR0 0xC6
#define UBRR1L 0xCC
#define UBRR1H 0xCD
#define UDR1 0xCE
#define DATA_REG
#define RX_FLAG 7
#define TX_FLAG 6
#define UDREn   5
#define RXEN0  4  
#define TXEN0  3  


#define UBRR0H_ADDR 0xC5
#define UBRR0L_ADDR 0xC4
#define USART0_UCSR0A_ADDR 0xC0
#define USART0_UCSR0B_ADDR 0xC1
#define USART0_UCSR0C_ADDR 0xC2
#define USART0_UBRR0H_ADDR 0xC5
#define USART0_UBRR0L_ADDR 0xC4
#define USART0_UDR0_ADDR   0xC6

#define REG8(addr) ((volatile uint8_t*)(uintptr_t)(addr))
static volatile uint8_t * const UCSR0A = REG8(USART0_UCSR0A_ADDR);
static volatile uint8_t * const UCSR0B = REG8(USART0_UCSR0B_ADDR);
static volatile uint8_t * const UCSR0C = REG8(USART0_UCSR0C_ADDR);
static volatile uint8_t * const UBRR0H = REG8(USART0_UBRR0H_ADDR);
static volatile uint8_t * const UBRR0L = REG8(USART0_UBRR0L_ADDR);
static volatile uint8_t * const UDR0   = REG8(USART0_UDR0_ADDR);



volatile uint8_t * const UBRR0H_ = (volatile uint8_t*)UBRR0H_ADDR;
volatile uint8_t * const UBRR0L_ = (volatile uint8_t*)UBRR0L_ADDR;

char x = 'a';
USART_t USART0;
DEFINE_USART_METHODS(USART0);

int main() {
  *UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  USART0.comm_reg = UCSR0A;
  USART0.data_reg = UDR0;
  USART0.rx_flag = RX_FLAG;
  USART0.tx_flag = UDREn;
  USART0.init(19200, UBRR0L_);
   
  while(1) {
     USART0.transmit(x);
      x++;
    _delay_ms(500);
  }

}
