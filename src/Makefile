CC = gcc
CFLAGS = -g -O2 -w
TARGET = osh
OBJECTS	= error.o string.o init.o lexer.o parser.o built_in_command.o linked_list.o process_manager.o
MAIN_SOURCE	= osh.c

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