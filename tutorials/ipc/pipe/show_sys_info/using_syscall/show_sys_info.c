/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

/* Show host system information using a pipe interface. 
   Pipe is one-way communicating method -
   that inter-process communicate through a file. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* read_fp;
    char buf[1024];
    const char* command_line = "uname -a";

    /* popen()의 command parameter로 "uname -a"를,
       open_mode로 "r"을 사용했다. 
       popen()은 command로 호출된 program의 stdin을 읽고
       File stream에 기록하여 File*를 반환한다. 
       "w"인 경우에는 현재 program의 stdout을 File stream에 기록하고,
       command의 stdin으로 보낸다. */
    if(!(read_fp = popen(command_line, "r"))) {
        perror("popen()");
        return -1;
    }

    memset(buf, '\0', sizeof(buf));
    int n_chars = 0;
    if((n_chars = fread(buf, sizeof(char), 1024, read_fp)) < 0) {
        printf("Can not read from ""uname -a""\n");
        pclose(read_fp);
        return 0;
    }
    printf("Output : -\n%s\n", buf);
    /* popen()으로 호출한 command(program)이 끝낼 때 까지 
       pclose()는 block된다. */
    pclose(read_fp);

    return 0;
}
