#include "../servocontrols.h"

int main(){
	init_servos();
	drive_forward(1, 1);
	drive_backwards(1, 1);
	rotate_left(1, 50);
	rotate_right(1, 50);
	close_servos();
	return 0;	
}