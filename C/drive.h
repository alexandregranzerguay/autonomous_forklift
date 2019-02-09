#ifndef DRIVE_H_
#define DRIVE_H_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define PALLET_DIST 20

char change_dir(char new_dir, char curr_dir);
int get_package();
int drop_package();
int drive_path(int path_length, char * robot_direction);

#endif