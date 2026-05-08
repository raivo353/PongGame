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
	
	FieldControlFB.FieldControl->STS.StateInt = STATE_IDLE;

	TEST_DONE;
}

_TEST Test_Idle_StaysIdle_WhenNotRunning(void)
{
	FieldControlFB.FieldControl->STS.Running = 0;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldControlFB.FieldControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_TransitionsToRunning(void)
{
	FieldControlFB.FieldControl->STS.Running = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, FieldControlFB.FieldControl->STS.StateInt);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 13:23:22Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Idle_StaysIdle_WhenNotRunning", Test_Idle_StaysIdle_WhenNotRunning), 
	new_TestFixture("Test_Idle_TransitionsToRunning", Test_Idle_TransitionsToRunning), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldControl_Idle, "testSet_FieldControl_Idle", setupTest, 0, fixtures, 0, 0, 0);

