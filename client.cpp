//
// Created by pacman29 on 12.10.17.
//

#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <zconf.h>
#include <netdb.h>
#include "arpa/inet.h"
#include "sys/socket.h"
#include "sys/types.h"

#define SERVER_PORT 8080
#define SERVER_ADDRES "localhost"

#define BUFFER 128

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("ERROR opening socket");
    server = gethostbyname(SERVER_ADDRES);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);

    serv_addr.sin_port = htons(SERVER_PORT);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");



    char request[128];

    char c = NULL; int i = 0;
    cout << "Input row index: " << endl;
    while( (c = getchar()) != '\n'){
        request[i++] = c;
    }
    request[i] = '\0';


    if(write(sockfd, request, strlen(request)) < 0)
        error("ERROR writing to socket");

    sleep(2);

    char response[128];
    bzero(response,128);
    read(sockfd,response,BUFFER);

    cout << response << endl;

    close(sockfd);
    return 0;
}