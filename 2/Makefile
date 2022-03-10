CC = gcc
CFLAGS = -g -O2
TARGET = main
OBJECTS	= error.o parser.o command.o
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