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

int main(int argc, char* argv[]) {
    int status; 
    char ipstr[INET6_ADDRSTRLEN]; 
    struct addrinfo hints, *res; 

    memset(&hints, 0, sizeof(hints)); 
    hints.ai_family = AF_UNSPEC; 
    hints.ai_flags = AF_PASSIVE; 
    hints.ai_socktype = SOCK_STREAM; 

    if((status = getaddrinfo(,,&hints,&res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); 
        return 1; 
    }

    for(struct addrinfo* p = res; p != NULL; p = p->ai_next) {
        void* addr; 
        char* ipver; 
        if(p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_family); 
            ipver = "IPv4"; 
        }
        else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_family); 
            ipver = "IPv6"; 
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr)); 
    }

    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 

    

    return 0; 
}