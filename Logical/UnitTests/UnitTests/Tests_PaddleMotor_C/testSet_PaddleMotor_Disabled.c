/********************************************************************
 * COPYRIGHT - MyAutoMation-IT
 ********************************************************************
 * Program: -
 * Author:
 * Created: 
 ********************************************************************
 * Tests for ... 
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "Library.h"

#define STATE_DISABLED 0
#define STATE_INITIALIZING 10

_SETUP_TEST(void)
{
	/* TODO:  add code running before test set here */
	PaddleMotorFB.PaddleMotor = &PaddleMotorStruct;
	PaddleMotorFB.PaddleMotor->STS.StateInt = STATE_DISABLED;
	
	TEST_DONE;
}

_TEST test_Disabled_State_DefaultBehavior(void)
{
	PaddleMotorFB.digitalInput = 0;
	

	// Setting signals that have to be reset
	PaddleMotorFB.PaddleMotor->CS.Power = 1;
	PaddleMotorFB.PaddleMotor->CS.Home = 1;
	PaddleMotorFB.PaddleMotor->CS.MoveJogNeg = 1;
	PaddleMotorFB.PaddleMotor->CS.MoveJogPos = 1;
	PaddleMotorFB.PaddleMotor->CS.MoveAbsolute = 1;

	PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg = 1;
	PaddleMotorFB.PaddleMotor->HMI.MoveJogPos = 1;

	PaddleMotorFB.PaddleMotor->STS.TimerStarted = 1;
	PaddleMotorFB.PaddleMotor->STS.TimerEnded = 1;
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 1234;
	PaddleMotorFB.PaddleMotor->STS.ReferenceSet = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.Disabled);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.Power);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.Home);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveAbsolute);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveJogPos);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.TimerStarted);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.TimerEnded);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.ReferencePosition);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.ReferenceSet);

	TEST_DONE;
}

_TEST test_Disabled_NoInitialize_StaysDisabled(void)
{
	PaddleMotorFB.PaddleMotor->CS.Initialize = 0;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Disabled_ToInitializing(void)
{
	PaddleMotorFB.PaddleMotor->CS.Initialize = 1;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Disabled_NoTransition_WhenAlarm(void)
{
	PaddleMotorFB.PaddleMotor->CS.Initialize = 1;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 1;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Disabled_NoTransition_WhenInterlocked(void)
{
	PaddleMotorFB.PaddleMotor->CS.Initialize = 1;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 1;
	
	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}




/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-04-20 10:39:20Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Disabled_State_DefaultBehavior", test_Disabled_State_DefaultBehavior), 
	new_TestFixture("test_Disabled_NoInitialize_StaysDisabled", test_Disabled_NoInitialize_StaysDisabled), 
	new_TestFixture("test_Disabled_ToInitializing", test_Disabled_ToInitializing), 
	new_TestFixture("test_Disabled_NoTransition_WhenAlarm", test_Disabled_NoTransition_WhenAlarm), 
	new_TestFixture("test_Disabled_NoTransition_WhenInterlocked", test_Disabled_NoTransition_WhenInterlocked), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Disabled, "testSet_PaddleMotor_Disabled", setupTest, 0, fixtures, 0, 0, 0);

