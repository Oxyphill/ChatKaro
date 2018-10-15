#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 
#define PORT 8888
  
int main(int argc, char const *argv[])
{
     char buff[1024];
     int size = 1024;
     int i,num;
     memset(buff,'\0',size);
     printf("Please enter your name to beacome online\n");
     scanf("%s",buff);
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , buff , strlen(buff) , 0 );
    printf("Hello %s .. hold on making you online \n",buff);
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
/*
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
*/
   
    while(1) {
        printf("Client: Enter Data for Server:\n");
        fgets(buffer,1024,stdin);
        if ((send(sock,buffer, strlen(buffer),0))== -1) {
                fprintf(stderr, "Failure Sending Message\n");
                close(sock);
                exit(1);
        }
        else {
                printf("Client:Message being sent: %s\n",buffer);
                num = recv(sock, buffer, sizeof(buffer),0);
                if ( num <= 0 )
                {
                        printf("Either Connection Closed or Error\n");
                        //Break from the While
                        break;
                }

                buff[num] = '\0';
                printf("Client:Message Received From Server -  %s\n",buffer);
           }
    }
    close(sock);









    return 0;
}
