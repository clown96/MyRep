

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sigchild(int sig) {
	printf("catch you\n");
}

int main() {
	int pid;
	
	signal(SIGCHLD,sigchild);

	if((pid = fork())==0) {
		printf("This is child p\n");
		exit(0);
	}
	wait(NULL);

	printf("This is parent\n");
	exit(0);
}
