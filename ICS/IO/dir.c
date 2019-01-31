#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *f;
	int dir;
	mkdir("a",0755);
	if(chdir("a") < 0) {
		fprintf(stderr,"chdir error\n");
		exit(0);
	}
	if((f = fopen("hello","w+")) == NULL) {
		fprintf(stderr, "fopen error\n");
		exit(0);
	}
	fputc('w',f);
	fclose(f);
}
