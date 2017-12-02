#include <sys/types.h>    
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>    
#include <time.h>    
#include <string.h>    
#include <stdio.h>    
#include <unistd.h>    
#include <stdlib.h>    
#include<errno.h>
#define TARGET_PORT	6666    
#define TARGET_IP "192.168.251.170"    
int main(int argc, char *argv[])    
{    
    struct sockaddr_in addr;    
    int sockfd, cnt;    
    struct ip_mreq mreq;    
    char *sendline=(char*)"hello";    
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0)) < 0)     
    {    
        perror("socket");    
        exit(1);    
    }    
    memset(&addr,0,sizeof(addr));    
    addr.sin_family=AF_INET;    
    addr.sin_addr.s_addr=inet_addr(TARGET_IP);    
    addr.sin_port=htons(TARGET_PORT);    
	for(int i=0; i<5; i++){
		printf("send : %s\n", sendline);
		if(sendto(sockfd,sendline, strlen(sendline), 0, (struct sockaddr *) &addr, sizeof(addr)) < 0) {    
			printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
			exit(0);
		}
		sleep(1);
	}
	close(sockfd);
    return 0;    
}    