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

_TEST Test_Stopping_ResetsStateFlags(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FieldMotorFB.FieldMotor->STS.Running = 1;
	FieldMotorFB.FieldMotor->STS.Idle = 1;
	FieldMotorFB.FieldMotor->STS.Initializing = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Running);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Idle);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Initializing);

	TEST_DONE;
}

_TEST Test_Stopping_StopsAllMovement(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FieldMotorFB.FieldMotor->CS.MoveAbsolute = 1;
	FieldMotorFB.FieldMotor->CS.MoveJogNeg = 1;
	FieldMotorFB.FieldMotor->CS.MoveJogPos = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Stopping_SetsStopCommand(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FieldMotorFB.FieldMotor->CS.Stop = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->CS.Stop);

	TEST_DONE;
}

_TEST Test_Stopping_TransitionsToDisabled(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FieldMotorFB.FieldMotor->STS.StandStill = 1;
	FieldMotorFB.FieldMotor->STS.Interlocked = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_DoesNotTransitionWhenMoving(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FieldMotorFB.FieldMotor->STS.StandStill = 0;
	FieldMotorFB.FieldMotor->STS.Interlocked = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_DoesNotTransitionWhenInterlocked(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FieldMotorFB.FieldMotor->STS.StandStill = 1;
	FieldMotorFB.FieldMotor->STS.Interlocked = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_UpdatesStopOutput(void)
{
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_STOPPING;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->IO.Stop);

	TEST_DONE;
}


/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 09:05:51Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Stopping_ResetsStateFlags", Test_Stopping_ResetsStateFlags), 
	new_TestFixture("Test_Stopping_StopsAllMovement", Test_Stopping_StopsAllMovement), 
	new_TestFixture("Test_Stopping_SetsStopCommand", Test_Stopping_SetsStopCommand), 
	new_TestFixture("Test_Stopping_TransitionsToDisabled", Test_Stopping_TransitionsToDisabled), 
	new_TestFixture("Test_Stopping_DoesNotTransitionWhenMoving", Test_Stopping_DoesNotTransitionWhenMoving), 
	new_TestFixture("Test_Stopping_DoesNotTransitionWhenInterlocked", Test_Stopping_DoesNotTransitionWhenInterlocked), 
	new_TestFixture("Test_Stopping_UpdatesStopOutput", Test_Stopping_UpdatesStopOutput), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldMotor_Stopping, "testSet_FieldMotor_Stopping", setupTest, 0, fixtures, 0, 0, 0);

