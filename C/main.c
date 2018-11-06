/*
    C socket server example
*/
#include "server.h"

 
int main(int argc , char *argv[])
{
	int client_sock, read_size, argsize;
	char client_message[MSG_SIZE];
	char args[MAX_ARGS][MAX_ARG_SIZE];
	
	client_sock = init_server();
	
	if(client_sock < 0) {
		perror("Closing...");
		return 1;
	}
    
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , MSG_SIZE , 0)) > 0 )
    {
        //Send the message back to client
        // write(client_sock , client_message , strlen(client_message));
		// char* token = strtok(s, " ");
		if((argsize = tokenize(client_message, args)) < 0) {
			perror("Error with tokenize");
			return 1;
		}
		write(client_sock , "Message recieved\n" , 17);
    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}