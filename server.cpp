//
// Created by pacman29 on 12.10.17.
//

#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <zconf.h>
#include <unordered_map>
#include <sstream>
#include "arpa/inet.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "FileKeeper.h"
#include "IpConverter.h"

#define SERVER_PORT 8080
#define SERVER_ADDRES "127.0.0.1"
#define FILE_NAME "../ips.txt"
#define BUFFER 128
using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd;
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0)
    error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    printf("server: got connection from %s port %d\n",
           inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    FileKeeper fileKeeper(FILE_NAME);

        char buffer[BUFFER];
        bzero(buffer,BUFFER);
        if(read(newsockfd,buffer,BUFFER-1) < 0){
            error("ERROR reading from socket");
        }

        unsigned int index = 0;
        sscanf(buffer,"%d",&index);
        try {
            unordered_map<string,string> map = IpConverter::converter(fileKeeper.getLine(index));
            string response = "";
            for (std::pair<string,string> p : map) {
                stringstream ss;
                ss << p.first << ":  " << p.second << "\n";
                response.append(ss.str());
            }

            write(newsockfd,response.data(),BUFFER);
        } catch (std::exception& e){
            write(newsockfd,"ERROR",BUFFER);
        }
    close(newsockfd);
    close(sockfd);
}