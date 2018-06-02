/*
 *	author	:	Gu-hwan Bae
 *	date	:	May 29, 2018
 */

/* Create a child process using vfork() sys-call.  
   vfork() doesn't copy parent's memory to child's. 
   And Child process execute Shell command with execvp(). */

#include <unistd.h>
#include <sys/types.h>	/*  pid_t vfork(), 
							int execvp(const char* file, char *const argv[]) */

#include <stdio.h>
#include <stdlib.h>

void parse_sh_argv(const int argc, char* argv[], char* sh_argv[]);
void show_sh_argv(char* sh_argv[]);

void vfork_and_exec(char* sh_argv[]);

int main(int argc, char* argv[]) 
{
	if(argc < 2) {
		printf("Usage : %s bin options ...\n", argv[0]);
		return -1;
	}
	
	char* sh_argv[64];
	parse_sh_argv(argc, argv, sh_argv);

	show_sh_argv(sh_argv);

	vfork_and_exec(sh_argv);
	
	return 0;
}

void show_sh_argv(char* sh_argv[]) {
	printf("Shell command : ");
	while(*sh_argv) {
		printf("%s  ", *sh_argv);
		++sh_argv;
	}
	printf("\n");
}

void parse_sh_argv(const int argc, char* argv[], char* sh_argv[]) {
	const int sh_argc = argc - 1;
	int i;
	for(i = 0; i < sh_argc; ++i) {
		sh_argv[i] = argv[i+1];
	}
	/* exevpl()가 argc를 받지 않으므로 끝을 나타내는 NULL terminator가 필요하다. */
	sh_argv[sh_argc] = NULL; /* NULL terminator */
}

void vfork_and_exec(char* argv[]) {
	pid_t pid;
	if((pid = vfork()) < 0)
	{
		perror("vfork()");
	}
	
	if(pid == 0)
	{
		/* vfork()로 생성된 Child는 Parent의 data, stack segment를 복사하지 않는다. 
		   따라서 global, local var을 변경하면 Parent의 var value가 바뀐다. */
		
		/* exec()으로 Child process의 text segent를 바꾼다. */
		/* execvp()는 exec()의 GNU extension이다. */
		/* Child의 text segemnt를 sh binary로 변경. */
		/* execvp()는 POSIX 표준이 아니고, 
		   보안문제도 있으므로 system()이나 다른 대안을 사용한다. */
		printf("In child process : ");
		execvp(argv[0], argv);
		/* Child가 return or exit()를 호출하면 
		   Parent의 stack도 비워지므로 _exit()를 호출한다. */
		_exit(0);
	}
	else
	{
		sleep(1);
	}
}
