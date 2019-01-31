
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int pid;
	int x = 1;

	pid = fork();
	if(pid == 0) {
		printf("child:x=%d\n",++x);
		exit(0);
	}
	waitpid(pid,NULL,WNOHANG);
	printf("parent:x=%d\n",--x);
	exit(0);
}
