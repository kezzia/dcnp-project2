/************* UDP SERVER CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

/* <server> <port> <loss probability> <random seed> */
int main(int argc, char *argv[]) {
  int udpSocket, nBytes, port_num, loss_probability, random_seed;
  char buffer[1024];
  char message[9];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  if (argc != 4) {
    printf("Too few args!\n");
    return 1;
  }

  port_num = atoi(argv[1]);
  loss_probability = atoi(argv[2]);
  random_seed = atoi(argv[3]);

  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port_num);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;
  printf("Server running on port %d\n", port_num);
  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of
      requesting client will be stored on serverStorage variable */
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

    printf("Received from client: %s", buffer);

    if (correct_format(buffer) == 1) {
      strcpy(message, "Success!\n");
    } else {
      strcpy(message, "Failure!\n");
    }

    printf("%s\n", message);
    // /*Convert message received to uppercase*/
    // for(i=0;i<nBytes-1;i++)
    //   buffer[i] = toupper(buffer[i]);
    //

    /*Send uppercase message back to client, using serverStorage as the address*/
    sendto(udpSocket,message,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);

    // if we get a syntax error we must exit without doing anything
    if (strcmp(message,"Failure!\n") == 0) {
      return 0;
    }
  }

  return 0;
}
