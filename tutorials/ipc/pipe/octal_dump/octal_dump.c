/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

 /* Dump a words as octal format using a pipe interface. 
    popen()으로 command "od -c"로 문자열을 보낸다. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage : %s input_words...\n", argv[0]);
        return -1;
    }
    
    int i;
    char buf[BUFSIZ];

    memset(buf, '\0', sizeof(buf));
    for(i = 1; i < argc; ++i) {
        strcat(buf, argv[i]);
        strcat(buf, " ");
    }
    
    /* popen()으로 pipe을 열고, write로 설정한다.
       이 program의 stdout이 pipe를 통해
       command_line의 stdin으로 들어가게 된다. */
    const char* command_line = "od -c";
    FILE* write_fp;
    if(!(write_fp = popen(command_line, "w"))) {
        perror("popen()");
        return -1;
    }

    /* pipe를 통해 쓴다. */
    fwrite(buf, sizeof(char), strlen(buf), write_fp);
    pclose(write_fp);

    return 0;
}



