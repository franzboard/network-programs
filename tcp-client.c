/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Headerfiles für UNIX/Linux */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3333
#define MAXBUF 1024

// error handling
static void error_exit(char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
    exit(EXIT_FAILURE);
}

int main( int argc, char *argv[]) {
    struct sockaddr_in server;
    struct hostent *host_info;
    unsigned long addr;
    int sock;
    char buffer[MAXBUF];

    // tcp-client 127.0.0.1
    if (argc < 2)
        error_exit("usage: tcp-client server-ip");

    // create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0 )) < 0)
        error_exit( "could not create socket");

    // argv[1] IP address or hostname
    memset( &server, 0, sizeof (server));
    if ((addr = inet_addr( argv[1])) != INADDR_NONE) {      
	// IP
        memcpy( (char *)&server.sin_addr, &addr, sizeof(addr));
    }
    else {
	// convert hostname to IP
        host_info = gethostbyname(argv[1]);
        if (NULL == host_info)
            error_exit("unknown host");
        // IP
        memcpy( (char *)&server.sin_addr,
                host_info->h_addr, host_info->h_length );
    }
    server.sin_family = AF_INET; // IP v4
    server.sin_port = htons( PORT );

    if(connect(sock,(struct sockaddr*)&server,sizeof(server)) <0)
        error_exit("cannot connect server");


    for(;;) {
	bzero(buffer, sizeof(buffer));
    	printf("> ");
    	scanf("%s", buffer);

        // send string
        if (send(sock, buffer, sizeof(buffer), 0) != sizeof(buffer))
        	error_exit("could not send all bytes");

        // receive string
        if (!recv(sock, buffer, MAXBUF, 0)) break; 
        printf("< %s\n", buffer);

    }

    // close connection
   close(sock);
   printf("Bye!\n");
   return EXIT_SUCCESS;
}
