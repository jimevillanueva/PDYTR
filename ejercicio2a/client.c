#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct timeval start, end;
    double potencia = atof(argv[3]);
    int size = pow(10,potencia);
    fprintf(stderr,"CLIENTE\n");
    char *buffer = malloc(size * sizeof(char) + sizeof(char));
    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
	
    portno = atoi(argv[2]);
	  sleep(10);
	
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    if (sockfd < 0) 
        error("ERROR opening socket");
	
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
	
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
     serv_addr.sin_port = htons(portno);
 
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    
    bzero(buffer,size);
    for(int i=0; i < size; i++){
      buffer[i]='b'; 
    }

  gettimeofday(&start, NULL);
	n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,size);
	
	n = read(sockfd,buffer,size -1);
    if (n < 0) 
         error("ERROR reading from socket");
  
  gettimeofday(&end, NULL);
  long seconds = (end.tv_sec - start.tv_sec);
  long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
  int p = potencia;
  printf("Cantidad caracteres: 10 a la  %d. El tiempo fue: %ld segundos y %ld microsegundos\n", p, seconds, micros);
  return 0;
}
