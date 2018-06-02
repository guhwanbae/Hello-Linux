/*
 *  author  :   Gu-hwan Bae
 *  date    :   27 May 2018
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

void file_copy(const char*, const char*);

int main(int argc, char* argv[]) {
    if(argc != 2) {
        const char* err_msg = "Invalid_input.\n";
        write(2, err_msg, sizeof(err_msg));
        return -1;
    }

    file_copy(argv[1], "file.out");

    return 0;
}

void file_copy(const char* file_in, const char* file_out) {
    int fd_in = -1, fd_out = -1;
    
    fd_in = open(file_in, O_RDONLY);
    fd_out = open(file_out, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);  // rw------- = 600

    char ch;
    while(read(fd_in, &ch, 1) == 1) {   // read just a character.
        write(fd_out, &ch, 1);          // write just a character.
    }
}
