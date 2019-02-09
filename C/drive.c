#include "servocontrols.h"
#include "astar.h"

char change_dir(new_dir, curr_dir) {
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
}

int drivePath(int path_length) {
	for(i = 0; i < total_length; i++)
	{
		char direction = path[i]->dir;
		int num_tiles = path[i]->dist;
		robot_direction = change_dir(direction, robot_direction);
		drive(2, num_tiles, 'f');
	}
}