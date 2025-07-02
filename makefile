MCU=atmega328p
F_CPU=16000000UL
BAUD=115200
PORT=/dev/ttyACM1
PROGRAMMER=arduino

# Paths
AVRDUDE=avrdude
CC=avr-gcc
OBJCOPY=avr-objcopy

# Files
TARGET=main
OBJ=$(TARGET).o
HEX=$(TARGET).hex

# Flags
CFLAGS=-Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -std=c++11

all: $(HEX)

$(OBJ): $(TARGET).cpp
	avr-g++ $(CFLAGS) -c -o $@ $<

$(HEX): $(OBJ)
	avr-g++ $(CFLAGS) -o $(TARGET).elf $(OBJ)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $@

upload: $(HEX)
	$(AVRDUDE) -V -patmega328p -carduino -P$(PORT) -b$(BAUD) -D -Uflash:w:$(HEX):i

clean:
	rm -f *.o *.elf *.hex
