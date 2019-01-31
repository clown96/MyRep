#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
static int url2uri(char *url, char *host, char *uri)
{
	char *p;
	p = strchr(url,'/');
	while(*p == '/') p++;
	strcpy(host,p);
	p = strchr(host,'/');
	strcpy(uri,p);
	*p = '\0';
	return 0;
}
int main(int argc, char **argv) {
	char url[100];
	char host[100];
	char uri[100];
	scanf("%s",url);
	url2uri(url,host,uri);
	printf("%s\n",host);
	printf("%s\n",uri);
	return 0;
}
