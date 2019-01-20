#include "server.h"

int init_server()
{
	int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[MSG_SIZE];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        perror("Could not create socket");
		return -1;
    }
    puts("Socket created");
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );
    
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("Error: bind failed");
        return -1;
    }
    puts("bind done");
    
    //Listen
    listen(socket_desc , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return -1;
    }
    puts("Connection accepted");
	return client_sock;
}

int tokenize(char* client_message, char args[MAX_ARGS][MAX_ARG_SIZE]) {
	char* token = strtok(client_message, " ");
	int i = 0;
	while (token && i < MAX_ARGS) {
        if(token == NULL){
            break;
        }
		strncpy(args[i], token, MAX_ARG_SIZE);
		token = strtok(NULL, " ");
		i++;
	}
	return i;
}