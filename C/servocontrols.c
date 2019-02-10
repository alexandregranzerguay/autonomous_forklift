#include <stdlib.h>
#include "servocontrols.h"
#include "servocomm.h"
// add missing set values
// #define speed 40 // in percent!
// int time = 10; //time it takes to travel 1 meter in s

int max_val(int x, int y) {
	if(x >= y) {
		return x;
	} else {
		return y;
	}
}

int min_val(int x, int y) {
	if(x < y) {
		return x;
	} else {
		return y;
	}
}

float distance_to_rotations(int distance){
    // distance in meters
    float wheel_circ = (WHEEL_DIAMETER*2*PI);
    float rotations = distance / wheel_circ;
    return rotations;
}

float angle_to_rotations(int angle){
    float base_circ = (WHEEL_DISTANCE*2*PI);
    float rotations = distance_to_rotations(angle*base_circ/360);
    return rotations;
}

int speed_to_pwm(int speed){
    return (speed * 7500);
}

// Sometimes the feedback has an unusual value returned, this is to filter out those misreadings
int filter_feedback_R(int lastVal) {
	int newVal = servo_feedback_R();
	if(newVal > FEEDBACK_MAX || newVal < FEEDBACK_MIN) {
		return lastVal;
	} else {
		return newVal;
	}
}

int filter_feedback_L(int lastVal) {
	int newVal = servo_feedback_L();
	if(newVal > FEEDBACK_MAX || newVal < FEEDBACK_MIN) {
		return lastVal;
	} else {
		return newVal;
	}
}

int drive(int speed, float units, char dir){
	
	int pulse_L = OFF;
	int pulse_R = OFF;
	
	int unit_time = 0;
	
    // set wheel rotations based on the direction. If it's forwards or backwards, translate a distance to a number of units
	// if it's left or right, translate an angle to a number of units
	if(dir == 'f') {
		unit_time = UNIT_TIME_FORWARD;
		pulse_L += speed_to_pwm(speed);
		pulse_R -= (speed_to_pwm(speed) + RIGHT_ADJUST_FORWARD);
	} else if (dir == 'b') {
		unit_time = UNIT_TIME_BACKWARD;
		pulse_L -= (speed_to_pwm(speed) + LEFT_ADJUST_BACKWARD);
		pulse_R += speed_to_pwm(speed);
	} else if (dir == 'r') {
		unit_time = UNIT_TIME_RIGHT;
		pulse_L += speed_to_pwm(speed);
		pulse_R += speed_to_pwm(speed);
	} else if (dir == 'l') {
		unit_time = UNIT_TIME_LEFT;
		pulse_L -= speed_to_pwm(speed);
		pulse_R -= speed_to_pwm(speed);
	}
	
	servo_write_L(pulse_L);
    servo_write_R(pulse_R);
	usleep((int) (units * unit_time));
	servo_write_L(OFF);
    servo_write_R(OFF);
    return 0;
}

int move_positional(int position){
	int pulse_P = 150000+ position;
	servo_write_P(pulse_P);
	return 0;
}
