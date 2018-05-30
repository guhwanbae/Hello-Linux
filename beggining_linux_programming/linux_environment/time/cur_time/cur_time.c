/*
 *	author	:	Gu-hwan Bae
 *	date	:	May 29, 2018
 */

/* Getting a time info using clib <time.h> or linux system calls. */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>	/* gettimeofday(struct timeval*, struct timezone*)  */
#include <stdlib.h>

int main() {
	time_t clib_time;
	time(&clib_time);	/* using c lib time.h */
	                /* return a current calendar time encoded as a time_t.  */
	printf("using c library(since epoch to a calendar local time)\n");
	printf("time : %lu(sec)\n", clib_time);

	struct timeval ltime;
	gettimeofday(&ltime, NULL);	
	/* using linux sys call */
	/* tz(timezone) has never used. */
	printf("using linux sys-call(since epoch to a calendar local time)\n");
	printf("time : %ld(sec) + %ld(microsec)\n", ltime.tv_sec, ltime.tv_usec);

	/* using c lib time.h, convert to human readable time*/
	printf("human readable time : %s\n", ctime(&clib_time));

	return 0;
}
