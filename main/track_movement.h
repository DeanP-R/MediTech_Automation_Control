#pragma once

// Pin definitions
#define LEFT_TRACK_1_PIN 7
#define LEFT_TRACK_2_PIN 6
#define RIGHT_TRACK_1_PIN 5
#define RIGHT_TRACK_2_PIN 4
#define ENABLE_A 9
#define ENABLE_B 3

// Speed of the motors
const int MOTOR_SPEED = 250;

void setup_Motor_Control();
void forward();
void reverse();
void turn_Right();
void turn_Left();

/*

//porportional line following

#define MOT_A1_PIN 5
#define MOT_A2_PIN 6
#define EN1_PIN 3

#define MOT_B1_PIN 9
#define MOT_B2_PIN 10
#define EN2_PIN 11

void setupMotors();
void moveForward();
void turnRight();
void turnLeft();
void scan();
void updateDirection();