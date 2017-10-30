# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
# Inspired by Thies Keulen's makefile
TARGET	 	= device
SOURCES 	= $(wildcard src/*.c) $(wildcard src/modules/*.c)

all: compile cpobject upload

compile:
	avr-gcc -W -mmcu=atmega328p -Os $(SOURCES) -o $(TARGET).elf

cpobject:
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	python build/upload.py $(TARGET)

clean:
	rm -f src/*.o src/*.hex src/*.elf *.o *.elf *.hex