/************* UDP SERVER CODE *******************/
#include <ctype.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

/*
 * <server> <port> <loss probability> <random seed>
 */
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Too few args!\n");
    return 1;
  }

  int port_num = atoi(argv[1]);
  printf("Starting server on port number %i\n", port_num);
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/

  /* family/domain to be used by listening socket */
  serverAddr.sin_family = AF_INET;
  /* port on which server will wait for clients */
  serverAddr.sin_port = htons(port_num);
  /* interface the socket will listen on */
  serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;

  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of
      requesting client will be stored on serverStorage variable */
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

    /*Convert message received to uppercase*/
    for(i=0;i<nBytes-1;i++)
      buffer[i] = toupper(buffer[i]);

    /*Send uppercase message back to client, using serverStorage as the address*/
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}
