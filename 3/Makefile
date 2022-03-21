CC = gcc
CFLAGS = -g -O2
TARGET = main
OBJECTS	= error.o string.o init.o lexer.o parser.o
MAIN_SOURCE	= main.c

.SUFFIEXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(MAIN_SOURCE)

.c .o : 
	rm -f $(OBJECTS)
	rm -f $(TARGET)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)