#include "usart.h"

typedef enum {
    DEBUG, PRINT, err
}COMMANDS;

struct str_to_cmd {
    const char* name;
    COMMANDS cmd; 
};

COMMANDS parse_command(char *buffer);
COMMANDS receive_command(USART *USARTn);