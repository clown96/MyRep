#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
	void *rsp = main;
	printf("0x%x\n",rsp);
	return 0;
}
