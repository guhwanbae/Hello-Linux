CC      = gcc
CFLAGS  = -W -Wall
TARGET  = environ

OBJECTS = environ.o

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

clean :
	rm -f $(OBJECTS) $(TARGET)

environ.o : environ.c
