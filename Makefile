# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
# Inspired by Thies Keulen's makefile
TARGET	 	= device
SOURCES 	= $(wildcard src/*.c) $(wildcard src/modules/*.c)

all: 		moderequest compile cpobject upload
cmponly:	compile cpobject upload

moderequest:
	python3 build/target.py

compile:
	avr-gcc -W -mmcu=atmega328p -Os $(SOURCES) -o $(TARGET).elf

cpobject:
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	python3 build/upload.py $(TARGET)

clean:
	rm -f src/*.o src/*.hex src/*.elf *.o *.elf *.hex