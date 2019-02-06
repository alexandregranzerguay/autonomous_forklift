#include <stdlib.h>
#include "servocontrols.h"
#include "servocomm.h"
// add missing set values
// #define speed 40 // in percent!
// int time = 10; //time it takes to travel 1 meter in s

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

// Sometimes the feedback has an unusual value returned, this is to filter out those misreading
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

int drive_forward(int speed, int distance){
    int last_feedback_L = servo_feedback_L();
    int last_feedback_R = servo_feedback_R();
	
	int new_feedback_L = last_feedback_L;
	int new_feedback_R = last_feedback_R;
	
	int feedback_count_L = 0;
	int feedback_count_R = 0;
	
	int left_done = 0;
	int right_done = 0;
	
    //drive a certain distance using feedback
	float req_units = distance_to_rotations(distance) * (FEEDBACK_MAX - FEEDBACK_MIN);
	
    // arbitraty value picked but needs to be dynamic
    int pulse_L = 150000 + speed_to_pwm(speed);
    int pulse_R = 150000 - speed_to_pwm(speed);
	servo_write_L(pulse_L);
    servo_write_R(pulse_R);
	
	while(!(right_done && left_done)) {
		new_feedback_L = filter_feedback_L(last_feedback_L);
		new_feedback_R = filter_feedback_R(last_feedback_R);
		// if the new is less, that means the feedback wrapped around
		if(abs(new_feedback_L - last_feedback_L) > 90000) {
			feedback_count_L += (FEEDBACK_MAX - last_feedback_L) + (new_feedback_L - FEEDBACK_MIN);
		} else {
			feedback_count_L += new_feedback_L - last_feedback_L;
		}
		if(abs(new_feedback_R - last_feedback_R) > 90000) {
			feedback_count_R += (FEEDBACK_MAX - new_feedback_R) + (last_feedback_R - FEEDBACK_MIN);
		} else {
			feedback_count_R += last_feedback_R - new_feedback_R;
		}
		if(feedback_count_R > req_units) {
			servo_write_R(150000);
			right_done = 1;
		}
		if(feedback_count_L > req_units) {
			servo_write_L(150000);
			left_done = 1;
		}
		last_feedback_L = new_feedback_L;
		last_feedback_R = new_feedback_R;
		usleep(1000);
	}
    return 0;
}

int drive_backwards(int speed, int distance){
    int last_feedback_L = servo_feedback_L();
    int last_feedback_R = servo_feedback_R();
	
	int new_feedback_L = last_feedback_L;
	int new_feedback_R = last_feedback_R;
	
	int feedback_count_L = 0;
	int feedback_count_R = 0;
	
	int left_done = 0;
	int right_done = 0;
	
    //drive a certain distance using feedback
	float req_units = distance_to_rotations(distance) * (FEEDBACK_MAX - FEEDBACK_MIN);
	
	
    // arbitraty value picked but needs to be dynamic
    int pulse_L = 150000 - speed_to_pwm(speed);
    int pulse_R = 150000 + speed_to_pwm(speed);
	servo_write_L(pulse_L);
    servo_write_R(pulse_R);
	
	while(!(right_done && left_done)) {
		new_feedback_L = filter_feedback_L(last_feedback_L);
		new_feedback_R = filter_feedback_R(last_feedback_R);
		// if the new is less, that means the feedback wrapped around
		if(abs(new_feedback_L - last_feedback_L) > 90000) {
			feedback_count_L += (FEEDBACK_MAX - new_feedback_L) + (last_feedback_L - FEEDBACK_MIN);
		} else {
			feedback_count_L += last_feedback_L - new_feedback_L;
		}
		if(abs(new_feedback_R - last_feedback_R) > 90000) {
			feedback_count_R += (FEEDBACK_MAX - last_feedback_R) + (new_feedback_R - FEEDBACK_MIN);
		} else {
			feedback_count_R += new_feedback_R - last_feedback_R;
		}
		
		
		if(feedback_count_R > req_units) {
			servo_write_R(150000);
			right_done = 1;
		}
		if(feedback_count_L > req_units) {
			servo_write_L(150000);
			left_done = 1;
		}
		last_feedback_L = new_feedback_L;
		last_feedback_R = new_feedback_R;
		usleep(1000);
	}
    return 0;
}

int rotate_left(int speed, int angle){
    int last_feedback_L = servo_feedback_L();
    int last_feedback_R = servo_feedback_R();
	
	int new_feedback_L = last_feedback_L;
	int new_feedback_R = last_feedback_R;
	
	int feedback_count_L = 0;
	int feedback_count_R = 0;
	
	int left_done = 0;
	int right_done = 0;
	
    //drive a certain distance using feedback
	float req_units = distance_to_rotations(angle) * (FEEDBACK_MAX - FEEDBACK_MIN);
	printf("REQ_UNITS: %0.2f\n", req_units);
	
    // arbitraty value picked but needs to be dynamic
    int pulse_L = 150000 - speed_to_pwm(speed);
    int pulse_R = 150000 - speed_to_pwm(speed);
	servo_write_L(pulse_L);
    servo_write_R(pulse_R);
	
	while(!(right_done && left_done)) {
		new_feedback_L = filter_feedback_L(last_feedback_L);
		new_feedback_R = filter_feedback_R(last_feedback_R);
		// if the new is less, that means the feedback wrapped around
		if(abs(new_feedback_L - last_feedback_L) > 90000) {
			feedback_count_L += (FEEDBACK_MAX - new_feedback_L) + (last_feedback_L - FEEDBACK_MIN);
		} else {
			feedback_count_L += last_feedback_L - new_feedback_L;
		}
		if(abs(new_feedback_R - last_feedback_R) > 90000) {
			feedback_count_R += (FEEDBACK_MAX - new_feedback_R) + (last_feedback_R - FEEDBACK_MIN);
		} else {
			feedback_count_R += last_feedback_R - new_feedback_R;
		}
		printf("FEEDBACK_COUNT_R: %d\n", feedback_count_R);
		printf("FEEDBACK_COUNT_L: %d\n", feedback_count_L);
		if(feedback_count_R > req_units) {
			servo_write_R(150000);
			right_done = 1;
		}
		if(feedback_count_L > req_units) {
			servo_write_L(150000);
			left_done = 1;
		}
		last_feedback_L = new_feedback_L;
		last_feedback_R = new_feedback_R;
		usleep(1000);
	}
    return 0;
}

int rotate_right(int speed, int angle){
    int last_feedback_L = servo_feedback_L();
    int last_feedback_R = servo_feedback_R();
	
	int new_feedback_L = last_feedback_L;
	int new_feedback_R = last_feedback_R;
	
	int feedback_count_L = 0;
	int feedback_count_R = 0;
	
	int left_done = 0;
	int right_done = 0;
	
    //drive a certain distance using feedback
	float req_units = distance_to_rotations(angle) * (FEEDBACK_MAX - FEEDBACK_MIN);
	printf("REQ_UNITS: %0.2f\n", req_units);
	
    // arbitraty value picked but needs to be dynamic
    int pulse_L = 150000 + speed_to_pwm(speed);
    int pulse_R = 150000 + speed_to_pwm(speed);
	servo_write_L(pulse_L);
    servo_write_R(pulse_R);
	
	while(!(right_done && left_done)) {
		new_feedback_L = filter_feedback_L(last_feedback_L);
		new_feedback_R = filter_feedback_R(last_feedback_R);
		// if the new is less, that means the feedback wrapped around
		if(abs(new_feedback_L - last_feedback_L) > 90000) {
			feedback_count_L += (FEEDBACK_MAX - last_feedback_L) + (new_feedback_L - FEEDBACK_MIN);
		} else {
			feedback_count_L += new_feedback_L - last_feedback_L;
		}
		if(abs(new_feedback_R - last_feedback_R) > 90000) {
			feedback_count_R += (FEEDBACK_MAX - last_feedback_R) + (new_feedback_R - FEEDBACK_MIN);
		} else {
			feedback_count_R += new_feedback_R - last_feedback_R;
		}
		printf("FEEDBACK_COUNT_R: %d\n", feedback_count_R);
		printf("FEEDBACK_COUNT_L: %d\n", feedback_count_L);
		if(feedback_count_R > req_units) {
			servo_write_R(150000);
			right_done = 1;
		}
		if(feedback_count_L > req_units) {
			servo_write_L(150000);
			left_done = 1;
		}
		last_feedback_L = new_feedback_L;
		last_feedback_R = new_feedback_R;
		usleep(1000);
	}
    return 0;
}