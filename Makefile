# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
# Inspired by Thies Keulen's makefile
TARGET	 	= device

INCLUDES 	=
LIBRARIES 	=
SOURCES 	= $(wildcard src/*.c)

UNAME:=$(shell uname)

ifeq "$(UNAME)" "windows"
	PORT = COM5
else
	PORT = /dev/ttyACM0
endif

all: compile cpobject upload

compile:
	avr-gcc -W -mmcu=atmega328p -Os $(SOURCES) -o $(TARGET).elf

cpobject:
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	avrdude -F -V -c arduino -p atmega328p -P $(PORT) -b 115200 -U flash:w:$(TARGET).hex

clean:
	rm -f src/*.o src/*.hex src/*.elf