#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pin.h"

/*! \name USART Initializers 
 *  \details Configuration options used with \ref USART::init()
 * @{
 */
/*! \enum rx_int_mode
 *  \brief Enable or disable the Rx interrupt 
 *  \details  */
enum class rx_int_mode : uint8_t { dis = 0, en = 1 };
/*! \enum tx_int_mode
 *  \brief Enable or disable the Tx interrupt 
 *  \details  */
enum class tx_int_mode : uint8_t { dis = 0, en = 1 };
/*! \enum data_int_mode
 *  \brief Enable or disable the UDR data interrupt 
 *  \details  */
enum class data_int_mode : uint8_t { dis = 0, en = 1 };
/*! \enum rx_mode
 *  \brief Enable or disable the USART receiver
 *  \details  */
enum class rx_mode : uint8_t { dis = 0, en = 1 };
/*! \enum tx_mode
 *  \brief Enable or disable the USART transmitter
 *  \details  */
enum class tx_mode : uint8_t { dis = 0, en = 1 };
/*! \enum spd_mode
 *  \brief Select USART normal or double-speed mode
 *  \details  */
enum class spd_mode : uint8_t { norm, doub };
///@}

/*! \class USART 
 *  \brief Defines an interface for AVR USART operation
 *  \details This class encapsulates register-level access and provides functions for
 *  initialization, transmission and reception. 
 */
class USART {

    public:

    /*! \fn USART
        \brief Construct a USART module instance
     *  \param tx_x Tx pin defined in \link pin.h \endlink (const struct pin)
     *  \param rx_x Rx pin defined in \link pin.h \endlink (const struct pin)
     *  \param uscrnA_addr Address of the UCSRnA register 
     *  \param ucsrnB_addr Address of the UCSRnB register  
     *  \param ubrrn_addr Address of the UBRRn register 
     *  \param udrn_addr Address of the UDRn register */
    USART(const pin& tx_x,
        const pin& rx_x,
        uint16_t ucsrnA_addr, 
        uint16_t ucsrnB_addr,
        uint16_t ubrrn_addr,
        uint16_t udrn_addr);


        /*! \fn init()
         *  \brief Configures USART module parameters
         *  \param baud_rate Desired baud rate 
         *  \param rxInt Enable/disable rx interrupt with \link rx_int_mode enum \endlink 
         *  \param txInt Enable/disable tx interrupt with \link tx_int_mode enum \endlink 
         *  \param datInt Enable/disable UDR data interrupt with \link data_int_mode enum \endlink 
         *  \param rxEn Enable/disable rx interface with \link rx_mode enum \endlink 
         *  \param txEn Enable/disable tx interface with \link tx_mode enum \endlink 
         *  \param speed Select baud rate prescaler with \link spd_mode enum \endlink */
        void init(unsigned long baud_rate, 
                rx_int_mode rxInt, 
                tx_int_mode txInt, 
                data_int_mode datInt,
                rx_mode rxEn,
                tx_mode txEn,
                spd_mode speed);
        
        /*! \fn ready
         *  \brief Indicates if USART is ready to transmit
         *  \returns True if ready, False if not ready */
        bool ready(void);

        /*! \fn write
         *  \brief Writes one byte of binary data
         *  \param data One data byte to send */
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