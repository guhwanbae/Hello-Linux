/*
 *  author  :   Gu-hwan Bae
 *  date    :   30 May 2018
 */

 /* Running ps with execlp() */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    /* 이 program pid와 execlp()가 실행한 명령(ps ax)의 pid를 비교해보자.  */
    printf("This program PID = %d\n", getpid());
    printf("Running ps with execlp()\n");
    execlp("ps", "ps", "ax", NULL);

    /* execlp()를 호출하고 난 뒷부분은 절대로 도달하지 못한다.
       단 error가 발생하면 exec()는 -1을 return한다. */
    /* execlp()로 실행되는 ps로도 이 program을 찾을 수 없다. 
       이 program process가 execlp()가 수행한 process로 대체된다. */
    printf("Done.\n");
    return 0;
}
