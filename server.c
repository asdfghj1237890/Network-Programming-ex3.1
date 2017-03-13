#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(int argc, char ** argv) 
{
	int listenfd, connfd;
	socklen_t clilen = sizeof(struct sockaddr_in);
	struct sockaddr_in servaddr, cliaddr;
	char buf[MAXLINE + 1], *ip;
	time_t ticks;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if( listenfd < 0 ) {
          perror("Create socket failed.");
          exit(1);
        }
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(10127);
	
	if( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
          perror("Bind socket failed.");
          exit(1);
        }
	
	listen(listenfd, 1024);
	while(1){
		puts("prepared to accept");
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr,(socklen_t*)&clilen);
		printf("connection from %s, port %d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));
		close(connfd);
	}
	return 0;
}

