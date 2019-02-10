#include "../servocontrols.h"

int main(){
	init_servos();
	// drive(1, 90, 'r');
	move_positional(-75000);
	usleep(500000);
	drive(1, 0.5, 'f');
	usleep(500000);
	move_positional(10000);
	usleep(500000);
	drive(1, 0.5, 'b');
	close_servos();
return 0;	
}
