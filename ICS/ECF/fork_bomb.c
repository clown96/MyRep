
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int pid;
	int count = 0;
	

	while(1) {
		pid = fork();
		if(pid < 0) break;
		if(pid == 0) {
			exit(0);
		}
		else {
			count++;
		}
	}
	while(waitpid(-1,NULL,0)>0);
	printf("%d\n",count);
	exit(0);
}
