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
  int udpSocket, nBytes, port_num, random_seed;
  float loss_probability;
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

    int separator1_index = find_index_of_separator(buffer,'$');
    int separator2_index = find_index_of_separator(buffer,'!');

    char output_file_target[60];
    strncpy(output_file_target, buffer, separator1_index);
    output_file_target[separator1_index ] = '\0';

    char message[60];
    strncpy(message, &buffer[separator1_index + 1],
      (separator2_index-separator1_index)-3);
    message[strlen(buffer)] = '\0';     /*  terminate substring */

    char to_format_char[60];
    strncpy(to_format_char, &buffer[separator2_index + 1], strlen(buffer));
    to_format_char[60] = '\0';
    int to_format = atoi(to_format_char);

    printf("\nMessage is: %s\n", message);
    printf("Target is: %s\n", output_file_target);
    printf("Using translation type: %i\n", to_format);

    // if have successfully received the message, we send back an ACK
    char ack[] = "ACK";
    lossy_sendto(loss_probability, random_seed, udpSocket, ack, nBytes,
      (struct sockaddr *)&serverStorage,addr_size);

    char reply[20];
    if (correct_format(message) == 1) {
      strcpy(reply, "Success!\n");
    } else {
      strcpy(reply, "Format error!\n");
    }

    // if we get a syntax error we must exit without doing anything
    if (strcmp(reply,"Format error!\n") == 0) {
      return 0;
    }

    switch (to_format) {
      case 0:
        type_0_translation(message, output_file_target);
        break;
      case 1:
        type_1_translation(message, output_file_target);
        break;
      case 2:
        type_2_translation(message, output_file_target);
        break;
      case 3:
        type_3_translation(message, output_file_target);
        break;
    }

    //clear text fields in preparation to receive a new one
    memset(message,0,strlen(message));
    memset(output_file_target,0,strlen(output_file_target));
    memset(to_format_char,0,strlen(to_format_char));

    /*Send message back to client, using serverStorage as the address*/
    lossy_sendto(loss_probability, random_seed, udpSocket, reply, nBytes,
      (struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}
