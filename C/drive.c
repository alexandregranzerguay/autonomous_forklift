#include "drive.h"
#include "servocontrols.h"
#include "astar.h"

char change_dir(char new_dir, char curr_dir) {
	if(new_dir == 'n' && curr_dir == 'e')
		{
		  drive(2, 90, 'l');
		}
		if(new_dir == 's' && curr_dir == 'e')
		{
		  drive(2, 90, 'r');
		}
		if(new_dir == 'w' && curr_dir == 'e')
		{
		  drive(2, 180, 'r');
		}
		
		if(new_dir == 's' && curr_dir == 'n')
		{
		  drive(2, 180, 'l');
		}
		if(new_dir == 'e' && curr_dir == 'n')
		{
		  drive(2, 90, 'r');
		}
		if(new_dir == 'w' && curr_dir == 'n')
		{
		  drive(2, 90, 'l');
		} 
		  
		if(new_dir == 's' && curr_dir == 'w')
		{
		  drive(2, 90, 'l');
		}
		if(new_dir == 'e' && curr_dir == 'w')
		{
		  drive(2, 180, 'r');
		}
		if(new_dir == 'n' && curr_dir == 'w')
		{
		  drive(2, 90, 'r');
		} 
		  
		if(new_dir == 'n' && curr_dir == 's')
		{
		  drive(2, 180, 'l');
		}
		if(new_dir == 'e' && curr_dir == 's')
		{
		  drive(2, 90, 'l');
		}
		if(new_dir == 'w' && curr_dir == 's')
		{
		  drive(2, 90, 'r');  
		}
	return new_dir;
}

int get_package() {
	move_positional(-40000);
	drive(2, PALLET_DIST, 'f');
	move_positional(40000);
	drive(2, PALLET_DIST, 'b');
}

int drop_package() {
	move_positional(40000);
	drive(2, PALLET_DIST, 'f');
	move_positional(-40000);
	drive(2, PALLET_DIST, 'b');
	move_positional(40000);
}

int drive_path(int path_length, char * robot_direction) {
	int i;
	for(i = 0; i < path_length; i++)
	{
		char direction = path[i].dir;
		int num_tiles = path[i].dist;
		*robot_direction = change_dir(direction, *robot_direction);
		drive(2, num_tiles, 'f');
	}
}