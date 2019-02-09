##ifndef DRIVE_H_
#define DRIVE_H_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define PALLET_DIST 20

char change_dir(new_dir, curr_dir);
int get_package();
int drop_package();
int drivePath(int path_length);

#endif