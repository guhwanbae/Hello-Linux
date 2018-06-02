/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

/* Cancel a sub thread on main thread. */

#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

void* sub_task(void*);

int main() {
    pthread_t sub_thread;

    /* Cancelable thread를 생성하기 위해서는, 
       Thread가 받는 Task 내부에서 Cancelable하게 설정할 수 있다. */
    if(pthread_create(&sub_thread, NULL, sub_task, NULL)) {
        perror("Failed to create a sub thread.");
        return -1;
    }
    
    printf("Main thread : sleep 5 seconds.\n");
    sleep(5);

    printf("Main thread : Canceling a sub thread.\n");

    /* Sub thread를 Cancel. */
    if(pthread_cancel(sub_thread) != 0) {
        perror("Thread cancelation failed.");
        return -1;
    }

    printf("Main thread : Waiting for thread to finish.\n");
    if(pthread_join(sub_thread, NULL) != 0) {
        perror("Thread join failed.");
        return -1;
    }
    
    printf("Bye\n");

    return 0;
}

void* sub_task(void* arg) {
    /* Thread가 받는 내부 Task에서 Cancelable state로 설정한다.  */
    if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0) {
        perror("pthread_setcancelstate() failed.");
        exit(EXIT_FAILURE);
    }
    /* 이 Thread를 CANCEL_DEFERRED로 설정한다.
        PTHREAD_CANCEL_ASYNCHRONOUS : cancel()이 호출된 즉시 종료된다.
        PTHREAD_CANCEL_DEFFERED : join(), cond_wait() 등을
                                  호출하기 전까지 Cancel이 미뤄진다. */
    if(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL) != 0) {
        perror("pthread_setcanceltype() failed.");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        printf("Sub thread is still running.\n");
        sleep(1);
    }

    pthread_exit(NULL);
}
