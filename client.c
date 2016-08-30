#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 4096

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	if (argc != 3) 
		printf("usage: a.out <IPaddress> <ServerPort>\n");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket error\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_ption error for %s\n", argv[1]);
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		printf("connect error\n");
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
			printf("fputs error\n");
	}
	if (n < 0)
		printf("read error\n");
	return 0;
}
