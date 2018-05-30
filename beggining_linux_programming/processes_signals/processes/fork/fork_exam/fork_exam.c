/*
 *	author	:	Gu-hwan Bae
 *	date	:	May 29, 2018
 */

/* Create a child process using fork() sys-call.  */

#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>

static int g_var = 1;	/* var in data segment  */

int main() 
{
	pid_t pid;
	int var = 92;	/* var in stack segment  */

	if((pid = fork()) < 0)
	{
		perror("fork()");
	}
	
	if(pid == 0)	/* fork()가 반환한 pid == 0이면 Child process */
	{
		g_var++;
		var++;
		printf("Child process(%d) from Parent process(%d)\n", getpid(), getppid());
	}
	else	/* Parent는 fork() 반환값으로 Child의 pid를 받는다. */
	{
		printf("Parent process(%d) and Child's pid = %d\n", getpid(), pid);
		sleep(1);	/* Parent가 먼저 종료되면 Child는 Orphaned process가 된다.
					   이 경우 system이 init process의 Child로 만든다. */
	}
	
	/* Child는 Parent의 text segment를 공유하고 data, stack segment는 복사한다.
	   즉 Child가 global, local var을 변경해도 Parent의 var value를 바꾸지 않는다. */
	printf("pid = %d, g_var = %d, var = %d\n", getpid(), g_var, var);

	return 0;
}
