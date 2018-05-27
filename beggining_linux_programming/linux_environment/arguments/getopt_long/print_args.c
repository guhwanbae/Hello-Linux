/*
 *  author  :   Gu-hwan Bae
 *  date    :   27 May 2018
 */

/* print arguments by using getopt(). 
   getopt_long() is function as GNU C Libraries(glic).
   getopt_long() support to get long type argument(GNU style).
   e.g) --verbose == -v
        --version == -V
        --warnings == -W
        ... */

#include <stdio.h>
#include <unistd.h> /* int getopt(int argc, char *const argv[], const char* optstring); */
#include <stdlib.h>

#define _GNU_SOURCE /* Using GNU Source */
#include <getopt.h> /* int getopt_long(int argc, char *const argv[], const char* optstring, struct option*, char(*)[]) */

int main(int argc, char* argv[]) {
    int opt;

    /* struct option {
           const char* name;    -> long type option.
           int has_arg;         -> 마찬가지로 추가적인 arguments를 갖는 여부.
           int* flag;           -> option(val)을 반환받을 변수를 pointer로 받는다. NULL이면 getopt_long()은 val을 반환한다.
           int val;             -> short type option
       }; */

    struct option longopts[] = {
        {"initialize", 0, NULL, 'i'},
        {"file", 1, NULL, 'f'},
        {"list", 0, NULL, 'l'},
        {"restart", 0, NULL, 'r'},
        {0, 0, 0, 0}};

    while((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
        /* 3번째 인자는 -(dash)로 받을 수 있는 option들을 나타낸다.
           option 앞의 :(colon)은 추가적인 argument를 받을 수 있음을 의미한다.
           e.g) :f -> -f file.in */
       /* getopt()는 argv에서 발견한 option을 반환한다. */
       switch(opt) {
           case 'i':
           case 'l':
           case 'r':
               printf("option : %c\n", opt);
               break;
           case 'f':
               printf("filename : %s\n", optarg);
               break;
           case ':':
           /* option이 추가적인 argument를 받는다고 명시했지만 받지 못한 경우
              getopt()는 :을 반환한다. */
               printf("option needs a value\n");
               break;
           case '?':
           /* 지정한 option이 아닐경우 getopt()는 ?를 반환한다.
              extern global variable optopt은 해당(지정되지 않은) option */
               printf("unknown option : %c\n", optopt);
               break;
       }
    }
    /* 모든 option을 처리하고 남은 argument의 index가
       extern global variable optind로 지정된다. */
    for(; optind < argc; ++optind) {
        printf("argument : %s\n", argv[optind]);
    }

    printf("End of this program.");
    return 0;
}
