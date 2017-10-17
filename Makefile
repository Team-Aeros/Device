# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
TARGET	 	= device

INCLUDES 	=
LIBRARIES 	=
SOURCES 	= $(wildcard src/*.c)
OBJECTS 	= $(SOURCES:.c=.o)

program: $(OBJECTS)
	avr-gcc -W -mmcu=atmega32 -Os $(OBJECTS) -o $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avrdude -v -p m32 -c STK500 -e -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex

clean:
	rm -f *.o