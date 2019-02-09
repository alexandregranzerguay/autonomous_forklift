#include <stdlib.h>
#include <stdio.h>
#include "../servocontrols.h"
#include "../servocomm.h"
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
    return (speed * 5000);
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

int drive(int speed, int units, char dir){
	printf("DRIVING %c FOR %d UNITS AT SPEED %d\n", dir, units, speed);
	
    return 0;
}

int move_positional(int position){
	int pulse_P = 150000 + position;
	printf("CHANGING POSITIONAL TO %d\n", pulse_P);
	return 0;
}