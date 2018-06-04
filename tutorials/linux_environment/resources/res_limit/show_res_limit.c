/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 4, 2018
 */

/* Showing resouce limits in this program.
   현재 프로그램이 사용하고 있는 시스템 자원 정보를 표시한다. 
   할당된 Stack size, Data segment limit 등을 표시한다. */

#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>   /* int getrlimit(int res, struct rlimit* r_limit)  */
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>

void show_res_limits(int res_flag, const char* res_msg);

int main() {

    show_res_limits(RLIMIT_CORE, "The maximum size of core file(core dump size)");
    show_res_limits(RLIMIT_CPU,"The amount of CPU time that the process can consume");
    show_res_limits(RLIMIT_DATA,"The maximum size of the process's data segment(initialized data, uninitialized data, and heap)");
    show_res_limits(RLIMIT_FSIZE,"The maximum size in bytes of files that process may create");
    show_res_limits(RLIMIT_NOFILE,"The maximum file descriptor number that can be opened by this process");
    show_res_limits(RLIMIT_STACK,"The maximum size of the process stack");
    show_res_limits(RLIMIT_AS,"The maximum size of the process's virtual memory(address space)");
    show_res_limits(RLIMIT_LOCKS, "A limits on the combined number of locks");

    return 0;
}

void show_res_limits(int res_flag, const char* res_msg) {
    struct rlimit res_limits;
    getrlimit(res_flag, &res_limits);
    /* struct rlimit의 member는 cur(soft limit)과 max(hard limit)이 있다.
       soft limit을 넘어서면, Library function들이 error를 반환할 수 있다.
       hard limit을 넘어서면, System이 해당 process를 종료하기 위해 signal을 보낸다. */
    printf("%s : soft = %lu, hard = %lu\n", res_msg, res_limits.rlim_cur, res_limits.rlim_max);
}
