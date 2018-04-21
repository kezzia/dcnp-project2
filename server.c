#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "practice_project.h"
#include "sendlib.h"


/* <server> <port> <loss probability> <random seed> */
int main(int argc, char *argv[]) {
  int udpSocket, nBytes, port_num, loss_probability, random_seed;
  char buffer[1024];
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

    printf("Received from client: %s\n", buffer);

    int separator_index = find_index_of_separator(buffer);
    char output_file_target[60];
    strncpy(output_file_target, buffer, separator_index);
    output_file_target[separator_index ] = '\0';

    char message[60];
    strncpy(message, &buffer[separator_index + 1], strlen(buffer));
    message[60] = '\0';     /*  terminate substring */

    // printf("message is: %s", message);
    // printf("target is: %s\n", output_file_target);


    char reply[20];
    if (correct_format(message) == 1) {
      strcpy(reply, "Success!\n");
    } else {
      strcpy(reply, "Failure!\n");
    }

    // if we get a syntax error we must exit without doing anything
    if (strcmp(reply,"Failure!\n") == 0) {
      return 0;
    }
    //type_0_translation(message, output_file_target);
    //type_1_translation(message, output_file_target);
    //type_2_translation(message, output_file_target);
    type_3_translation(message, output_file_target);
    //
    /*Send message back to client, using serverStorage as the address*/
    lossy_sendto(loss_probability, random_seed, udpSocket, reply, nBytes,
      (struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}
