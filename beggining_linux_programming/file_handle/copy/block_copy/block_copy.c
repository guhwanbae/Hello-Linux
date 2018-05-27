/*
 *  author  :   Gu-hwan Bae
 *  date    :   27 May 2018
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int block_copy(const char*, const char*);

int main(int argc, char* argv[]) {
    if(argc != 2) {
        const char* err_msg = "Invalid input!\n";
        write(2, err_msg, sizeof(err_msg));
        return -1;
    }

    block_copy(argv[1], "file.out");
    
    return 0;
}

int block_copy(const char* file_in, const char* file_out) {
    char buf[1024];
    int fd_in = -1, fd_out = -1;
    int nread;

    fd_in = open(file_in, O_RDONLY);
    fd_out = open(file_out, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((nread = read(fd_in, buf, sizeof(buf))) > 0) {
        write(fd_out, buf, nread);
    }

    return 0;
}

