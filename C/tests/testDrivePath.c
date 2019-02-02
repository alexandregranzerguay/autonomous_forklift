#include "astar.h"

int main(){

Coord Begin;
Coord Finish;
Begin->x = 1;
Begin->y = 1;
char robot_direction;
Finish->x = 3;
Finish->y = 3;
robot_direction = 'n';
int total_length = find_path(Begin, Finish);
int i;
	for(i = 0; i < total_length; i++)
	{
		char direction = path[i]->dir;
		int num_tiles = path[i]->dist;
		if(direction == 'e && robot_direction == 'e')
		{
		// no rotation
		}
		if(direction == 'n' && robot_direction == 'e')
		{
		  rotate_left(10, 90);
		  robot_direction = 'n';
		}
		if(direction == 's' && robot_direction == 'e')
		{
		  rotate_right(10, 90);
		  robot_direction = 's';
		}
		if(direction == 'w' && robot_direction == 'e')
		{
		  rotate_right(10, 180);
		  robot_direction = 'w';
		}
		
		
		if(direction == 'n' && robot_direction == 'n')
		{
		  // no rotation
		}
		if(direction == 's' && robot_direction == 'n')
		{
		  rotate_left(10, 180);
		  robot_direction = 's';
		}
		if(direction == 'e' && robot_direction == 'n')
		{
		  rotate_right(10, 90);
		  robot_direction = 'e';
		}
		if(direction == 'w' && robot_direction == 'n')
		{
		  rotate_left(10, 90);
		  robot_direction = 'w';
		} 
		  
		  
		if(direction == 'w' && robot_direction == 'w')
		{
		  // no rotation
		}
		if(direction == 's' && robot_direction == 'w')
		{
		  rotate_left(10, 90);
		  robot_direction = 's';
		}
		if(direction == 'e' && robot_direction == 'w')
		{
		  rotate_right(10, 180);
		  robot_direction = 'e';
		}
		if(direction == 'n' && robot_direction == 'w')
		{
		  rotate_right(10, 90);
		  robot_direction = 'n';
		} 
		  
		  
		if(direction == 's' && robot_direction == 's')
		{
		  // no rotation
		}
		if(direction == 'n' && robot_direction == 's')
		{
		  rotate_left(10, 180);
		  robot_direction = 'n';
		}
		if(direction == 'e' && robot_direction == 's')
		{
		  rotate_left(10, 90);
		  robot_direction = 'e';
		}
		if(direction == 'w' && robot_direction == 's')
		{
		  rotate_right(10, 90);  
		  robot_direction = 'w';
		}
		drive_forward(10, num_tiles);
		
	}


}

test failure case