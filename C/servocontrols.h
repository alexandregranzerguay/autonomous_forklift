#ifndef SERVOCONTROLS_H_
#define SERVOCONTROLS_H_

#include <stdio.h>
#include <math.h>
#include "servocomm.h"

#define LEFT_ADJUST_BACKWARD 800
#define RIGHT_ADJUST_FORWARD 350
#define WRAP_VALUE 95000
#define UNIT_TIME_FORWARD 1900000
#define UNIT_TIME_BACKWARD 2000000
#define UNIT_TIME_RIGHT 10500
#define UNIT_TIME_LEFT 12250
#define OFF 150000

int max_val(int x, int y);

int min_val(int x, int y);

float distance_to_rotations(int distance);

float angle_to_rotations(int angle);

int filter_feedback_R(int lastVal);

int filter_feedback_L(int lastVal);

int drive(int speed, float units, char dir);

int move_positional(int position);

int speed_to_pwm(int speed);

#endif // SERVOCONTROLS_H_
