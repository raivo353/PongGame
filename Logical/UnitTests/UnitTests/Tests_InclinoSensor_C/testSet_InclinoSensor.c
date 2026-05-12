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
	InclinoSensorFB.InclinoSensor = &InclinoSensorStruct;
	memset(	InclinoSensorFB.InclinoSensor, 0, sizeof(*InclinoSensorFB.InclinoSensor));

	TEST_DONE;
}

_TEST Test_InclinoSensor_CalculatesAngleFromRawData(void)
{
	InclinoSensorFB.InclinoSensor->IO.DataMSB = 0x01;
	InclinoSensorFB.InclinoSensor->IO.DataLSB = 0x00;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_FLOAT((float)256 / TO_DEGREES, InclinoSensorFB.InclinoSensor->STS.CurrentAngle);

	TEST_DONE;
}

_TEST Test_InclinoSensor_CalculatesNegativeAngle(void)
{
	InclinoSensorFB.InclinoSensor->IO.DataMSB = 0xFF;
	InclinoSensorFB.InclinoSensor->IO.DataLSB = 0x00;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_FLOAT((float)((INT)((0xFF00))) / TO_DEGREES, InclinoSensorFB.InclinoSensor->STS.CurrentAngle);

	TEST_DONE;
}

_TEST Test_InclinoSensor_SetsAlarmColourGreen(void)
{
	InclinoSensorFB.InclinoSensor->STS.AlarmActive = 0;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_INT(GREEN_COLOUR, InclinoSensorFB.InclinoSensor->STS.AlarmActiveColour);

	TEST_DONE;
}

_TEST Test_InclinoSensor_SetsAlarmColourRed(void)
{
	InclinoSensorFB.InclinoSensor->STS.AlarmActive = 1;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_INT(RED_COLOUR, InclinoSensorFB.InclinoSensor->STS.AlarmActiveColour);

	TEST_DONE;
}

_TEST Test_InclinoSensor_SetCenterPoint_NormalMode(void)
{
	InclinoSensorFB.InclinoSensor->CS.SetCenterPoint = 0;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_INT(CENTERPOINT_NORMAL, InclinoSensorFB.InclinoSensor->IO.SetCenterPoint);

	TEST_DONE;
}

_TEST Test_InclinoSensor_SetCenterPoint_CalibrationMode(void)
{
	InclinoSensorFB.InclinoSensor->CS.SetCenterPoint = 1;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_INT(CENTERPOINT_SET, InclinoSensorFB.InclinoSensor->IO.SetCenterPoint);

	TEST_DONE;
}

_TEST Test_InclinoSensor_RawBitCombination(void)
{
	InclinoSensorFB.InclinoSensor->IO.DataMSB = 0x12;
	InclinoSensorFB.InclinoSensor->IO.DataLSB = 0x34;

	FB_InclinoSensor(&InclinoSensorFB);

	TEST_ASSERT_EQUAL_INT((0x1234), (INT)((InclinoSensorFB.InclinoSensor->STS.CurrentAngle * TO_DEGREES) + 1));

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 09:44:28Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_InclinoSensor_CalculatesAngleFromRawData", Test_InclinoSensor_CalculatesAngleFromRawData), 
	new_TestFixture("Test_InclinoSensor_CalculatesNegativeAngle", Test_InclinoSensor_CalculatesNegativeAngle), 
	new_TestFixture("Test_InclinoSensor_SetsAlarmColourGreen", Test_InclinoSensor_SetsAlarmColourGreen), 
	new_TestFixture("Test_InclinoSensor_SetsAlarmColourRed", Test_InclinoSensor_SetsAlarmColourRed), 
	new_TestFixture("Test_InclinoSensor_SetCenterPoint_NormalMode", Test_InclinoSensor_SetCenterPoint_NormalMode), 
	new_TestFixture("Test_InclinoSensor_SetCenterPoint_CalibrationMode", Test_InclinoSensor_SetCenterPoint_CalibrationMode), 
	new_TestFixture("Test_InclinoSensor_RawBitCombination", Test_InclinoSensor_RawBitCombination), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_InclinoSensor, "testSet_InclinoSensor", setupTest, 0, fixtures, 0, 0, 0);

