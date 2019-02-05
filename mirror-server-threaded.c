/* Simple server listening on port 5000 - threaded version */
/* connect with telnet or nc, send string */
/* Server answers with string with characters in reverse order */
/* build with -lpthread */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define BUFSIZE 1000

void* mirror(void* arg)
{
    int clientfd = *(int *)arg;
    char inbuffer[BUFSIZE];
    char outbuffer[BUFSIZE];

	int count = read(clientfd, inbuffer, sizeof(inbuffer));
	for (int n = 0; n < count; n++)
		outbuffer[n] = inbuffer[count-1-n];

	write(clientfd, outbuffer, count);
	close(clientfd);
    return arg;
}

int main()
{
	int server_socket, rec_socket;
	unsigned int len;
	struct sockaddr_in serverinfo, clientinfo;

	unsigned short int port = 5000;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	serverinfo.sin_family = AF_INET;
	serverinfo.sin_addr.s_addr = htonl(INADDR_ANY);
	serverinfo.sin_port = htons(port);

	if (bind(server_socket, (struct sockaddr *)&serverinfo, sizeof(serverinfo)) != 0) {
        perror("Error ");
        return 1;
    }
	listen(server_socket, 3);

	while(1) {
        pthread_t child;

        printf("Server waiting...\n");
		rec_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &len);
        printf("Connected from %s:%d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));

        if (pthread_create(&child, NULL, mirror, &rec_socket) != 0) {
			perror("Error ");
			return 1;
		}
    	else
        	pthread_detach(child);
		
	}	
}




     

