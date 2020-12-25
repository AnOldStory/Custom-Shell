CC = gcc
CFLAGS = -g -O2
TARGET = hShell
OBJECTS	= error.o debug.o lexer.o parser.o symbol.o init.o
MAIN_SOURCE	= main.c

.SUFFIEXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(MAIN_SOURCE)

.c .o : 
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)