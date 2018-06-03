/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

/* Producer reads string from the text file and
   writes it to the FIFO.
   Producer는 입력 텍스트로부터 문자열을 읽어 FIFO에 기록한다.
   Consumer는 FIFO에서 문자열을 읽어서 화면에 출력한다. */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> /* 하나의 FIFO에 넣을 수 있는 데이터 상한 PIPE_BUF  */

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage : %s file_path\n", argv[0]);
        return -1;
    }

    const char* text_file = argv[1];
    int fd_text_file;

    if((fd_text_file = open(text_file, O_RDONLY)) < 0) {
        perror("Failed to open text file.");
        return -1;
    }

    const char* fifo_path = "./my_fifo";
    int fd_fifo;
    /* mkfifo()로 fifo를 생성. */
    if(mkfifo(fifo_path, 0777) < 0) {
        perror("Failed to create fifo.");
        return -1;
    }
    printf("Make a fifo %s\n", fifo_path);
    
    /* fifo나 pipe도 일반 파일처럼 열고 닫을 수 있다. 
       단 fifo나 pipe는 단방향(One-way) 통신이다. */
    if((fd_fifo = open(fifo_path, O_WRONLY)) < 0) {
        perror("Failed to open fifo.");
        return -1;
    }
    printf("Read from %s, Write to %s\n", text_file, fifo_path);

    /* fifo에는 한번에 보낼 수 있는 데이터의 양이 제한되어있다.
       이는 system에서 정하는데, limits.h의 Macro PIPE_BUF로 알 수 있다. */
    char buf[PIPE_BUF];
    int num_bytes = 0, sent_bytes = 0;

    memset(buf, '\0', sizeof(buf));
    while((num_bytes = read(fd_text_file, buf, PIPE_BUF)) > 0) {
        num_bytes = write(fd_fifo, buf, num_bytes);
        if(num_bytes < 0) {
            perror("Write error on fifo.");
            return -1;
        }
        sent_bytes += num_bytes;
        memset(buf, '\0', sizeof(buf));
    }

    close(fd_fifo);
    close(fd_text_file);
    
    double sent_mb = ((double)sent_bytes)/(1024*1024);
    printf("Producer : Process finished, write %d byets, ( = %.2f MB)\n", sent_bytes, sent_mb);

    return 0;
}
