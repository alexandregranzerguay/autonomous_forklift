#ifndef SERVOCOMM_H_
#define SERVOCOMM_H_

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include "address_map_arm.h"

#define ANGLE_OVERFLOW 10
#define PI 3.1415
#define WHEEL_DIAMETER 65
#define WHEEL_DISTANCE 10
#define FEEDBACK_MIN 3190
#define FEEDBACK_MAX 106810

/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void * map_physical (int, unsigned int, unsigned int);
void close_physical (int);
int unmap_physical (void *, unsigned int);
int init_servos(void);
int close_servos(void);
int servo_write_R(int pulse);
int servo_write_L(int pulse);
int servo_feedback_L(void);
int servo_feedback_R(void);
int servo_write_P(int pulse);

#endif