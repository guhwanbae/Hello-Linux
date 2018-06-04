CC = gcc
CFLAGS = -W -Wall
LFLAGS = -lpthread

all : chat_client chat_server

chat_client : 1626191_client.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

chat_server : 1626191_server.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean :
	rm -f *.o chat_client chat_server
