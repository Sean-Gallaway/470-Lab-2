#Define which C compiler to use
CC=gcc

#compile flags
CFLAGS=-Wall -g

# set name of the executable
TARGET=Lab2

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
