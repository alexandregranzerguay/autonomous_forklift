#include "../servocomm.h"

#define CHANGE_RATE 1000
int r_on, l_on;
int r_count, l_count;

int init_servos(void){
   r_on = 0;
   l_on = 0;
   r_count = FEEDBACK_MIN;
   l_count = FEEDBACK_MIN;
   return 0;
}

int close_servos(void){
	// Does nothing for stub
    return 0;
}

// This program writes a PWM value to servos
int servo_write_R(int pulse){
    if(pulse > 150000) {
		r_on = 1;
	} else if (pulse < 150000) {
		r_on = -1;
	} else {
		r_on = 0;
	}
	printf("R_ON = %d\n", r_on);
}

// This program writes a PWM value to servos
int servo_write_L(int pulse){
    if(pulse > 150000) {
		l_on = 1;
	} else if (pulse < 150000) {
		l_on = -1;
	} else {
		l_on = 0;
	}
	printf("L_ON = %d\n", l_on);
}

int servo_feedback_R(void){
	if(r_on == 1) {
		r_count += CHANGE_RATE;
		if(r_count > FEEDBACK_MAX)
			r_count = FEEDBACK_MIN + CHANGE_RATE;
	} else if (r_on == -1) {
		r_count -= CHANGE_RATE;
		if(r_count < FEEDBACK_MIN)
			r_count = FEEDBACK_MAX - CHANGE_RATE;
	}
	
	printf("Read %d from right\n", r_count);
	return r_count;
}

int servo_feedback_L(void){
	if(l_on == 1) {
		l_count += CHANGE_RATE;
		if(l_count > FEEDBACK_MAX)
			l_count = FEEDBACK_MIN + CHANGE_RATE;
	} else if (l_on == -1) {
		l_count -= CHANGE_RATE;
		if(l_count < FEEDBACK_MIN)
			l_count = FEEDBACK_MAX - CHANGE_RATE;
	}
	
	printf("Read %d from left\n", l_count);
	return l_count;
}

