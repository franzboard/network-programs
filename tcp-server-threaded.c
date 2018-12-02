// tcp-server-threaded.c
// compile with -lpthreads
//
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 3333
#define MAXBUF 1024

void* echo(void* arg)
{
    int clientfd = *(int *)arg;
    int bytes_read;
    char buffer[MAXBUF];
    // echo until receives "quit" from client
    for(;;) {
        bytes_read = recv(clientfd, buffer, MAXBUF, 0); 
        if (strncmp(buffer, "quit", 4) == 0) break;
        send(clientfd, buffer, bytes_read, 0); 
    }
    // close client connection
    close(clientfd);
    return arg;
}

int main(int argc, char *argv[]) {
    struct sockaddr_in server;
    int sockfd;

    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    	exit(EXIT_FAILURE);

    // Server socket address
    bzero( &server, sizeof (server)); // fill server with 0
    server.sin_family = AF_INET; // IP v4
    server.sin_addr.s_addr = htonl(INADDR_ANY); // listen on all interfaces
    server.sin_port = htons(PORT);

    // assign port number to socket
    if(bind(sockfd,(struct sockaddr*)&server, sizeof( server)) < 0)
    	exit(EXIT_FAILURE);

    // socket listens for connections
    if(listen(sockfd, 5) == -1 )
    	exit(EXIT_FAILURE);

    printf("server ready ...\n");
    // receive loop
    for (;;) {
	int clientfd;
	struct sockaddr_in client_addr;
        unsigned addrlen = sizeof(client_addr);
	pthread_t child;
	
	// wait for connect
        clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
	printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	if (pthread_create(&child, NULL, echo, &clientfd) != 0)
	    exit(EXIT_FAILURE);
	else 
	    pthread_detach(child);
	
    }
    close(sockfd);
    return EXIT_SUCCESS;
}
