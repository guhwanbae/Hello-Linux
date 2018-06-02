/*
 *  author  :   Gu-hwan Bae
 *  date    :   May 30, 2018
 */

/* Execute Shell command using system(). 
   It's simpler more than calling exec(). */

#include <stdio.h>
#include <stdlib.h> /* int system(const char* command) */
#include <string.h>

void parse(int argc, char* argv[], char* str);

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage : %s command\n", argv[0]);
        return -1;
    }

    char cmd[BUFSIZ];
    parse(argc, argv, cmd);

    /* Running command with system(). */
    /* libc 의 system()을 사용하여 shell command를 실행시켰다. */
    /* system(command)는 $sh -c command와 동일하다. */
    int res = system(cmd);
    if(res < 0) {
        perror("system()");
        return -1;
    }
    else if(res == 127) {
        printf("Failed : Running %s\n", cmd);
        return -1;
    }

    /* system()은 command 실행이 완료된 후에 return된다. */
    /* 단 background로 실행(&) 하는 경우 system()이 return되기 전에 process가 끝나버릴 수 있다. */
    printf("End of this program.\n");
    return 0;
}

void parse(int argc, char* argv[], char* str) {
    int i;
    for(i = 1; i < argc; ++i) {
        strcat(str, argv[i]);
        strcat(str, " ");
    }
}
        
