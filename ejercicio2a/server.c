/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     double potencia = atof(argv[2]);
     int size = pow(10,potencia);
     char *buffer = malloc(size * sizeof(char) + sizeof(char));
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     fprintf(stderr,"SERVIDOR\n");
     if (argc < 3) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));

	 portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
	 
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
			  
     listen(sockfd,5);
	 
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
				 
	 if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,size);

     n = read(newsockfd,buffer,size);
     int totalBytesRead = n;
     while (totalBytesRead < size){
      n = read(newsockfd,buffer + totalBytesRead, size - totalBytesRead);
      if (n < 0){
         error("ERROR reading from socket");
         break;
      } else if (n == 0){
        break;
      }
      totalBytesRead += n;
     }
     
     printf("Here is the message: %s\n",buffer);
	 
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     return 0; 
}
