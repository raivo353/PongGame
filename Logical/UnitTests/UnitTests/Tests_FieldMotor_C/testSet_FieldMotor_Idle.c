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
	FieldMotorFB.FieldMotor = &FieldMotorStruct;
	memset(	FieldMotorFB.FieldMotor, 0, sizeof(*FieldMotorFB.FieldMotor));
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_IDLE;

	TEST_DONE;
}

_TEST test_Idle_AllOutputsOff(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.Power);

	TEST_DONE;
}

_TEST test_Idle_StatusFlags(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.Idle);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Initializing);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Running);

	TEST_DONE;
}

_TEST test_Idle_NoTransitionWithoutStart(void)
{
	FieldMotorFB.FieldMotor->CS.Start = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_TransitionToRunning(void)
{
	FieldMotorFB.FieldMotor->CS.Start = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_BlockedByAlarm(void)
{
	FieldMotorFB.FieldMotor->CS.Start = 1;
	FieldMotorFB.FieldMotor->STS.AlarmActive = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_BlockedByInterlock(void)
{
	FieldMotorFB.FieldMotor->CS.Start = 1;
	FieldMotorFB.FieldMotor->STS.Interlocked = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 13:34:14Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Idle_AllOutputsOff", test_Idle_AllOutputsOff), 
	new_TestFixture("test_Idle_StatusFlags", test_Idle_StatusFlags), 
	new_TestFixture("test_Idle_NoTransitionWithoutStart", test_Idle_NoTransitionWithoutStart), 
	new_TestFixture("test_Idle_TransitionToRunning", test_Idle_TransitionToRunning), 
	new_TestFixture("test_Idle_BlockedByAlarm", test_Idle_BlockedByAlarm), 
	new_TestFixture("test_Idle_BlockedByInterlock", test_Idle_BlockedByInterlock), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldMotor_Idle, "testSet_FieldMotor_Idle", setupTest, 0, fixtures, 0, 0, 0);

