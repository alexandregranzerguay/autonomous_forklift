#ifndef SERVOCOMM_H_
#define SERVOCOMM_H_

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include "address_map_arm.h"

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

#endif