#ifndef SERVOCONTROLS_H_
#define SERVOCONTROLS_H_

#include <stdio.h>
#include <math.h>
#include "servocomm.h"

#define WRAP_VALUE 95000
#define OFF 150000

int max_val(int x, int y);

int min_val(int x, int y);

float distance_to_rotations(int distance);

float angle_to_rotations(int angle);

int filter_feedback_R(int lastVal);

int filter_feedback_L(int lastVal);

int drive(int speed, int units, char dir);

int move_positional(int position);

int speed_to_pwm(int speed);

#endif // SERVOCONTROLS_H_