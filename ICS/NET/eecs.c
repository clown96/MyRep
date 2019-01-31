#include "csapp.h"

int main(int argc, char **argv) {
	int connfd,n;
	int filefd;
	char buf[MAXLINE];
	rio_t rio;
	
	filefd = open("eecs_code.txt",O_RDWR|O_CREAT|O_TRUNC,DEF_MODE);
	if(filefd < 0) {
		fprintf(stderr,"Open error: %s\n",strerror(errno));
		exit(0);
	}

	connfd = open_clientfd("eecs.pku.edu.cn","80");
	if(connfd < 0) {
		fprintf(stderr,"Open_clientfd error: %s\n",strerror(errno));
		exit(0);
	}
	
	sprintf(buf,"GET / HTTP/1.1\r\n");
	strcat(buf,"Host: eecs.pku.edu.cn\r\n");
	strcat(buf,"Connection: close\r\n");
	strcat(buf,"\r\n");
	rio_readinitb(&rio, connfd);
	if(rio_writen(connfd,buf,sizeof(buf)) < 0 ) {
		fprintf(stderr,"Rio_writen error: %s\n",strerror(errno));
		exit(0);
	}
	while(1) {
		rio_readlineb(&rio,buf,MAXLINE);
		if(strcmp(buf,"\r\n") == 0) break;
	}
	while(1) {
		n = rio_readnb(&rio,buf,MAXLINE);
		if(n < 0) {
			fprintf(stderr, "Rio_readnb error: %s\n",strerror(errno));
			exit(0);
		}
		if(n == 0) break;
		rio_writen(filefd,buf,n);
	}
	close(filefd);
	close(connfd);
	execve("getObj",argv,environ);
}
