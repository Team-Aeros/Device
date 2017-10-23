# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
# Inspired by Thies Keulen's makefile
TARGET	 	= device
SOURCES 	= $(wildcard src/*.c)

all: compile cpobject upload

compile:
	avr-gcc -W -mmcu=atmega328p -Os $(SOURCES) -o $(TARGET).elf

cpobject:
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	avrdude -F -V -c arduino -p atmega328p -P COM5 -b 115200 -U flash:w:$(TARGET).hex

clean:
	rm -f src/*.o src/*.hex src/*.elf