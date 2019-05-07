/* Connect to a webserver on port 80 and print answer on console */
/* Call: ./connect-http 127.0.0.1 */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define HTTP_PORT 80
#define BUFSIZE 20000

int main(int argc, char *argv[])
{
    int socket_fd;
    int len;
    struct sockaddr_in adressinfo;
    int result;
    char cmd[] = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char answer[BUFSIZE];
    int n;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    adressinfo.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1],&adressinfo.sin_addr.s_addr);
    adressinfo.sin_port = htons(HTTP_PORT);
    len = sizeof(adressinfo);
    result = connect(socket_fd, (struct sockaddr *)&adressinfo, len);
    if (result != 0) {
        printf("connect failed!\n");
    }
    else {
        printf("----- received: -----\n");
        write(socket_fd, cmd, sizeof(cmd));        
        n = read(socket_fd, answer, sizeof(answer)-1);        
        answer[n] = '\0';
        printf("%s\n", answer);
    }

    close(socket_fd);
    return(0);
}
