/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H


#define ENDBUTTON_BITMASK_FIELD 0x4
#define ENDBUTTON_BITMASK_PADDLE 0x2

#define TO_DEGREES 100
#define SHIFT_BYTE 8

#define CENTERPOINT_NORMAL 7
#define CENTERPOINT_SET 3

#define BLACK_COLOUR 0
#define GREEN_COLOUR 10
#define RED_COLOUR   51

#define STATE_DISABLED 0
#define STATE_INITIALIZING 10
#define STATE_IDLE 20
#define STATE_RUNNING 30
#define STATE_STOPPING 40

#define STATE_SHOOTING 30
#define SHOOT_OUTPUT_BIT 3
#define FAN_OUTPUT_BIT 0

#define STATE_DETECT_RIGHT 0
#define STATE_START_SPEEDTIMER 5
#define STATE_DETECT_MIDDLE 10
#define STATE_DETECT_LEFT 20
#define STATE_SHOOT 30

#define MS_50 50
#define MS_100 100
#define MS_500 500
#define MS_1000 1000

#define MAX_ACC_DEC 40000
#define MAX_VELOCITY 2000
#define MIN_VELOCITY 100
#define STD_VELOCITY 1000
#define MIN_POSITION (PaddleMotor->STS.ReferencePosition - MAX_PADDLE_DISTANCE_TICKS)

#define OVERLOAD 32760
#define UNDERLOAD -32760
#define SHIFT_BYTE 8
#define NUM_SENSORS 3

#define OUT1_BITMASK 0x1
#define OUT2_BITMASK 0x2
#define DEVICE_STATUS_BITMASK 0xF0
#define SENSOR_FAILURE 4

#define BALL_MIN_DISTANCE 50
#define BALL_MAX_DISTANCE 300
#define MAX_PADDLE_DIFFERENCE 50

#define MM_TO_POSITION 11.2
#define MAX_POSITION (PaddleMotor->STS.ReferencePosition - 100)
#define AUTOMODE_VELOCITY 5000
#define MIN_FIELD_DISTANCE 50
#define MAX_INTENSITY 10
#define MIN_INTENSITY 3

#define MAX_ANGLE 18
#define MIN_ANGLE 3

#define DISTANCE_BETWEEN_SENSORS_MM 24
#define DISTANCE_SENSOR_LEFT_TO_PADDLE_MM 75

#define GAME_OVER_TRIGGER_MS 5000

static const float MAX_PADDLE_DISTANCE_MM = 222.0f;
static const float MAX_PADDLE_DISTANCE_TICKS = 2830.0f;

static const float TICKS_TO_MM = 222.0f / 2830.0f;
static const float MM_TO_TICKS = 2830.0f / 222.0f;
#endif
