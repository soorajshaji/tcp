#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>

void main() 
{
struct sockaddr_in serverAddr, clientAddr;
int len, clientSocket,clientNumber=0, serverSocket=socket(AF_INET, SOCK_STREAM, 0);
char data[1024];
pid_t childpid;

serverAddr.sin_family = AF_INET;
serverAddr.sin_addr.s_addr = INADDR_ANY;
serverAddr.sin_port = 4040;

bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

printf("Waiting for a connection...\n");
listen(serverSocket, 5);

while(1) 
{ 
    len = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &len);
    printf("Connection accepted!... Total no. of Clients:%d\n",++clientNumber);
    
    if ((childpid = fork()) == 0) 
    { 
        close(serverSocket);
        while (1) 
        {
            recv(clientSocket, data, 1024, 0);
            printf("\nReceived data from client %d: %s", clientNumber, data);
            send(clientSocket, data, 1024, 0);
            printf("\nSenting data to client %d: %s\n", clientNumber, data);
        } 

    } 
    close(clientSocket);
}
}
