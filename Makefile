# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
# Inspired by Thies Keulen's makefile
TARGET	 	= device
SOURCES 	= $(wildcard src/*.c) $(wildcard src/modules/*.c)
PTHN		= python

all: 		moderequest compile cpobject upload
cmponly:	compile cpobject upload

ifdef SYSTEMROOT
	PTHN = python
else
	PTHN = python3
endif

moderequest:
	$(PTHN) build/target.py

compile:
	avr-gcc -W -mmcu=atmega328p -Os $(SOURCES) -o $(TARGET).elf

cpobject:
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	$(PTHN) build/upload.py $(TARGET)

clean:
	rm -f src/*.o src/*.hex src/*.elf *.o *.elf *.hex