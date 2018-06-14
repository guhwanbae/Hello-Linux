/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 14, 2018
 */

 /* Running ps with execlp() */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage : %s script.py\n", argv[0]);
	return -1;
    }
    /* execlp()으로 Python interpreter를 호출하여 script.py를 실행하게 한다. */
    const char* script_file = argv[1];
    execlp("python3", "python3", script_file, NULL);

    /* execlp()를 호출하고 난 뒷부분은 절대로 도달하지 못한다.
       단 error가 발생하면 exec()는 -1을 return한다. */
    /* execlp()로 실행되는 ps로도 이 program을 찾을 수 없다. 
       이 program process가 execlp()가 수행한 process로 대체된다. */
    printf("%s : Done.\n", argv[0]);
    return 0;
}
