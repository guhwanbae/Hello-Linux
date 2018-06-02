/*
 *  author : Gu-hwan Bae
 *  date   : 27 May 2018
 */

#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd_out = 1;
    int fd_err = 2;
    const char out_msg[] = "Here is some data.\n";
    const char err_msg[] = "A write error has occured on file descriptor 1.\n";

    if(write(fd_out, out_msg, sizeof(out_msg)) != sizeof(out_msg)) {
        write(fd_err, err_msg, sizeof(err_msg));
        return -1;
    }
    return 0;
}
