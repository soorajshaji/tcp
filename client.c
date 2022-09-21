#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>

void main() 
{
struct sockaddr_in serverAddr, clientAddr;
char data[1024];
int sockfd = socket(AF_INET,SOCK_STREAM, 0);

serverAddr.sin_family = AF_INET;
serverAddr.sin_addr.s_addr = INADDR_ANY;
serverAddr.sin_port = 4040;

connect(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
printf("Connected to the server...\n");

while (1) 
{
    printf("Enter your message: ");
    scanf("%s",data);
    send(sockfd, data, 1024, 0);
    recv(sockfd, data, 1024, 0);
    printf("Received from server:%s\n",data); 
}

}
