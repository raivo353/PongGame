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
	PaddleMotorFB.PaddleMotor->STS.StateInt = STATE_STOPPING;

	TEST_DONE;
}

_TEST test_Stopping_AllCommandsReset(void)
{
	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.Stop);

	TEST_DONE;
}

_TEST test_Stopping_RemainsInState_WhenNotStandStill(void)
{
	PaddleMotorFB.PaddleMotor->STS.StandStill = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Stopping_ToDisabled_WhenStandStill(void)
{
	PaddleMotorFB.PaddleMotor->STS.StandStill = 1;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Stopping_NoTransition_WhenInterlocked(void)
{
	PaddleMotorFB.PaddleMotor->STS.StandStill = 1;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Stopping_StopSignalAlwaysActive(void)
{
	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.Stop);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 12:04:37Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Stopping_AllCommandsReset", test_Stopping_AllCommandsReset), 
	new_TestFixture("test_Stopping_RemainsInState_WhenNotStandStill", test_Stopping_RemainsInState_WhenNotStandStill), 
	new_TestFixture("test_Stopping_ToDisabled_WhenStandStill", test_Stopping_ToDisabled_WhenStandStill), 
	new_TestFixture("test_Stopping_NoTransition_WhenInterlocked", test_Stopping_NoTransition_WhenInterlocked), 
	new_TestFixture("test_Stopping_StopSignalAlwaysActive", test_Stopping_StopSignalAlwaysActive), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Stopping, "testSet_PaddleMotor_Stopping", setupTest, 0, fixtures, 0, 0, 0);

