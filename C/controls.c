#include "controls.h"
#include "servoconfig.h"
// add missing set values
#define angle_overflow
#define pi=3.1415
#define wheel_diameter
#define wheel_distance
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

int drive_forward(float distance, int speed){
    int init_feedback_L = servo_feedback_R();
    int init_feedback_R = servo_feedback_L();
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr2)

    //drive a certain distance using feedback
    float rotations = distance_to_rotations(distance);
    while(rotations>0){
        if(rotations < 1){
            if((servo_feedback_L < init_feedback_L+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L() > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R < init_feedback_R-(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R() > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow){
                break;
            }
        }
        if((servo_feedback_L < init_feedback_L+0.1*angle_overflow && servo_feedback_L() > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R < init_feedback_R+0.1*angle_overflow && servo_feedback_R() > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }

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
    while(rotations>0){
        if(rotations < 1){
            if((servo_feedback_L() < init_feedback_L-(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L() > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R() < init_feedback_R+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R() > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow){
                break;
            }
        }
        if((servo_feedback_L() < init_feedback_L+0.1*angle_overflow && servo_feedback_L() > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R() < init_feedback_R+0.1*angle_overflow && servo_feedback_R() > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }

    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}

int rotate_left(int speed, int angle){
    init_feedback_L = servo_feedback_L;
    init_feedback_R = servo_feedback_R;
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500+speed_to_pwm(speed)+servo_addr2)

    //rotate angle
    rotations = angle_to_rotations(angle)
    while(rotations>0){
        if(rotations < 1){
            if((servo_feedback_L < init_feedback_L+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R < init_feedback_R+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow){
                break;
            }
        }
        if((servo_feedback_L < init_feedback_L+0.1*angle_overflow && servo_feedback_L > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R < init_feedback_R+0.1*angle_overflow && servo_feedback_R > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }

    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}

int rotate_right(int speed){
    init_feedback_L = servo_feedback_L;
    init_feedback_R = servo_feedback_R;
    // init_position = accel_reading

    // send speed and rotate servos
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr1)
    // send(socket, 1500-speed_to_pwm(speed)+servo_addr2)

    //rotate angle
    rotations = angle_to_rotations(angle)
    while(rotations>0){
        if(rotations < 1){
            if((servo_feedback_L < init_feedback_L+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_L > init_feedback_L+(rotations*angle_overflow)-0.1*angle_overflow)
            && (servo_feedback_R < init_feedback_R+(rotations*angle_overflow)+0.1*angle_overflow && servo_feedback_R > init_feedback_R+(rotations*angle_overflow)-0.1*angle_overflow){
                break;
            }
        }
        if((servo_feedback_L < init_feedback_L+0.1*angle_overflow && servo_feedback_L > init_feedback_L-0.1*angle_overflow) 
        && (servo_feedback_R < init_feedback_R+0.1*angle_overflow && servo_feedback_R > init_feedback_R-0.1*angle_overflow)){ //degree fo error
            rotations--;
        }
    }

    // send(socket, 1500+servo_addr1)
    // send(socket, 1500+servo_addr2)
}