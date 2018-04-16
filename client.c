/************* UDP CLIENT CODE *******************/
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

/*
 * <client> <server IP> <server port> <file path> <to format> <to name>
 * <loss probability> <random seed>
 */
int main(int argc, char *argv[]) {
  char input_file_path[1024];
  char output_file_target[1024];
  int port_num, to_format, loss_probability, random_seed;

  if (argc != 8) {
    printf("Too few args!\n");
    return 1;
  }

  /* Setting port # */
  port_num = atoi(argv[2]);
  /* Setting input file path*/
  strncpy(input_file_path, argv[3], strlen(argv[3]));
  /* Setting format */
  to_format = atoi(argv[4]);
  /* Setting output file target */
  strncpy(output_file_target, argv[5], strlen(argv[5]));
  /* Setting loss ratio */
  loss_probability = atoi(argv[6]);
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
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  while(1){
    printf("Type a sentence to send to server:\n");
    fgets(buffer,1024,stdin);
    printf("You typed: %s",buffer);

    nBytes = strlen(buffer) + 1;

    ssize_t sendto(int socket, const void *message, size_t length,
           int flags, const struct sockaddr *dest_addr,
           socklen_t dest_len);
    /*Send message to server*/
    lossy_sendto(loss_probability, random_seed, clientSocket, buffer, nBytes,
      (struct sockaddr *)&serverAddr, addr_size);

    /*Receive message from server*/
    nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

    printf("Received from server: %s\n",buffer);

  }

  return 0;
}
