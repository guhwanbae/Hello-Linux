/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char msg[128] = "Hello, Tux!";

void* sub_task(void*);

int main() {
    printf("Hello!\n");
    printf("Message(global val) is %s\n", msg);

    pthread_t sub_thread;
    char* sub_retval;

    if(pthread_create(&sub_thread, NULL, sub_task, (void*)msg) != 0) {
        perror("Failed to create sub thread.");
        return -1;
    }
    printf("Waiting for sub thread to finish.\n");
    if(pthread_join(sub_thread, (void*)&sub_retval) != 0) {
        perror("Failed to sub thread join.");
        return -1;
    }
    printf("Sub thread joined, it returned %s\n", sub_retval);
    printf("Message(global val) is now %s\n", msg);

    printf("Bye!\n");
    return 0;
}

void* sub_task(void* arg) {
    printf("Task of sub thread is running, Argument was %s\n", (char*)arg);
    sleep(3);
    strcpy(msg, "Hello, Daemon!");
    pthread_exit("Thx! Sub task is finished.");
}
