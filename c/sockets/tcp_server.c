/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     char buffer[256];

     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
     {
        error("ERROR opening socket");
     }

     struct sockaddr_in serv_addr;
     int portno = 42000;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     socklen_t socket_size = sizeof(serv_addr);
     int bind_err = bind(sockfd, (struct sockaddr *) &serv_addr, socket_size);
     if (bind_err < 0)
     {
       error("ERROR on binding");
     }

     struct sockaddr_in cli_addr;
     listen(sockfd,5);
     int connectionfd = accept(
       sockfd, (struct sockaddr *) &cli_addr, &socket_size);
     if (connectionfd < 0)
     {
       error("ERROR on accept");
     }
     int n = read(connectionfd, buffer, 255);
     if (n < 0)
     {
       error("ERROR reading from socket");
     }
     printf("Here is the message: %s\n", buffer);
     n = write(connectionfd, "I got your message", 18);
     if (n < 0)
     {
       error("ERROR writing to socket");
     }
     close(connectionfd);
     close(sockfd);
     return 0;
}
