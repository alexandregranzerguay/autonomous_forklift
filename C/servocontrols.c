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
	int last_feedback_L = servo_feedback_L();
    int last_feedback_R = servo_feedback_R();
	
	int new_feedback_L = last_feedback_L;
	int new_feedback_R = last_feedback_R;
	
	int feedback_count_L = 0;
	int feedback_count_R = 0;
	
	int pulse_L = OFF;
	int pulse_R = OFF;
	
	int left_done = 0;
	int right_done = 0;
	
    //drive a certain number of units using feedback
	float req_units = 0;
	
    // set wheel rotations based on the direction. If it's forwards or backwards, translate a distance to a number of units
	// if it's left or right, translate an angle to a number of units
	if(dir == 'f') {
		req_units = distance_to_rotations(units) * (FEEDBACK_MAX - FEEDBACK_MIN);
		pulse_L += speed_to_pwm(speed);
		pulse_R -= speed_to_pwm(speed);
	} else if (dir == 'b') {
		req_units = distance_to_rotations(units) * (FEEDBACK_MAX - FEEDBACK_MIN);
		pulse_L -= speed_to_pwm(speed);
		pulse_R += speed_to_pwm(speed);
	} else if (dir == 'r') {
		req_units = angle_to_rotations(units) * (FEEDBACK_MAX - FEEDBACK_MIN);
		pulse_L += speed_to_pwm(speed);
		pulse_R += speed_to_pwm(speed);
	} else if (dir == 'l') {
		req_units = angle_to_rotations(units) * (FEEDBACK_MAX - FEEDBACK_MIN);
		pulse_L -= speed_to_pwm(speed);
		pulse_R -= speed_to_pwm(speed);
	}
	
	servo_write_L(pulse_L);
    servo_write_R(pulse_R);
	
	/*while(!(right_done && left_done)) {
		new_feedback_L = filter_feedback_L(last_feedback_L);
		new_feedback_R = filter_feedback_R(last_feedback_R);
		// if the new is less, that means the feedback wrapped around
		if(!left_done) {
			if(abs(new_feedback_L - last_feedback_L) > WRAP_VALUE) {
			feedback_count_L += ((FEEDBACK_MAX - max_val(last_feedback_L, new_feedback_L)) + (min_val(last_feedback_L, new_feedback_L) - FEEDBACK_MIN));
			} else {
				feedback_count_L += abs(new_feedback_L - last_feedback_L);
			}
		}
		if(!right_done) {
			if(abs(new_feedback_R - last_feedback_R) > WRAP_VALUE) {
			feedback_count_R += ((FEEDBACK_MAX - max_val(last_feedback_R, new_feedback_R)) + (min_val(last_feedback_R, new_feedback_R) - FEEDBACK_MIN));
			} else {
				feedback_count_R += abs(new_feedback_R - last_feedback_R);
			}
		}
		
		if((feedback_count_R > req_units) && !right_done) {
			servo_write_R(OFF);
			right_done = 1;
		}
		if((feedback_count_L > req_units) && !left_done) {
			servo_write_L(OFF);
			left_done = 1;
		}
		last_feedback_L = new_feedback_L;
		last_feedback_R = new_feedback_R;
		usleep(1000);
	}*/
	usleep(units * 1000000);
	servo_write_L(OFF);
    servo_write_R(OFF);
    return 0;
}

int move_positional(int position){
	int pulse_P = 150000+ position;
	servo_write_P(pulse_P);
	return 0;
}