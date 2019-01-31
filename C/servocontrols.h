#ifndef SERVOCONTROLS_H_
#define SERVOCONTROLS_H_

#include <stdio.h>
#include <math.h>
#include "servocomm.h"

float distance_to_rotations(float distance);

float angle_to_rotations(int angle);

int drive_forward(float distance, int speed);

int drive_backwards(float distance, int speed);

int rotate_left(int speed, int angle);

int rotate_right(int speed, int angle);

int speed_to_pwm(int speed);

#endif // SERVOCONTROLS_H_