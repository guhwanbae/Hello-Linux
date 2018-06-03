/*
 * chat_server.c
 *
 *  Created on: Jun 1, 2018
 *      Author: guhwanbae
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS (20)

/* Interface for Clients Management
   클라이언트 관리용 인터페이스
   Set으로 구현하면 효율적이었으나... 시간이 없는 관계로 리스트로 구현 */
struct clients_info {
    char user[128];
    int csock;
};

struct clients_tb {
    struct clients_info clinfos[MAX_USERS];
    int len;
};

void cltb_init(struct clients_tb* cltb);
int cltb_push(struct clients_tb* cltb, struct clients_info* clinfo);
int cltb_pop(struct clients_tb* cltb, struct clients_info* clinfo);
int cltb_cmp(struct clients_tb* cltb, struct clients_info* clinfo);
void clinfo_init(struct clients_info* clinfo);
int clinfo_isempty(struct clients_info* clinfo);
void clinfo_copy(struct clients_info* dst, struct clients_info* src);
int clinfo_cmp(struct clients_info* first, struct clients_info* second);

struct clients_tb cltb;

/* Chatting Server interface
   채팅 서버 인터페이스 */

#define CHAT_PORT (16261)

void send_msg(struct clients_info* clinfo, char* msg, int num_bytes);
void* chat_sv_recv(void *);

pthread_mutex_t cl_lck;

int main()
{
    printf("Hello. I'm chat server.\n");

    int ssock, csock;
    struct sockaddr_in svaddr, claddr;
    int clen;
    char* clip;
    pthread_t thread;

    if(pthread_mutex_init(&cl_lck, NULL)) {
        perror("mutex_init()");
        return -1;
    }

    ssock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svaddr.sin_port = htons(CHAT_PORT);

    if(bind(ssock, (struct sockaddr*)&svaddr, sizeof(svaddr)) < 0) {
        perror("socket bind()");
        return -1;
    }

    if(listen(ssock, 20) < 0) {
        perror("socket listen()");
        return -1;
    }

    cltb_init(&cltb);

    while(1) {
        clen = sizeof(claddr);
        csock = accept(ssock, (struct sockaddr*)&claddr, &clen);

        struct clients_info clinfo;
        clip = inet_ntoa(claddr.sin_addr);
        strcpy(clinfo.user, clip);
        clinfo.csock = csock;

        pthread_mutex_lock(&cl_lck);
        cltb_push(&cltb, &clinfo);
        pthread_mutex_unlock(&cl_lck);

        pthread_create(&thread, NULL, chat_sv_recv, (void*)&clinfo);
        printf("New client, Hello : %s\n", inet_ntoa(claddr.sin_addr));
    }
    
    close(ssock);

    return 0;
}

/* 채팅 서버 인터페이스 구현 */

void* chat_sv_recv(void* arg) {
    struct clients_info clinfo;
    clinfo_copy(&clinfo, (struct clients_info*)arg);

    char buf[1024];
    int num_bytes = 0;
    while((num_bytes = read(clinfo.csock, buf, sizeof(buf))) > 0) {
        send_msg(&clinfo, buf, num_bytes);
    }
    
    close(clinfo.csock);
    return NULL;
}

void send_msg(struct clients_info* clinfo, char* msg, int num_bytes) {
    int i, len = cltb.len;
    for(i = 0; i < len; ++i) {
        if(clinfo_cmp(&(cltb.clinfos[i]), clinfo) == 0) {
            write((cltb.clinfos[i]).csock, msg, num_bytes);
        }
    }
}

/* 클라이언트 관리 인터페이스 구현 */

void cltb_init(struct clients_tb* cltb) {
    cltb->len = MAX_USERS;
    int i;
    for(i = 0; i < cltb->len; ++i) {
        clinfo_init(&(cltb->clinfos[i]));
    }
}

int cltb_push(struct clients_tb* cltb, struct clients_info* clinfo) {
    int i, len = cltb->len;
    for(i = 0; i < len; ++i) {
        if(clinfo_isempty(&(cltb->clinfos[i]))) {
            clinfo_copy(&(cltb->clinfos[i]), clinfo);
            return 1;
        }
    }
    return 0;
}

int cltb_pop(struct clients_tb* cltb, struct clients_info* clinfo) {
    int i, len = cltb->len;
    for(i = 0; i < len; ++i) {
        if(clinfo_cmp(&(cltb->clinfos[i]), clinfo)) {
            clinfo_init(&(cltb->clinfos[i]));
        }
    }
    return 0;
}

int cltb_cmp(struct clients_tb* cltb, struct clients_info* clinfo) {
    int i, len = cltb->len;
    for(i = 0; i < len; ++i) {
        if(clinfo_cmp(&(cltb->clinfos[i]), clinfo)) {
            return 1;
        }
    }
    return 0;
}

void clinfo_init(struct clients_info* clinfo) {
    memset(clinfo->user, '\0', sizeof(clinfo->user));
    strcpy(clinfo->user, "no-name");
    clinfo->csock = -1;
}

int clinfo_isempty(struct clients_info* clinfo) {
    if(clinfo->csock == -1) {
        return 1;
    }
    return 0;
}

void clinfo_copy(struct clients_info* dst, struct clients_info* src) {
    strcpy(dst->user, src->user);
    dst->csock = src->csock;
}

int clinfo_cmp(struct clients_info* first, struct clients_info* second) {
    if(first->csock == second->csock) {
        return 1;
    }
    return 0;
}
