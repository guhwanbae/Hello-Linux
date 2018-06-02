TARGET				= detached

CC				= gcc
CFLAGS				= -W -Wall -D_REENTRANT
LFLAGS				= -lpthread

SRCS				= detached.c

$(TARGET) :
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

clean :
	rm -f *.o $(TARGET)
