/*
 *  author  :   Gu-hwan Bae
 *  date    :   May 28, 2018
 */

#include <unistd.h> /* gethostname() -> get network name of this computer. */
#include <stdio.h>
#include <stdlib.h>

#include <sys/utsname.h>
/* uname(unix-name) system call.
   int uname(struct utsname* name)
   struct utsname contains OS, host, 
   release info & version of kernel,
   Hardware info. */

int main() {
    char host_name[256]; /* host name은 ssh나 scp같은 네트워크 접근에 식별자로 사용된다. */
    struct utsname uts;

    if(gethostname(host_name, 255) != 0 || uname(&uts) < 0) {
        fprintf(stderr, "Could not get host information!\n");
        return -1;
    }

    printf("Computer host name is %s.\n", host_name);
    printf("System is %s on %s hardware.\n", uts.sysname, uts.machine);
    printf("Nodename is %s.\n", uts.nodename);
    printf("Version is %s, %s.\n", uts.release, uts.version);

    return 0;
}
