TARGET				= create_and_join

CC				= gcc
CFLAGS				= -W -Wall -D_REENTRANT
LFLAGS				= -lpthread

SRCS				= create_and_join.c

$(TARGET) :
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

clean :
	rm -f *.o $(TARGET)
