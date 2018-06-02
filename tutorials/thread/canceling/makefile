TARGET				= canceling

CC				= gcc
CFLAGS				= -W -Wall -D_REENTRANT
LFLAGS				= -lpthread

SRCS				= canceling.c

$(TARGET) :
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

clean :
	rm -f *.o $(TARGET)
