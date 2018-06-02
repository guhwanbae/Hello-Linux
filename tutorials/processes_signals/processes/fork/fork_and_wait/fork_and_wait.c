#include <unistd.h>
#include <sys/types.h>  /* pid_t fork()  */
#include <sys/wait.h>   /* pid_t wait(int* stat_loc) */

#include <stdio.h>
#include <stdlib.h>

/* Wait for child process to finished(change state). */

void wait_for_child();
void sleep_and_msg(int, const char*);

int main() {
    printf("fork()\n");
    pid_t pid = fork();

    switch(pid) {
        case -1 :
            perror("fork()");
            return -1;
            break;
        case 0 :
            printf("This is child process(%d)\n", getpid());
            printf("Let it kill if you wanna know what it happen.\n");
            sleep_and_msg(10, "Sleep : child process.");       
            break;
        default :
            printf("This is parent process(%d)\n", getpid());

            wait_for_child();
            printf("End of parent process\n");
            break;
    }
    return 0;
}

void wait_for_child() {
    /* Child process가 종료되길 기다린다. */
    int stat_val;
    /* wait는 Child process가 종료되길 기다리며, 
       전달한 stat_val로 어떻게 종료되었는지 확인 할 수 있다.  */
    pid_t cpid = wait(&stat_val);

    /* sys/wait.h에 정의된 Macro로 종료상태를 확인 할 수 있다. */
    printf("Child process(%d) has finished.\n", cpid);
    if(WIFEXITED(stat_val)) {
        printf("Child process exited with return value %d.\n", WEXITSTATUS(stat_val));
    }
    else if(WIFSIGNALED(stat_val)) {
        printf("Child process terminated by signal(%d).\n", WTERMSIG(stat_val));
    }
    else {
        printf("Child process aborted!\n");
    }
}

void sleep_and_msg(int n_sec, const char* msg) {
    while(n_sec > 0) {
        printf("%d...%s\n", n_sec--, msg);
        sleep(1);
    }
}
