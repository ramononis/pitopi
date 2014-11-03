/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "communication.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int idnr = 13337;
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     struct message msg = {T_GO_SCAN, 0, 0, 0, 0, idnr++};
     write(newsockfd, &msg, sizeof(struct message));
     printf("sent go scan\n");
     while(read(newsockfd, &msg, sizeof(struct message))) {
         if(msg.type == T_SCAN_RESULT) {
             printf("got scan result%d\n", msg.arg1);
             int number = msg.arg2;
             int reading = msg.arg1;
             printf("%d\t%d\n", number, reading);
         } else if(msg.type == T_SCAN_DONE) {
             printf("got scan done\n");
             int command;
             char input;
             printf("try to read char\n");
             while((input = fgetc(stdin))) {
                 printf("i got a char. i'm so happy\n");
                 if(input == 'w') {
                     command = FORWARD;
                     break;
                 } else if(input == 's') {
                     command = REVERSE;
                     break;
                 } else if(input == 'a') {
                     command = LEFT;
                     break;
                 } else if(input == 'd') {
                     command = RIGHT;
                     break;
                 } else if(input == 'q') {
                     command = FORWARD_LEFT;
                     break;
                 } else if(input == 'e') {
                     command = FORWARD_RIGHT;
                     break;
                 } else if(input == ' ') {
                     command = OFF;
                     break;
                 }
             }
             struct message mcommand = {T_DIRECTION, command, 0, 0, idnr++};
             printf("sent direction:%d\n",command); 
             write(newsockfd, &mcommand, sizeof(struct message));
         } else if(msg.type == T_ACK) {
             printf("got ack\n");
             struct message goscan = {T_GO_SCAN, 0, 0, 0, 0, idnr++};
             write(newsockfd, &goscan, sizeof(struct message));
         }
 
     }
     close(newsockfd);
     close(sockfd);
     return 0; 
}
