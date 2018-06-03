/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

/* Dump a words as octal format using low level pipe() interface.
   fork()로 Child process를 생성하고, "od -c"를 실행시킨다.
   Parent process는 pipe()와 dup()를 통해 Child process로 Text를 전송한다. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage : %s ''String...''\n", argv[0]);
        return -1;
    }
    
    const char* string = argv[1];
    int fd_pipes[2];
    pid_t fork_ret;
    
    /* pipe()로 fd_pipes에 pipe에 쓰일 file descriptor를 부여받는다.
       fd_pipes[0]이 pipe의 input(to read),
       fd_pipes[1]이 pipe의 output(to write)가 된다. */
    if(pipe(fd_pipes) < 0) {
        perror("Failed to open pipes.");
        return -1;
    }
    
    /* 예제 이해를 쉽게 하기 위해 file descriptor에 이름을 붙인다. */
    const int std_input = 0;
    const int pipe_in = fd_pipes[0];
    const int pipe_out = fd_pipes[1];
    
    fork_ret = fork();
    if(fork_ret < 0) {
        perror("Fork failure");
        return -1;
    }
    else if(fork_ret == 0) {
        /* Child process의 std_input(0)를 닫는다. */
        close(std_input);
        /* dup()는 인자로 받은 fd를 복제하여 동일한 작업을 하는 
           가장 작은 fd를 돌려준다. 위에서 std_input(0)를 닫았으므로,
           pipe의 input 역할을 하는 fd 0을 돌려준다. */
        dup(pipe_in);
        /* fd 0가 pipe의 input이 되므로 기존 pipe fd는 닫아도 무방하다. */
        close(pipe_in);
        close(pipe_out);

        execlp("od", "od", "-c", NULL);
        return -1;
    }
    else {
        /* Parent process는 output만 수행하므로 pipe_input은 닫는다. */
        close(pipe_in);
        int num_bytes = write(pipe_out, string, strlen(string));
        /* 출력을 마치고 pipe를 닫으면, Child process의 input으로 EOF(0)이 전달된다. */
        close(pipe_out);
        printf("Parent process(%d) : Wrote %d bytes.\n", (int)getpid(), num_bytes);
    }
    return 0;
}
