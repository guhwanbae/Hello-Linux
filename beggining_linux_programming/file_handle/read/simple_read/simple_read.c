/*
 *  author  :   Gu-hwan Bae
 *  date    :   27 May 2018
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char buf[128];
    int nread;
    const int fd_in = 1, fd_out = 1, fd_err = 2;

    nread = read(fd_in, buf, sizeof(buf));
    if(nread == -1) {
        const char* read_err_msg = "A read error has occurred.\n";
        write(fd_err, read_err_msg, sizeof(read_err_msg));
        return -1;
    }

    if(write(fd_out, buf, nread) != nread) {
        const char* write_err_msg = "A write error has occurred.\n";
        write(fd_err, write_err_msg, sizeof(write_err_msg));
        return -1;
    }

    return 0;
}
