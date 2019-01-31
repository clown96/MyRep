#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
	int i;
	char *p;
	printf("Command-ine arguments:\n");
	for(i = 0; i < argc; i++)
		printf("argv[%2d]: %s\r",i,argv[i]);
	printf("Environment variables:\n");
	for(i = 0; ; i++) {
		p = envp[i];
		if(p == NULL) break;
		printf("envp[%2d]: %s\n",i,p);
	}
	return 0;
}
