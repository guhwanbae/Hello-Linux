/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

/* Consumer read the string from the FIFO and 
   writes to standard output. 
   Consumer는 FIFO를 통해 Text를 받아서 화면에 출력한다. */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h> /* PIPE_BUF */
#include <string.h> /* memeset() */

int main() {
    const char* fifo_path = "./my_fifo";
    int fd_fifo;

    printf("Consumer : Process(%d) opening FIFO O_RDONLY.\n", getpid());
    if((fd_fifo = open(fifo_path, O_RDONLY)) < 0) {
        perror("Failed to open fifo.");
        return -1;
    }
    printf("Consumer : Process(%d) opened FIFO(%d)\n", getpid(), fd_fifo);

    char buf[PIPE_BUF];
    int num_bytes = 0, read_bytes = 0;

    memset(buf, '\0', sizeof(buf));
    while((num_bytes = read(fd_fifo, buf, sizeof(buf))) > 0) {
        printf("%s\n", buf);
        read_bytes += num_bytes;
        memset(buf, '\0', sizeof(buf));
    }
    close(fd_fifo);
    
    double read_mb = ((double)read_bytes)/(1024*1024);
    printf("Consumer : Process finished. %d bytes read. ( = %.2fMB)\n", read_bytes, read_mb);

    return 0;
}
