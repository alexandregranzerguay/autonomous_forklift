#include "../astar.h"
#include "../map.h"

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

int main(){
	struct Location start, finish;
	start.dir = package_list[0].dir;
	start.loc.x = package_list[0].loc.x;
	start.loc.y = package_list[0].loc.y;
	
	finish.dir = location_list[1].dir;
	finish.loc.x = location_list[1].loc.x;
	finish.loc.y = location_list[1].loc.y;

	char robot_direction = 'n';

	int total_length = find_path(start.loc, finish.loc);
	int i;
	
	robot_direction = 
	for(i = 0; i < total_length; i++)
	{
		char direction = path[i]->dir;
		int num_tiles = path[i]->dist;
		robot_direction = change_dir(direction, robot_direction);
		
		if(i == total_length - 1){
			move_positional(-40000);
		}
		drive_forward(10, num_tiles);
		if(i == total_length - 1){
			move_positional(40000);
		}
	}


}

//test failure case