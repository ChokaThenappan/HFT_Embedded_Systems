CFLAGS = -Wall

OBJECTS = display.o fbputchar.o

TARFILES = Makefile display.c \
	fbputchar.h fbputchar.c \

display : $(OBJECTS)
	cc $(CFLAGS) -o display $(OBJECTS) -lusb-1.0 -pthread


display.o : display.c fbputchar.h
fbputchar.o : fbputchar.c fbputchar.h

.PHONY : clean
clean :
	rm -rf *.o display
