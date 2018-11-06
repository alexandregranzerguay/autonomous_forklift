#ifndef SERVER_H_
#define SERVER_H_

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#define MSG_SIZE 1024
#define PORT 8888
#define MAX_ARGS 10
#define MAX_ARG_SIZE 11

int init_server();
int tokenize(char* client_message, char args[MAX_ARGS][MAX_ARG_SIZE]);

#endif