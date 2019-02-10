/*
    C socket server example
*/
#include "server.h"
#include "map.h"
#include "astar.h"
#include "drive.h"

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
	init_servos();
	struct Coord robot_loc;
	robot_loc.x = 1;
	robot_loc.y = 4;
	char robot_direction = 'n'; 
	int client_sock, read_size, argsize, total_length;
	char client_message[MSG_SIZE];
	char args[MAX_ARGS][MAX_ARG_SIZE];
	reset_args(args);
	
	init_map("map.txt");
	
	init_locs();
	init_packs();
	
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
		if(!(strcmp(args[0],"move") || strcmp(args[1], "package") || strcmp(args[3], "to") || strcmp(args[4], "location"))){
			int packageid = atoi(args[2]);
			int locationid = atoi(args[5]);
			printf("PACKAGEID: %d, LOCATIONID: %d\n", packageid, locationid);
			struct Location loc = location_list[locationid];
			struct Location pkg = package_list[packageid];	
			printf("PACKAGE DIRECTION: %c, PACKAGE X: %d, PACKAGE Y: %d\n", pkg.dir, pkg.loc.x, pkg.loc.y);
			printf("LOCATION DIRECTION: %c, LOCATION X: %d, LOCATION Y: %d\n", loc.dir, loc.loc.x, loc.loc.y);
			printf("ROBOT AT X: %d, Y: %d, FACING DIRECTION %c\n", robot_loc.x, robot_loc.y, robot_direction);
			total_length = find_path(robot_loc, pkg.loc);
			drive_path(total_length, &robot_direction);
			free(path);
			robot_loc.x = pkg.loc.x;
			robot_loc.y = pkg.loc.y;
			printf("ROBOT AT X: %d, Y: %d, FACING DIRECTION %c\n", robot_loc.x, robot_loc.y, robot_direction);
			robot_direction = change_dir(pkg.dir, robot_direction);
			printf("ROBOT AT X: %d, Y: %d, FACING DIRECTION %c\n", robot_loc.x, robot_loc.y, robot_direction);
			get_package();
			total_length = find_path(robot_loc, loc.loc);
			drive_path(total_length, &robot_direction);
			free(path);
			robot_loc.x = loc.loc.x;
			robot_loc.y = loc.loc.y;
			printf("ROBOT AT X: %d, Y: %d, FACING DIRECTION %c\n", robot_loc.x, robot_loc.y, robot_direction);
			robot_direction = change_dir(loc.dir, robot_direction);
			printf("ROBOT AT X: %d, Y: %d, FACING DIRECTION %c\n", robot_loc.x, robot_loc.y, robot_direction);
			drop_package();
			package_list[packageid].dir = location_list[locationid].dir;
			package_list[packageid].loc.x = location_list[locationid].loc.x;
			package_list[packageid].loc.y = location_list[locationid].loc.y;
		}                //move package 0 to location 1
		write(client_sock , "Message recieved\n" , 17);
    }
	close_servos();
    
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
