#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "communication.h"
#include "drive.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}
int idnr = 1337;
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    struct message msg;

    while(read(sockfd, &msg, sizeof(struct message))) {
        if(msg.type == T_DIRECTION) {
            wiringPiSetup();
            setup();
            printf("got direction:%d\n", msg.arg1);
            if(msg.arg1 == FORWARD) {
                printf("forward bitch!!!\n");
                forward(0);
            } else if(msg.arg1 == REVERSE) {
                reverse(0);
            } else if(msg.arg1 == RIGHT) {
                right(400);
            } else if(msg.arg1 == LEFT) {
                left(400);
            } else if(msg.arg1 == FORWARD_RIGHT) {
                forward_right(400);
            } else if(msg.arg1 == FORWARD_LEFT) {
                forward_left(400);
            } else if(msg.arg1 == OFF) {
                off();
            }
            struct message ack = {T_ACK,0,0,0,0,msg.id};
            write(sockfd, &ack, sizeof(struct message));
            printf("sent ack\n");
        } else if(msg.type == T_GO_SCAN) {
            printf("got go scan\n");
            FILE *fp;
            fp = popen("sudo python mapping.py", "r");
            char reading[255];
            int number = 0;
            while (fgets(reading, sizeof(reading), fp)) {
                if(startsWith("sejdemedjikwurt ", reading)) {
                    int ireading = atoi(reading + 16);
                    printf("reading:%d\n", ireading);
                    struct message result = {T_SCAN_RESULT, ireading, number, 0, 0, idnr++};
                    write(sockfd, &result, sizeof(struct message));
                    number++;
                }
            }
            struct message done = {T_SCAN_DONE, 0, 0, 0, 0, idnr++}; 
            write(sockfd, &done, sizeof(struct message));
            printf("sent done\n");
            pclose(fp);
        }
    }
    close(sockfd);
    return 0;
}
