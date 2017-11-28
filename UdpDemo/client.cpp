// client.cpp (Windows7 Computer : 192.168.8.170)
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define BUFFER_SIZE  1024   

int main(){
    SOCKET sock_Client;
    WSADATA WSAData;
    char  receBuf[BUFFER_SIZE];
    char  sendBuf[BUFFER_SIZE];
    int sendResult;

    if(WSAStartup(MAKEWORD(2,2),&WSAData)!=0){
        printf("≥ı ºªØ ß∞‹!");
        return -1;
    } 
    sock_Client=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    SOCKADDR_IN addr_server;
    addr_server.sin_family=AF_INET;
    addr_server.sin_port=htons(4567);
    addr_server.sin_addr.S_un.S_addr=inet_addr("192.168.8.41"); 
    SOCKADDR_IN sock;
    int len=sizeof(sock);
    while(true){
        cout<<"Enter data to send : ";
        cin>>sendBuf;  
        sendResult = sendto(sock_Client,sendBuf,strlen(sendBuf),0,(SOCKADDR*)&addr_server,sizeof(SOCKADDR));
        printf("sendResult : %d\n", sendResult);
        int last=recvfrom(sock_Client,receBuf,BUFFER_SIZE,0,(SOCKADDR*)&sock,&len);
        if(last>0){
            receBuf[last]='\0'; 
            if(strcmp(receBuf,"bye")==0){
                    printf("good bye\n");
                   closesocket(sock_Client);
                    break;
            }else{
                printf("rec : %s\n", receBuf);
            }
        }else{
            printf("failed %d\n", last);
        }
    }
    closesocket(sock_Client);
    printf("the end\n");
    getchar();
    WSACleanup();
    return 0;
}