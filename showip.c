#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>  
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main(int argc, char* argv[]) {
    int status, sockfd;
    char ipstr[INET6_ADDRSTRLEN]; 
    struct addrinfo hints, *res; 

    if(argc != 2) {
        fprintf(stderr, "usage: showip hostname\n"); 
        return 1; 
    }

    memset(&hints, 0, sizeof(hints));   
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE; 

    if((status = getaddrinfo(argv[1], "4500", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); 
        return 2; 
    }

    for(struct addrinfo* p = res; p != NULL; p = p->ai_next) {
        char *ipver; 
        void *addr; 
        if(p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in*)p->ai_addr; 
            addr = &(ipv4->sin_addr); 
            ipver = "IPv4"; 
        }
        else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)p->ai_addr; 
            addr = &(ipv6->sin6_addr); 
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr)); 
        printf("    %s: %s\n", ipver, ipstr); 
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 

    connect(sockfd, res->ai_addr, res->ai_addrlen); 

    freeaddrinfo(res); 

    return 0; 
}