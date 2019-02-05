/* Simple http server, listens on all interfaces, port 80 */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket, rec_socket;
    unsigned int len;
    struct sockaddr_in serverinfo, clientinfo;
    char rec_buf[1000];
    char send_buf[] = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Hi People!</h1></body></html>";

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
        printf("Server waiting...\n");
        rec_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &len);
        printf("Connected from %s:%d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));

        read(rec_socket, rec_buf, sizeof(rec_buf));

        write(rec_socket, send_buf, sizeof(send_buf));
        close(rec_socket);
    } 

}
