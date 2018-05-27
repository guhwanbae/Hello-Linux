/*
 *  author  :   Gu-hwan Bae
 *  date    :   27 May 2018
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("argv[0] == name of program : %s\n", argv[0]);

    if(argc > 1) {
        int arg;
        for(arg = 1; arg < argc; ++arg) {
            if(argv[arg][0] == '-') {
                printf("option : %s\n", argv[arg]+1);
            }
            else {
                printf("arguments %d : %s\n", arg, argv[arg]);
            }
        }
    }

    return 0;
}
