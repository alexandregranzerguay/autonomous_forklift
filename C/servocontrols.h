#ifndef SERVOCONTROLS_H_
#define SERVOCONTROLS_H_

#include <stdio.h>
#include <math.h>
#include "servocomm.h"

float distance_to_rotations(int distance);

float angle_to_rotations(int angle);

int filter_feedback_R(int lastVal);

int filter_feedback_L(int lastVal);

int drive_forward(int speed, int distance);

int drive_backwards(int speed, int distance);

int rotate_left(int speed, int angle);

int rotate_right(int speed, int angle);

int speed_to_pwm(int speed);

#endif // SERVOCONTROLS_H_