/*
    C socket server example
*/
#include "server.h"

int reset_args(char args[MAX_ARGS][MAX_ARG_SIZE]) {
	int i;
	for (i = 0; i < MAX_ARGS; i++) {
		args[i][0] = '\0';
	}
}

int get_instructions(){
    
}
 
int main(int argc , char *argv[])
{
	int client_sock, read_size, argsize;
	char client_message[MSG_SIZE];
	char args[MAX_ARGS][MAX_ARG_SIZE];
	reset_args(args);
	
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
		if(args[0] == "move" && args[1] == "package" && args[3] == "to" && args[4] == "location"){
			int packageid = atoi(args[2]);
			int locationid = atoi(args[5]);
			Location loc_coord = location_list[locationid];
			Location pkg_coord = package_list[packageid];
			
		}                //move package 0 to location 1
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