#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAT_PORT (16261)
#define BUFSIZE (1024)

void *send_message(void *arg);
void *recv_message(void *arg);
void error_handling(char *message);

int main()
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_result;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(CHAT_PORT);

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect()");
        return -1;    
    }

    pthread_create(&snd_thread, NULL, send_message, (void*)sock);
    pthread_create(&rcv_thread, NULL, recv_message, (void*)sock);

    pthread_join(snd_thread, &thread_result);
    pthread_join(rcv_thread, &thread_result);

    close(sock);

    return 0;
}

void *send_message(void *arg)
{
    int sock = (int)arg;
    char message[BUFSIZE];

    while(1)
    {
        fgets(message, BUFSIZE, stdin);
        if(!strcmp(message, "q\n"))
        {
            close(sock);
            exit(0);
        }
        write(sock, message, strlen(message));
    }

    close(sock);

    return NULL;
}

void *recv_message(void *arg)
{
    int sock = (int)arg;
    char message[BUFSIZE];
    int len;

    while(1)
    {
        len = read(sock, message, BUFSIZE-1);
        if(len < 0) {
            break;
        }
        message[len] = 0;
        fputs(message, stdout);
    }
    
    close(sock);

    return NULL;
}
