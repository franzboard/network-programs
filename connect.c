/* Connect to a server, aka portscanner */
/* call: ./connect 127.0.0.1 5000 */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
   int socket_fd;
   int len;
   struct sockaddr_in adressinfo;
   int result;

   socket_fd = socket(AF_INET, SOCK_STREAM, 0);
   adressinfo.sin_family = AF_INET;
   inet_pton(AF_INET, argv[1],&adressinfo.sin_addr.s_addr);
   adressinfo.sin_port = htons(atoi(argv[2]));
   len = sizeof(adressinfo);
   result = connect(socket_fd, (struct sockaddr *)&adressinfo, len);
   if (result == 0)
      printf("port open\n");
   else
      printf("port closed\n");
   close(socket_fd);
   return(0);
}
