# Based on http://www.puxan.com/web/howto-write-generic-makefiles/
EXECUTABLE 	= device

INCLUDES 	=
LIBRARIES 	=
SOURCES 	= $(wildcard src/*.c)
BIN 		= bin
OBJECTS 	= $(SOURCES:.c=.o)

program: $(OBJECTS)
	avr-gcc $(OBJECTS) -o

%.o: %.c
	avr-gcc $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o