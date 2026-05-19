/********************************************************************
 * COPYRIGHT - MyAutoMation-IT
 ********************************************************************
 * Author: Raivo Berends
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "Library.h"
#include "CommonTypes.h"
#include <string.h>

_SETUP_TEST(void)
{
	DistanceSensorFB.DistanceSensorLeft = &DistanceSensorStruct;
	DistanceSensorFB.DistanceSensorMiddle = &DistanceSensorStruct;
	DistanceSensorFB.DistanceSensorRight = &DistanceSensorStruct;
	
	memset(	DistanceSensorFB.DistanceSensorMiddle, 0, sizeof(*DistanceSensorFB.DistanceSensorMiddle));

	TEST_DONE;
}

_TEST Test_DistanceSensor_CombinesMSB_LSB(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = BALL_MIN_DISTANCE + 100;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(BALL_MIN_DISTANCE + 100, DistanceSensorFB.DistanceSensorMiddle->STS.Distance);

	TEST_DONE;
}

_TEST Test_DistanceSensor_ClampsOverloadToZero(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataMSB = (OVERLOAD >> 8);
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = (OVERLOAD & 0xFF);

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->STS.Distance);

	TEST_DONE;
}

_TEST Test_DistanceSensor_ClampsUnderloadToZero(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataMSB = (UNDERLOAD >> 8);
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = (UNDERLOAD & 0xFF);

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->STS.Distance);

	TEST_DONE;
}

_TEST Test_DistanceSensor_Out1BitMapping(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.SensorInfo = OUT1_BITMASK;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(OUT1_BITMASK, DistanceSensorFB.DistanceSensorMiddle->IO.OUT1);

	TEST_DONE;
}

_TEST Test_DistanceSensor_Out2BitMapping(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.SensorInfo = OUT2_BITMASK;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->IO.OUT2);

	TEST_DONE;
}

_TEST Test_DistanceSensor_DeviceStatusMapping(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.SensorInfo = SENSOR_FAILURE << 4;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(SENSOR_FAILURE, DistanceSensorFB.DistanceSensorMiddle->STS.DeviceStatus);

	TEST_DONE;
}

_TEST Test_DistanceSensor_BallDetectedInsideRange(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataMSB = 0;
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = BALL_MIN_DISTANCE + 10;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(60, DistanceSensorFB.DistanceSensorMiddle->STS.Distance);
	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->STS.BallDetected);

	TEST_DONE;
}

_TEST Test_DistanceSensor_BallDetectedOutsideRange(void)
{
	DistanceSensorFB.DistanceSensorMiddle->STS.Distance = BALL_MAX_DISTANCE + 10;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->STS.BallDetected);

	TEST_DONE;
}

_TEST Test_DistanceSensor_TooFarCondition(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataMSB = 0x01;
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = 0x5E;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->STS.TooFar);
	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->ALM.OutOfBounds);

	TEST_DONE;
}

_TEST Test_DistanceSensor_TooCloseCondition(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataMSB = 0;
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = 30;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->STS.TooClose);
	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->ALM.OutOfBounds);

	TEST_DONE;
}

_TEST Test_DistanceSensor_NormalRangeClearsFlags(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = BALL_MIN_DISTANCE + 10;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->STS.TooClose);
	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->STS.TooFar);
	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->ALM.OutOfBounds);

	TEST_DONE;
}

_TEST Test_DistanceSensor_DeviceFailureSetsAlarm(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.SensorInfo = SENSOR_FAILURE << 4;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->STS.AlarmActive);

	TEST_DONE;
}

_TEST Test_DistanceSensor_OutOfBoundsSetsAlarm(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataMSB = 0x01;
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = 0x5E;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(1, DistanceSensorFB.DistanceSensorMiddle->ALM.OutOfBounds);

	TEST_DONE;
}

_TEST Test_DistanceSensor_DeviceStatusZeroClearsAlarm(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = BALL_MIN_DISTANCE;
	DistanceSensorFB.DistanceSensorMiddle->IO.SensorInfo = 0;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(0, DistanceSensorFB.DistanceSensorMiddle->STS.AlarmActive);

	TEST_DONE;
}

_TEST Test_DistanceSensor_AlarmColourRed(void)
{
	DistanceSensorFB.DistanceSensorMiddle->STS.AlarmActive = 1;
	DistanceSensorFB.DistanceSensorMiddle->IO.SensorInfo = 0x40;

	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(RED_COLOUR, DistanceSensorFB.DistanceSensorMiddle->STS.AlarmActiveColour);

	TEST_DONE;
}

_TEST Test_DistanceSensor_AlarmColourGreen(void)
{
	DistanceSensorFB.DistanceSensorMiddle->IO.DataLSB = BALL_MIN_DISTANCE + 10;
	DistanceSensorFB.DistanceSensorMiddle->STS.AlarmActive = 0;
	
	FB_DistanceSensor(&DistanceSensorFB);

	TEST_ASSERT_EQUAL_INT(GREEN_COLOUR, DistanceSensorFB.DistanceSensorMiddle->STS.AlarmActiveColour);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 10:39:43Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_DistanceSensor_CombinesMSB_LSB", Test_DistanceSensor_CombinesMSB_LSB), 
	new_TestFixture("Test_DistanceSensor_ClampsOverloadToZero", Test_DistanceSensor_ClampsOverloadToZero), 
	new_TestFixture("Test_DistanceSensor_ClampsUnderloadToZero", Test_DistanceSensor_ClampsUnderloadToZero), 
	new_TestFixture("Test_DistanceSensor_Out1BitMapping", Test_DistanceSensor_Out1BitMapping), 
	new_TestFixture("Test_DistanceSensor_Out2BitMapping", Test_DistanceSensor_Out2BitMapping), 
	new_TestFixture("Test_DistanceSensor_DeviceStatusMapping", Test_DistanceSensor_DeviceStatusMapping), 
	new_TestFixture("Test_DistanceSensor_BallDetectedInsideRange", Test_DistanceSensor_BallDetectedInsideRange), 
	new_TestFixture("Test_DistanceSensor_BallDetectedOutsideRange", Test_DistanceSensor_BallDetectedOutsideRange), 
	new_TestFixture("Test_DistanceSensor_TooFarCondition", Test_DistanceSensor_TooFarCondition), 
	new_TestFixture("Test_DistanceSensor_TooCloseCondition", Test_DistanceSensor_TooCloseCondition), 
	new_TestFixture("Test_DistanceSensor_NormalRangeClearsFlags", Test_DistanceSensor_NormalRangeClearsFlags), 
	new_TestFixture("Test_DistanceSensor_DeviceFailureSetsAlarm", Test_DistanceSensor_DeviceFailureSetsAlarm), 
	new_TestFixture("Test_DistanceSensor_OutOfBoundsSetsAlarm", Test_DistanceSensor_OutOfBoundsSetsAlarm), 
	new_TestFixture("Test_DistanceSensor_DeviceStatusZeroClearsAlarm", Test_DistanceSensor_DeviceStatusZeroClearsAlarm), 
	new_TestFixture("Test_DistanceSensor_AlarmColourRed", Test_DistanceSensor_AlarmColourRed), 
	new_TestFixture("Test_DistanceSensor_AlarmColourGreen", Test_DistanceSensor_AlarmColourGreen), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_DistanceSensor, "testSet_DistanceSensor", setupTest, 0, fixtures, 0, 0, 0);

