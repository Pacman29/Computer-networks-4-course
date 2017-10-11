//
// Created by pacman29 on 11.10.17.
//

#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <zconf.h>
#include "arpa/inet.h"
#include "sys/socket.h"
#include "sys/types.h"

#define SERVER_PORT 8080
#define SERVER_ADDRES "127.0.0.1"

using namespace std;

int main() {
    int socket_file_descriptor;
    if((socket_file_descriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        cout << "Socket not created" << endl;
        return 1;
    }

    struct sockaddr_in server_addres, client_addres;

    bzero(&server_addres, sizeof(server_addres));
    server_addres.sin_family = AF_INET;
    server_addres.sin_port = htons(SERVER_PORT);
    server_addres.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(socket_file_descriptor,(struct sockaddr*) &server_addres, sizeof(server_addres)) < 0){
        cout << "Socket not binded" << endl;
        close(socket_file_descriptor);
        return 1;
    }

    while(true){
        char request[128];
        int client = sizeof(client_addres);
        if(recvfrom(socket_file_descriptor, request, 128, 0, (struct sockaddr*) &client_addres,
                    reinterpret_cast<socklen_t *>(&client)) < 0){
            cout << "Error with request" << endl;
            close(socket_file_descriptor);
            return 1;
        }
        
        cout << "Request: " << request << endl;
        
        if(sendto(socket_file_descriptor, request, strlen(request), 0, (struct sockaddr*) &client_addres, client) < 0){
            cout << "Error with response" << endl;
            close(socket_file_descriptor);
            return 1;
        }
    }
    return 0;
}