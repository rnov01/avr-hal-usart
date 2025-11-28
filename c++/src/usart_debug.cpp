#include <string.h>
#include "../include/usart_debug.h"

#define BUFFER_SIZE 32 //move this to a definitions header 


static const str_to_cmd COMMAND_LUT[] = {
    {"debug", COMMANDS::DEBUG},
    {"print", COMMANDS::PRINT},
    {nullptr, COMMANDS::err}
};

COMMANDS parse_command(char *buffer) {
    for (int i=0; COMMAND_LUT[i].name != nullptr; i++) {
        if (strcmp(buffer, COMMAND_LUT[i].name) == 0) {
            return COMMAND_LUT[i].cmd;
        }
    }
    return COMMANDS::err;
}

COMMANDS receive_command(USART *USARTn) {
    char rx_buffer[BUFFER_SIZE];
    volatile uint8_t rx_index = 0;
    char rx_char;
    //char rx_char = USARTn->receive();
    do {
        rx_char = USARTn->receive();
       
    } while (rx_char == '\r' || rx_char == '\n');

    while (1) {
        if (rx_char == '\r' || rx_char == '\n') {
            rx_buffer[rx_index] = '\0';
            break;
        } else {
            rx_buffer[rx_index++] = rx_char;
        }
         rx_char = USARTn->receive();
    }
    return parse_command(rx_buffer);
}