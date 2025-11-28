#include <stdint.h>

#define REG_WIDTH 8

#define TYPE_FOR_WIDTH_8   uint8_t
#define TYPE_FOR_WIDTH_16  uint16_t
#define TYPE_FOR_WIDTH_32  uint32_t
#define TYPE_FOR_WIDTH_64  uint64_t

#define _TYPE_FOR_WIDTH(x) TYPE_FOR_WIDTH_##x
#define REGTYPE(x)         _TYPE_FOR_WIDTH(x)
typedef REGTYPE(REG_WIDTH) reg_t;

typedef struct USART {
    uint32_t BAUD_RATE;
    volatile reg_t *comm_reg;
    volatile reg_t *data_reg;
    volatile int rx_flag;
    volatile int tx_flag;
    void (*init)(uint32_t BAUD_RATE, volatile reg_t *UBRR);
    void (*transmit)( uint8_t data);
    reg_t (*receive)(void);
}USART;

typedef struct USART USART_t;

static void USART_init_i(USART *self, uint32_t BAUD_RATE, volatile reg_t *UBRR) {
    self->BAUD_RATE = BAUD_RATE;
    switch (BAUD_RATE) {
        case (19200):
            *UBRR = 51;
            break;
        default:
            break;
    }
}

static reg_t USART_read_i(USART *self) {
    while (!(*self->comm_reg & (1<<(self->rx_flag))));
    return *self->data_reg;
}

static void USART_write_i(USART *self, uint8_t data) {
    while (!(*self->comm_reg & (1<<(self->tx_flag))));
    *self->data_reg = data;
}

#define DEFINE_USART_METHODS(instance)                                          \
    static void instance##_init_wrapper(/*USART *self, */uint32_t baud, volatile reg_t *ubrr) {       \
        USART_init_i(&instance, baud, ubrr);                                          \
    }                                                                           \
    static reg_t instance##_read_wrapper(/*USART *self*/) {                     \
        return USART_read_i(&instance);                                         \
    }                                                                           \
    static void instance##_write_wrapper(/*USART *self, */reg_t d) {            \
        USART_write_i(&instance, d);                                            \
    }                                                                           \
    static void instance##_bind_methods(void) {                                 \
        (instance).init     = instance##_init_wrapper;                          \
        (instance).receive  = instance##_read_wrapper;                          \
        (instance).transmit = instance##_write_wrapper;                         \
    }                                                                           \
    static int instance##_dummy = (instance##_bind_methods(), 0)

