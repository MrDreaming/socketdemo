// server.cpp (运行到开发板中 192.168.8.41)
#include "stdafx.h"
#include "UdpServer.h"
#include <windows.h>
#include <commctrl.h>
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#pragma comment(lib,"ws2.lib") //windows 用 ws2_32.lib
#define BUFFER_SIZE 1024


static int StartUdpServer();

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    StartUdpServer();
    return 0;
}

static int StartUdpServer(){
    WSADATA WSAData;
    char receBuf[BUFFER_SIZE];
    char Response[512];
    printf("\n\n%s(%s:%d)...\n\n", __FILE__, __FUNCTION__, __LINE__);
    if(WSAStartup(MAKEWORD(2,2),&WSAData)!=0){
    printf("初始化失败");
    exit(1);
    }
    SOCKET sockServer=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockServer == INVALID_SOCKET)
    {
        printf("Failed socket() \n");
        return 0;
    }
    SOCKADDR_IN addr_Server; //服务器的地址等信息
    addr_Server.sin_family=AF_INET;
    addr_Server.sin_port=htons(4567);
    addr_Server.sin_addr.S_un.S_addr=INADDR_ANY;
    //服务器与本地地址绑定
    if(bind(sockServer,(SOCKADDR*)&addr_Server,sizeof(addr_Server))==SOCKET_ERROR ){
            printf("Failed socket() %d \n", WSAGetLastError());
             return 0;
    }
     SOCKADDR_IN addr_Clt;   

    int fromlen = sizeof(SOCKADDR);  
    while(true){  
        int last=  recvfrom(sockServer, receBuf, 1024, 0,  (SOCKADDR*) &addr_Clt, &fromlen);  
        if(last>0){  
           receBuf[last]='\0';// 防止乱码
           if(strcmp(receBuf,"bye")==0){
                  printf("Good bye \n");
                  sprintf(Response, "%s", receBuf);
                  sendto(sockServer,Response, strlen(Response), 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR));  
                  closesocket(sockServer);  
                  return 0;
           }else{
               printf("recv(%s) : %s\n", inet_ntoa(addr_Clt.sin_addr), receBuf);
           }
       }
        sprintf(Response, "#%s#", receBuf);
        sendto(sockServer,Response, strlen(Response), 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR));  
    }  
    closesocket(sockServer);  
    WSACleanup();
     return 0;
}