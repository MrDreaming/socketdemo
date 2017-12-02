#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_PORT 27350
#define MAXLINE 4096

int main(int argc, char** argv){
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
		printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
    }

    if( listen(listenfd, 10) == -1){
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
    }

	struct sockaddr_in sa;
	int len = sizeof(sa);
	int result = 0;
    while(1){
		if((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
			continue;
		}
		printf("accept success, ");
		result = getpeername(connfd, (struct sockaddr *)&sa, (socklen_t*)&len); // connfd(not listenfd)
		if(!result){
			printf( "(%s , %d)\n", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
		}else{
			printf("getpeername()=%d,  %s(errno: %d)\n", result, strerror(errno),errno);
		}
		n = recv(connfd, buff, MAXLINE, 0);
		buff[n] = '\0';
		printf("recv msg from client: %s\n", buff);
		memset(buff, 0, sizeof(buff));
		close(connfd);
    }

    close(listenfd);
}