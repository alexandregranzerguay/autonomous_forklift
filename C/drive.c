#include "drive.h"
#include "servocontrols.h"
#include "astar.h"

char change_dir(char new_dir, char curr_dir) {
	if(new_dir == 'n' && curr_dir == 'e')
		{
		  drive(1, 90, 'l');
		}
		if(new_dir == 's' && curr_dir == 'e')
		{
		  drive(1, 90, 'r');
		}
		if(new_dir == 'w' && curr_dir == 'e')
		{
		  drive(1, 180, 'r');
		}
		
		if(new_dir == 's' && curr_dir == 'n')
		{
		  drive(1, 180, 'l');
		}
		if(new_dir == 'e' && curr_dir == 'n')
		{
		  drive(1, 90, 'r');
		}
		if(new_dir == 'w' && curr_dir == 'n')
		{
		  drive(1, 90, 'l');
		} 
		  
		if(new_dir == 's' && curr_dir == 'w')
		{
		  drive(1, 90, 'l');
		}
		if(new_dir == 'e' && curr_dir == 'w')
		{
		  drive(1, 180, 'r');
		}
		if(new_dir == 'n' && curr_dir == 'w')
		{
		  drive(1, 90, 'r');
		} 
		  
		if(new_dir == 'n' && curr_dir == 's')
		{
		  drive(1, 180, 'l');
		}
		if(new_dir == 'e' && curr_dir == 's')
		{
		  drive(1, 90, 'l');
		}
		if(new_dir == 'w' && curr_dir == 's')
		{
		  drive(1, 90, 'r');  
		}
	usleep(500000);
	return new_dir;
}

int get_package() {
	move_positional(-75000);
	usleep(500000);
	drive(1, 0.5, 'f');
	usleep(500000);
	move_positional(40000);
	usleep(500000);
	drive(1, 0.5, 'b');
	usleep(500000);
}

int drop_package() {
	move_positional(40000);
	usleep(500000);
	drive(1, 0.5, 'f');
	usleep(500000);
	move_positional(-75000);
	usleep(500000);
	drive(1, 0.5, 'b');
	usleep(500000);
	move_positional(40000);
	usleep(500000);
}

int drive_path(int path_length, char * robot_direction) {
	int i;
	for(i = 0; i < path_length; i++)
	{
		char direction = path[i].dir;
		int num_tiles = path[i].dist;
		*robot_direction = change_dir(direction, *robot_direction);
		drive(1, num_tiles, 'f');
		usleep(500000);
	}
}
