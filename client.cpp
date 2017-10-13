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

    bzero(&client_addres, sizeof(client_addres));
    client_addres.sin_family = AF_INET;
    client_addres.sin_port = htons(0);
    client_addres.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(socket_file_descriptor,(struct sockaddr*) &client_addres, sizeof(client_addres)) < 0){
        cout << "Socket not binded" << endl;
        close(socket_file_descriptor);
        return 1;
    }

    bzero(&server_addres, sizeof(server_addres));
    server_addres.sin_family = AF_INET;
    server_addres.sin_port = htons(SERVER_PORT);
    if(inet_aton(SERVER_ADDRES,&server_addres.sin_addr) == 0){
        cout << "Invalid IP" << endl;
        close(socket_file_descriptor);
        return 1;
    }

    char request[128];

    char c = NULL; int i = 0;
    cout << "Input request: " << endl;
    while( (c = getchar()) != '\n'){
        request[i++] = c;
    }
    request[i] = '\0';
    
    if(sendto(socket_file_descriptor, request, strlen(request), 0, (struct sockaddr*) &server_addres, sizeof(server_addres)) < 0){
        cout << "Error with request" << endl;
        close(socket_file_descriptor);
        return 1;
    }

    char response[128];
    bzero(response,128);
    if(recvfrom(socket_file_descriptor,response,128, 0, NULL, NULL) < 0){
        cout << "Error with response" << endl;
        close(socket_file_descriptor);
        return 1;
    }

    cout << "Response: "<< response << endl;
    close(socket_file_descriptor);
    return 0;
}