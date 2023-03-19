// General Includes 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

// Socket Includes 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define MYPORT "3490"
#define BACKLOG 10  

int main(int argc, char* argv[]) {
    int status, sockfd, newfd; 
    struct addrinfo hints, *res;
    struct sockaddr_storage their_addr; 
    socklen_t addr_size;  

    // set up hints addrinfo 
    memset(&hints, 0, sizeof(hints)); 
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE; 

    // prepare the sockaddr through getaddrinfo 
    if((status = getaddrinfo(NULL, MYPORT,&hints,&res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); 
        return 1; 
    }

    // create a socket, bind it to a port, and have it listen 
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 
    bind(sockfd, res->ai_addr, res->ai_addrlen); 
    listen(sockfd, BACKLOG); 


    freeaddrinfo(res); 

    return 0; 
}