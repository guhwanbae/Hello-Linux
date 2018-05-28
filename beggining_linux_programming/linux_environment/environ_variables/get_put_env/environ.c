/*
 *  author  :   Gu-hwan Bae
 *  date    :   28 May 2018
 */

/* getting and putting environment variables. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if(argc == 1 || argc > 3) {
        fprintf(stderr, "usage : environ var [value]\n");
        return -1;
    }

    const char* var = argv[1];
    char* value = getenv(var);	/* getenv(char* var)는 해당 환경변수 명으로 값을 조회하여 반환한다. */

    if(value) {
        printf("Variable %s has value %s.\n", var, value);
    }
    else {
        printf("Variable %s has no value!\n", var);
    }

    if(argc == 3) {
        value = argv[2];
        char* string = (char*) malloc(strlen(var) + strlen(value) + 2);
        if(!string) {
            fprintf(stderr, "out of memeory.\n");
            return -1;
        }
        strcpy(string, var);
        strcat(string, "=");
        strcat(string, value);

        printf("Calling putenv with: %s\n", string);
        if(putenv(string) != 0) { /* putenv(char* string)은 env_var=value 포맷으로 전달받아 환경변수에 값을 할당한다. */
            fprintf(stderr, "putenv failed.\n");
            free(string);
            return -1;
        }
        value = getenv(var);
        if(value) {
            printf("New value of %s is %s\n", var, value);
        }
        else {
            printf("New value of %s is null?\n", var);
        }
    }
    return 0;
}

