/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 2, 2018
 */

 /* Create a sub thread and set this detached. */

#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mid;

int sub_task_finished;

void* sub_task(void*);

int main() {
    pthread_attr_t sub_thread_attr;
    pthread_t sub_thread;
    
    if(pthread_mutex_init(&mid, NULL) != 0) {
        perror("Faild to initialize a mutex.");
        return -1;
    }

    /* pthread attr을 설정한다. 이 객체를 설정해서 생성할 Thread의 특성을 정할 수 있다. */
    if(pthread_attr_init(&sub_thread_attr) != 0) {
        perror("Attribute creation failed.");
        return -1;
    }
    
    /* Sub thread를 Detached 로 만들어서, Sub task를 수행하게 하고, 
       Main thread에서 join하기위해 기다리지 않는다. 
       pthread attr을 설정하지 않으면 기본값은 Joinable thread로 생성된다. */
    if(pthread_attr_setdetachstate(&sub_thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("Setting detached attribute failed.");
        return -1;
    }

    printf("Create a sub thread as detached thread.\n");
    if(pthread_create(&sub_thread, &sub_thread_attr, sub_task, (void*)"Hello Tux!") != 0) {
        perror("Faild to create a sub thread.");
        return -1;
    }

    while(1) {
        pthread_mutex_lock(&mid);
        if(sub_task_finished) {
            pthread_mutex_unlock(&mid);
            break;
        }
        pthread_mutex_unlock(&mid);
        printf("Waiting for sub thread to finished.\n");
        sleep(1);
    }
    printf("Sub thread finished.\n");

    printf("Bye!\n");
    return 0;
}

void* sub_task(void* arg) {
    printf("Task of sub thread is running. Argument was %s\n",(char*)arg);
    printf("Sub task : sleep 5 seconds.\n");
    sleep(5);
    printf("Task of sub thread is finished.\n");

    pthread_mutex_lock(&mid);
    sub_task_finished = 1;
    pthread_mutex_unlock(&mid);

    pthread_exit(NULL);
}
