
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
extern char **environ;
int main() {
	int pid;
	char *argv[5];
	argv[0] = "/bin/ps";
		

	pid = fork();
	if(pid == 0) {
		if(execve("/bin/ps",argv,environ) < 0) {
			printf("execve error\n");
			exit(1);
		}
	}
	waitpid(-1,NULL,0);
	printf("parent return\n");
	exit(0);
}
