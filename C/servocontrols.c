#include "servocontrols.h"
#include "servocomm.h"
// add missing set values
#define angle_overflow 10
#define pi 3.1415
#define wheel_diameter 10
#define wheel_distance 10
// #define speed 40 // in percent!
// int time = 10; //time it takes to travel 1 meter in s

float distance_to_rotations(float distance){
    // distance in meters
    float wheel_circ = (wheel_diameter*2*pi);
    float rotations = distance / wheel_circ;
    return rotations;
}

float angle_to_rotations(int angle){
    float base_circ = (wheel_distance*2*pi);
    float rotations = distance_to_rotations(angle*base_circ/360);
    return rotations;
}

int speed_to_pwm(int speed){
    // speed *1000/100 
    return (speed * 10);
}

int drive_forward(float distance, int speed){
    unsigned int init_feedback_L = servo_feedback_R();
    unsigned int init_feedback_R = servo_feedback_L();
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr2)

    //drive a certain distance using feedback
    float rotations = distance_to_rotations(distance);

    // arbitraty value picked but needs to be dynamic
    int pulse_L = 1500+speed_to_pwm(speed);
    int pulse_R = 1500-speed_to_pwm(speed);
    while(rotations>0){
        servo_write_L(pulse_L);
        servo_write_R(pulse_R);
        if(rotations < 1){
            if((servo_feedback_L() < init_feedback_L+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L() > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R() < init_feedback_R-(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R() > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow)){
                break;
            }
        }
        if((servo_feedback_L() < init_feedback_L+0.1*angle_overflow && servo_feedback_L() > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R() < init_feedback_R+0.1*angle_overflow && servo_feedback_R() > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }
    return 0;
    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}

int drive_backwards(float distance, int speed){
    int init_feedback_L = servo_feedback_L();
    int init_feedback_R = servo_feedback_R();
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr2)

    //drive a certain distance using feedback
    float rotations = distance_to_rotations(distance);

    int pulse_L = 1500-speed_to_pwm(speed);
    int pulse_R = 1500+speed_to_pwm(speed);
    while(rotations>0){
        servo_write_L(pulse_L);
        servo_write_R(pulse_R);
        if(rotations < 1){
            if((servo_feedback_L() < init_feedback_L-(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L() > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R() < init_feedback_R+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R() > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow)){
                break;
            }
        }
        if((servo_feedback_L() < init_feedback_L+0.1*angle_overflow && servo_feedback_L() > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R() < init_feedback_R+0.1*angle_overflow && servo_feedback_R() > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }
    return 0;
    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}

int rotate_left(int speed, int angle){
    unsigned int init_feedback_L = servo_feedback_L();
    unsigned int init_feedback_R = servo_feedback_R();
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr2)

    //rotate angle
    float rotations = angle_to_rotations(angle);
    int pulse_L = 1500-speed_to_pwm(speed);
    int pulse_R = 1500-speed_to_pwm(speed);

    while(rotations>0){
        servo_write_L(pulse_L);
        servo_write_L(pulse_R);
        if(rotations < 1){
            if((servo_feedback_L() < init_feedback_L+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L() > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R() < init_feedback_R+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R() > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow)){
                break;
            }
        }
        if((servo_feedback_L() < init_feedback_L+0.1*angle_overflow && servo_feedback_L() > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R() < init_feedback_R+0.1*angle_overflow && servo_feedback_R() > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }
    return 0;
    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}

int rotate_right(int speed, int angle){
    unsigned int init_feedback_L = servo_feedback_L();
    unsigned int init_feedback_R = servo_feedback_R();
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr2)

    //rotate angle
    float rotations = angle_to_rotations(angle);

    int pulse_L = 1500+speed_to_pwm(speed);
    int pulse_R = 1500+speed_to_pwm(speed);

    while(rotations>0){
        servo_write_L(pulse_L);
        servo_write_L(pulse_R);
        if(rotations < 1){
            if((servo_feedback_L() < init_feedback_L+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L() > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R() < init_feedback_R+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R() > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow)){
                break;
            }
        }
        if((servo_feedback_L() < init_feedback_L+0.1*angle_overflow && servo_feedback_L() > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R() < init_feedback_R+0.1*angle_overflow && servo_feedback_R() > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }
    return 0;
    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}