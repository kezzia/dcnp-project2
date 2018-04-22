#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include "practice_project.h"
#include "sendlib.h"
#include <time.h>
/*
* <client> <server IP> <server port> <file path> <to format> <to name>
* <loss probability> <random seed>
*/
int main(int argc, char *argv[]) {
  char input_file_path[1024];
  char output_file_target[1024];
  char server_ip[17];
  int port_num, to_format, random_seed;
  float loss_probability;

  if (argc != 8) {
    printf("Too few args!\n");
    return 1;
  }
  /*setting server ip */
  strcpy(server_ip, argv[1]);
  /* Setting port # */
  port_num = atoi(argv[2]);
  /* Setting input file path*/
  strcpy(input_file_path, argv[3]);
  /* Setting format */
  to_format = atoi(argv[4]);
  /* Setting output file target */
  strcpy(output_file_target, argv[5]);
  /* Setting loss ratio */
  loss_probability = atof(argv[6]);
  /*setting seed */
  random_seed = atoi(argv[7]);

  // check if to_format is valid before sending anything to server
  if (to_format > 3) {
    printf("The format code you have entered is invalid/unsupported.\n");
    return 1;
  }
  printf("Sending %s to server\n", input_file_path);
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port_num);
  serverAddr.sin_addr.s_addr = inet_addr(server_ip);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

    FILE * input;
    char str[60];
    input = fopen(input_file_path, "r");

    if(input == NULL) {
      perror("Error opening file!\n");
      return 1;
    }
    printf("File opened!\n");

    while ( fgets(str, 60, input) != NULL) {
      //get message
      sprintf(buffer, "%s$%s!%i", output_file_target,str,to_format);
      printf("Sending to server: %s", buffer);
      nBytes = strlen(buffer) + 1;
      /*Send message to server*/
      lossy_sendto(loss_probability, random_seed, clientSocket, buffer, nBytes,
        (struct sockaddr *)&serverAddr, addr_size);
      int ack_rcvd;
      int timer = 0;
      while (timer < 5000) {
        // the idea here was to give it 5000 iterations to receive the ack
        // if no ack is rcvd close connection
        // gets stuck on recvFrom if no response from server so it's impossible
        // to loop
        ack_rcvd = 0;
        nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
        printf("Received from server: %s\n",buffer);
        if (strcmp(buffer,"ACK") == 0) {
          ack_rcvd = 1;
          break;
        }
        printf("%i seconds left\n", timer);
        timer++;
      }
      printf("\nBYE\n");
      // if we still have no ACK at this point, it's not coming
      // Since the same value of random_seed and loss_probability result in the
      // same segment loss over multiple executions, we are forced to close
      // here to avoid an infinite loop
      if (ack_rcvd == 0) {
        printf("\nPacket lost. Change values of loss_probability and random_seed and try again\n");
        printf("Current value of loss_probability: %f\n", loss_probability);
        printf("Current value of random_seed: %i\n", random_seed);
        return 0;
      }
    }
    fclose(input);

    // while(1) {
    //
    //
    //   /*Receive message from server*/
    //   /* if no message is received from server before timeout then the packet
    //    * has been lost. Since the packets will ALWAYS be lost (or not lost) for
    //    * the given values of loss_probability and random_seed, we close
    //    * the connection here to avoid an infinite loop */
    //
    //   nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
    //
    //   printf("Received from server: %s\n",buffer);
    //
    //   // we should close if the server reports an error
    //   if (strcmp(buffer,"Format error!\n") == 0) {
    //     printf("Closing...\n");
    //     return 0;
    //   }
    // }

    return 0;
}
