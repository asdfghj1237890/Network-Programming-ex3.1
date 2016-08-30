#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAXLINE 4096

int main(int argc, char ** argv) 
{
	int listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;
	char buf[MAXLINE + 1], *ip;
	time_t ticks;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	servaddr.sin_port = htons(13);
	
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	listen(listenfd, 1024);
	
	for ( ; ; ) {
		puts("prepared to accept");
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		ip = inet_ntoa(cliaddr.sin_addr);
		printf("connection from %s, port %d\n", ip, cliaddr.sin_port);
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));
		close(connfd);
	}
	return 0;
}

