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
	FieldControlFB.FieldControl = &FieldControlStruct;
	FieldControlFB.FieldMotor = &FieldMotorStruct;
	FieldControlFB.InclinoSensor = &InclinoSensorStruct;
	
	memset(FieldControlFB.FieldControl, 0, sizeof(*FieldControlFB.FieldControl));
	memset(FieldControlFB.FieldMotor, 0, sizeof(*FieldControlFB.FieldMotor));
	memset(FieldControlFB.InclinoSensor, 0, sizeof(*FieldControlFB.InclinoSensor));
	
	FieldControlFB.FieldControl->STS.StateInt = STATE_DISABLED;

	TEST_DONE;
}

_TEST Test_Disabled_ResetsAtTargetPosition(void)
{
	FieldControlFB.FieldControl->STS.AtTargetPosition = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldControl->STS.AtTargetPosition);

	TEST_DONE;
}

_TEST Test_Disabled_IncreaseAngle_IncreasesAngle(void)
{
	FieldControlFB.FieldControl->PAR.Angle = 10.0;
	FieldControlFB.FieldControl->HMI.IncreaseAngle = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_REAL_WITHIN(0.0001, 10.002, FieldControlFB.FieldControl->PAR.Angle);

	TEST_DONE;
}

_TEST Test_Disabled_IncreaseAngle_DoesNotExceedMax(void)
{
	FieldControlFB.FieldControl->PAR.Angle = MAX_ANGLE;
	FieldControlFB.FieldControl->HMI.IncreaseAngle = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_DOUBLE(MAX_ANGLE, FieldControlFB.FieldControl->PAR.Angle);

	TEST_DONE;
}

_TEST Test_Disabled_DecreaseAngle_DecreasesAngle(void)
{
	FieldControlFB.FieldControl->PAR.Angle = 10.0;
	FieldControlFB.FieldControl->HMI.DecreaseAngle = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_REAL_WITHIN(0.0001, 9.998, FieldControlFB.FieldControl->PAR.Angle);

	TEST_DONE;
}

_TEST Test_Disabled_DecreaseAngle_DoesNotGoBelowMin(void)
{
	FieldControlFB.FieldControl->PAR.Angle = MIN_ANGLE;
	FieldControlFB.FieldControl->HMI.DecreaseAngle = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_DOUBLE(MIN_ANGLE, FieldControlFB.FieldControl->PAR.Angle);

	TEST_DONE;
}

_TEST Test_Disabled_TransitionsToInitializing(void)
{
	FieldControlFB.FieldControl->STS.Initializing = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, FieldControlFB.FieldControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_StaysDisabled_WhenNotInitializing(void)
{
	FieldControlFB.FieldControl->STS.Initializing = 0;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, FieldControlFB.FieldControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_IncreaseHasPriorityOverDecrease(void)
{
	FieldControlFB.FieldControl->PAR.Angle = 10.0;

	FieldControlFB.FieldControl->HMI.IncreaseAngle = 1;
	FieldControlFB.FieldControl->HMI.DecreaseAngle = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_REAL_WITHIN(0.0001, 10.002, FieldControlFB.FieldControl->PAR.Angle);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 12:58:24Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Disabled_ResetsAtTargetPosition", Test_Disabled_ResetsAtTargetPosition), 
	new_TestFixture("Test_Disabled_IncreaseAngle_IncreasesAngle", Test_Disabled_IncreaseAngle_IncreasesAngle), 
	new_TestFixture("Test_Disabled_IncreaseAngle_DoesNotExceedMax", Test_Disabled_IncreaseAngle_DoesNotExceedMax), 
	new_TestFixture("Test_Disabled_DecreaseAngle_DecreasesAngle", Test_Disabled_DecreaseAngle_DecreasesAngle), 
	new_TestFixture("Test_Disabled_DecreaseAngle_DoesNotGoBelowMin", Test_Disabled_DecreaseAngle_DoesNotGoBelowMin), 
	new_TestFixture("Test_Disabled_TransitionsToInitializing", Test_Disabled_TransitionsToInitializing), 
	new_TestFixture("Test_Disabled_StaysDisabled_WhenNotInitializing", Test_Disabled_StaysDisabled_WhenNotInitializing), 
	new_TestFixture("Test_Disabled_IncreaseHasPriorityOverDecrease", Test_Disabled_IncreaseHasPriorityOverDecrease), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldControl_Disabled, "testSet_FieldControl_Disabled", setupTest, 0, fixtures, 0, 0, 0);

