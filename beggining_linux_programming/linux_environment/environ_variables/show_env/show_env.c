/*
 *  author  :   Gu-hwan Bae
 *  date    :   28 May 2018
 */

/* Showing enviroment variables. 
   Results varying from system to system, 
   shell to shell, user to user. */

#include <stdlib.h>
#include <stdio.h>

extern char** environ; 
/* extern variable environ은 user shell의 모든
   env var을 C-style string array로 갖고 있다. */

int main() {
    const char** env = environ;

    while(*env) { /* string의 array를 순회하여 출력. */
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
