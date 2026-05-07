/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#define BLACK_COLOUR 0
#define GREEN_COLOUR 10
#define RED_COLOUR   51

#define STATE_DISABLED 0
#define STATE_INITIALIZING 10
#define STATE_IDLE 20
#define STATE_RUNNING 30
#define STATE_STOPPING 40

#define MS_100 100
#define MS_500 500
#define MS_1000 1000

#define MAX_ACC_DEC 40000
#define MAX_VELOCITY 2000
#define MIN_VELOCITY 100
#define STD_VELOCITY 1000
#define MIN_POSITION (PaddleMotor->STS.ReferencePosition - MAX_PADDLE_DISTANCE_TICKS)

static const float MAX_PADDLE_DISTANCE_MM = 222.0f;
static const float MAX_PADDLE_DISTANCE_TICKS = 2830.0f;

static const float TICKS_TO_MM = 222.0f / 2830.0f;
static const float MM_TO_TICKS = 2830.0f / 222.0f;
#endif
