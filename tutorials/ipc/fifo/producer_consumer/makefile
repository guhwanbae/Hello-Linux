CC			= gcc
CFLAGS			= -W -Wall

all : producer consumer

producer : producer.c
	$(CC) $(CFLAGS) -o $@ $<

consumer : consumer.c
	$(CC) $(CFLAGS) -o $@ $<

clean :
	rm -f *.o producer consumer my_fifo
