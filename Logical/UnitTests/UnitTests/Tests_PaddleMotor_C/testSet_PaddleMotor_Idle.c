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
	PaddleMotorFB.PaddleMotor = &PaddleMotorStruct;
	memset(PaddleMotorFB.PaddleMotor, 0, sizeof(*PaddleMotorFB.PaddleMotor));
	PaddleMotorFB.PaddleMotor->STS.StateInt = STATE_IDLE;
	
	TEST_DONE;
}

_TEST test_Idle_SetsStatusAndResetsOutputs(void)
{
	PaddleMotorFB.PaddleMotor->STS.Initializing = 1;
	PaddleMotorFB.PaddleMotor->STS.Idle = 0;

	PaddleMotorFB.PaddleMotor->CS.MoveAbsolute = 1;
	PaddleMotorFB.PaddleMotor->CS.MoveJogNeg = 1;
	PaddleMotorFB.PaddleMotor->CS.MoveJogPos = 1;

	PaddleMotorFB.PaddleMotor->HMI.MoveAbsolute = 1;
	PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg = 1;
	PaddleMotorFB.PaddleMotor->HMI.MoveJogPos = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.Initializing);
	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.Idle);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveJogPos);

	TEST_DONE;
}

_TEST test_Idle_RemainsIdleWithoutStart(void)
{
	PaddleMotorFB.PaddleMotor->CS.Start = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_ToRunning(void)
{
	PaddleMotorFB.PaddleMotor->CS.Start = 1;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_NoTransitionWhenAlarmActive(void)
{
	PaddleMotorFB.PaddleMotor->CS.Start = 1;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 1;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_NoTransitionWhenInterlocked(void)
{
	PaddleMotorFB.PaddleMotor->CS.Start = 1;
	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Idle_IOOutputsRemainZero(void)
{
	PaddleMotorFB.PaddleMotor->CS.MoveJogPos = 0;
	PaddleMotorFB.PaddleMotor->HMI.MoveJogPos = 1;

	PaddleMotorFB.PaddleMotor->CS.MoveJogNeg = 0;
	PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->IO.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->IO.MoveJogNeg);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 11:23:13Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Idle_SetsStatusAndResetsOutputs", test_Idle_SetsStatusAndResetsOutputs), 
	new_TestFixture("test_Idle_RemainsIdleWithoutStart", test_Idle_RemainsIdleWithoutStart), 
	new_TestFixture("test_Idle_ToRunning", test_Idle_ToRunning), 
	new_TestFixture("test_Idle_NoTransitionWhenAlarmActive", test_Idle_NoTransitionWhenAlarmActive), 
	new_TestFixture("test_Idle_NoTransitionWhenInterlocked", test_Idle_NoTransitionWhenInterlocked), 
	new_TestFixture("test_Idle_IOOutputsRemainZero", test_Idle_IOOutputsRemainZero), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Idle, "testSet_PaddleMotor_Idle", setupTest, 0, fixtures, 0, 0, 0);

