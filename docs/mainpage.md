# AVR USART Drivers

Semi hardware-abstracted USART drivers for AVR devices.

---
\section intro Overview

A modular USART driver that is hardware agnostic within the AVR chip family. The files \ref usart.h and \ref usart.cpp define 
    a 'USART' class used to create hardware-backed USART objects. Member functions include basic USART capabilities like
    read and write. 

    The file \ref pin.h defines a 'pin' struct for hardware-abstracted GPIO access. The 'PIN_LIST' macro expands all
        ATMEGA2560 pins automatically. This list can be adjusted for other AVR chips as needed.
\section compinfo Compilation Info

    This software was compiled using:
    - **avr-gcc**
    - **avrdude**
    - **GNU make**

\section mem Memory Usage

The following memory usage statistics are generated automatically usuing `avr-size` during the build process:

\include c++/memusage.txt

---


