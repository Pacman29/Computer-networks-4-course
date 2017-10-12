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
#define TEXT "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis consequat id ante id tincidunt. Phasellus sit amet ante felis. Curabitur mattis vestibulum nulla id consectetur. Cras semper lacus nulla, sit amet mollis dui vehicula nec. Donec tempus velit tortor, sit amet eleifend mi cursus at. Duis viverra, dolor et volutpat fringilla, eros metus fringilla lacus, quis ornare leo elit nec leo. Vestibulum sapien eros, tempor vel semper ut, laoreet et lacus.\n\nInterdum et malesuada fames ac ante ipsum primis in faucibus. Cras eget porttitor lectus. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Cras quis tincidunt enim. Maecenas consequat neque ac elit eleifend scelerisque. Mauris quis consectetur tellus. Vestibulum tincidunt quis felis vel euismod. Phasellus non magna faucibus, luctus urna in, rhoncus urna."

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

    size_t size = strlen(TEXT);
    char buf[BUFFER];
    for(unsigned int i = 0; i < size; i+= BUFFER-1) {
        bzero(buf,BUFFER);
        for(unsigned int j = 0; (j<BUFFER-1) && (j<size); j++) {
            buf[j] = TEXT[i+j];
        }
        if(write(sockfd, buf, strlen(buf)) < 0) {
            error("ERROR writing to socket");
        }
        sleep(1);
    }
    close(sockfd);
    return 0;
}