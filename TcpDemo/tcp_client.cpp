#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TARGET_PORT	6666    
#define TARGET_IP "192.168.251.170"   
#define MAXLINE 4096

int main(int argc, char** argv){
    int sockfd, n;
    char recvline[4096];
	char sendline[4096];
    struct sockaddr_in servaddr;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
		exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(TARGET_PORT);
    if( inet_pton(AF_INET, TARGET_IP, &servaddr.sin_addr) <= 0){
		exit(0);
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
    }
    printf("send msg to server: \n");
	strcpy(sendline, "Hello\n");
	for(int i=0; i<5; i++){
		printf("send : %s\n", sendline);
		if( send(sockfd, sendline, strlen(sendline), 0) < 0){
			printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
			exit(0);
		}
		sleep(1);
	}
    close(sockfd);
    exit(0);
}