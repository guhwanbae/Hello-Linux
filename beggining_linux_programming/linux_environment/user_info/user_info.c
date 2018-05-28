/*
 *  author  :   Gu-hwan Bae
 *  date    :   May 28, 2018
 */

/* Showing user information.
   uid, gid, home path, default shell type... */

#include <sys/types.h>  /* uid_t, gid_t ... */
#include <pwd.h>        /* (user info) struct passwd ... */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    uid_t uid = getuid();
    gid_t gid = getgid();

    printf("User is %s\n", getlogin()); /* getlogin()은 현재 user name을 반환한다. */
    printf("User : uid = %d, gid = %d\n", uid, gid);

    struct passwd* pw = getpwuid(uid);
    /* 암호화된 password file(/etc/shadow)로부터 user info를 얻는다.
       /etc/passwd를 직접접근하는 방법보다 안전하고 표준적인 방법이다. */

    printf("UID passwd entry:\n");
    printf("name = %s, uid = %d, gid = %d, ", pw->pw_name, pw->pw_uid, pw->pw_gid);
    printf("home = %s, shell = %s\n", pw->pw_dir, pw->pw_shell);

    pw = getpwnam("root"); /* user name으로 passwd struct를 얻는다. */
    printf("root passwd entry:\n");
    printf("name = %s, uid = %d, gid = %d, ", pw->pw_name, pw->pw_uid, pw->pw_gid);
    printf("home = %s, shell = %s\n", pw->pw_dir, pw->pw_shell);

    return 0;
}

