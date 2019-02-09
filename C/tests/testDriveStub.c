#include "../servocontrols.h"

int main(){
	init_servos();
	drive(1, 150, 'f');
	drive(1, 150, 'b');
	drive(1, 150, 'l');
	drive(1, 150, 'r');
	close_servos();
	return 0;	
}