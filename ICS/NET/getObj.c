#include "csapp.h"

void GetObj(char *s);

int main()
{
	FILE *f;
	char buf[MAXLINE];
	char Obj[MAXLINE];
	char *p,*q;
	int n;

	if( (f = fopen("eecs_code.txt","r")) == NULL) {
		fprintf(stderr,"fopen error\n");
		exit(0);
	}
	mkdir("Objects",0755);
	if(chdir("Objects") < 0) {
		fprintf(stderr,"chdir error\n");
		exit(0);
	}
	while(!feof(f)) {
		fgets(buf,MAXLINE,f);
		p = buf;
		while((p = strstr(p,"href="))) {
			p = strchr(p,'\"');
			strcpy(Obj,p+1);
			q = strchr(Obj,'\"');
			*q = '\0';
			printf("Tring to get object: %s\n",Obj);
			GetObj(Obj);
		}
		p = buf;
		while((p = strstr(p,"src="))) {
			p = strchr(p,'\"');
			strcpy(Obj,p+1);
			q = strchr(Obj,'\"');
			*q = '\0';
			printf("Tring to get object: %s\n",Obj);
			GetObj(Obj);
		}
	}
	fclose(f);
}

void GetObj(char *s)
{
	char host[MAXLINE],uri[MAXLINE],name[MAXLINE];
	char buf[MAXLINE];
	char header[MAXLINE];
	int fd,filefd,n;
	static int idx = 1;
	rio_t rio;
	char *p;	
	if(s[0] == '/') {
		strcpy(host,"eecs.pku.edu.cn");
		strcpy(uri,s);
	}
	else {
		p = strstr(s,"//");
		if(p == NULL) return;
		strcpy(host,p+2);
		p = strchr(host,'/');
		if(p == NULL)
			strcpy(uri,"/");
		else {
			strcpy(uri,p);
			*p = '\0';
		}
	}
	p = strrchr(uri,'/');
	strcpy(name,p+1);
	if(strlen(name) == 0)
		sprintf(name,"obj%d.html",idx++);
	//printf("Object's name: %s\n",name);

	sprintf(buf,"GET %s HTTP/1.1\r\n",uri);
	strcpy(header,buf);
	sprintf(buf,"Host: %s\r\n",host);
	strcat(header,buf);
	strcat(header,"Connection: close\r\n");
	strcat(header,"\r\n");

	if((fd = open_clientfd(host,"80")) < 0) {
		unix_error("Open_clientfd error");
		return;
	}
	//printf("fd: %d\n",fd);

	rio_readinitb(&rio,fd);
	if(rio_writen(fd,header,sizeof(header)) < 0) {
		unix_error("Rio_writen error");
		return;
	}
	filefd = open(name,O_RDWR|O_CREAT|O_TRUNC,DEF_MODE);
	if(filefd < 0) {
		fprintf(stderr,"Open error\n");
		return;
	}
	//printf("filefd: %d\n",filefd);
	while(1) {
		rio_readlineb(&rio,buf,MAXLINE);
		if(strcmp(buf,"\r\n") == 0) break;
	}
	while(1) {
		n = rio_readnb(&rio,buf,MAXLINE);
		if(n == 0) break;
		rio_writen(filefd,buf,n);
	}
	close(fd);
	close(filefd);
}
