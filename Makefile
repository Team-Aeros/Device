# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
TARGET	 	= device
CC			= avr-gcc

INCLUDES 	=
LIBRARIES 	=
SOURCES 	= $(wildcard src/*.c)
OBJECTS 	= $(SOURCES:.c=.elf)

%.hex: %.elf
	avr-gcc -W -mmcu=atmega328p -Os $(OBJECTS) -o $(TARGET).elf
	
%.hex: %.o
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	
upload:
	avrdude -v -p m32 -c STK500 -e -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex

clean:
	rm -f *.o