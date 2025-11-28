# -------- USER SETTINGS --------
MCU = atmega2560
F_CPU = 16000000UL
SERIAL_BAUD = 19200

# Serial upload settings
PORT = COM5
PROGRAMMER = wiring
BAUD = 115200

# Project name
TARGET = firmware

# --------------------------------

# Tools
CXX = avr-g++
CC  = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Flags
CPPFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=gnu++17 -Wall -Iinclude
CFLAGS   = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=gnu11   -Wall -Iinclude
LDFLAGS  = -mmcu=$(MCU)

# Find all source files
C_SOURCES   = $(wildcard src/*.c)
CPP_SOURCES = $(wildcard src/*.cpp)
OBJ = $(C_SOURCES:.c=.o) $(CPP_SOURCES:.cpp=.o)

# Default target
all: $(TARGET).hex

# Compile C++
src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# Compile C
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link ELF
$(TARGET).elf: $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@

# HEX file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Upload
flash: $(TARGET).hex
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) \
	    -U flash:w:$(TARGET).hex:i

# Serial monitor (if you want one)
monitor:
	picocom -b $(SERIAL_BAUD) $(PORT)

# Clean up
clean:
	rm -f src/*.o $(TARGET).elf $(TARGET).hex
