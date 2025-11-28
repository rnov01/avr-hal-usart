#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pin.h"

enum class rx_int_mode : uint8_t { dis = 0, en = 1 };
enum class tx_int_mode : uint8_t { dis = 0, en = 1 };
enum class data_int_mode : uint8_t { dis = 0, en = 1 };
enum class rx_mode : uint8_t { dis = 0, en = 1 };
enum class tx_mode : uint8_t { dis = 0, en = 1 };
enum class spd_mode : uint8_t { norm, doub };

class USART {

    public:

    USART(const pin& tx_x,
        const pin& rx_x,
        uint16_t ucsrnA_addr, 
        uint16_t ucsrnB_addr,
        uint16_t ubrrn_addr,
        uint16_t udrn_addr);

        void init(unsigned long baud_rate, 
                rx_int_mode rxInt, 
                tx_int_mode txInt, 
                data_int_mode datInt,
                rx_mode rxEn,
                tx_mode txEn,
                spd_mode speed);
        bool ready(void);
        volatile void write(const uint8_t data);
        uint8_t receive(void);

        void putc(uint8_t c);
        void put_string(char str[], uint8_t STR_LEN);
        void put_stringP(PGM_P str);
        
    private:
        const pin& tx_pin;
        const pin& rx_pin;
        volatile uint8_t* const UCSRnA;
        volatile uint8_t* const UCSRnB;
        //volatile uint8_t* const UCSRnC;
        //volatile uint8_t* const UBRRnH;
        volatile uint16_t* const UBRRn;
        volatile uint8_t* const UDRn;
        volatile uint8_t BR_PS = 16;
};

extern USART USART0;
extern USART USART3;