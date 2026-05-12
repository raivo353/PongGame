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
	BallControlFB.BallControl = &BallControlStruct;
	BallControlFB.DistanceSensorLeft = &DistanceSensorLeftStruct;
	BallControlFB.DistanceSensorMiddle = &DistanceSensorMiddleStruct;
	BallControlFB.DistanceSensorRight = &DistanceSensorRightStruct;
	BallControlFB.PaddleMotor = &PaddleMotorStruct;
	BallControlFB.Shooter = &ShooterStruct;
	
	memset(BallControlFB.BallControl, 0, sizeof(*BallControlFB.BallControl));
	memset(BallControlFB.DistanceSensorLeft, 0, sizeof(*BallControlFB.DistanceSensorLeft));
	memset(BallControlFB.DistanceSensorMiddle, 0, sizeof(*BallControlFB.DistanceSensorMiddle));
	memset(BallControlFB.DistanceSensorRight, 0, sizeof(*BallControlFB.DistanceSensorRight));
	memset(BallControlFB.PaddleMotor, 0, sizeof(*BallControlFB.PaddleMotor));
	memset(BallControlFB.Shooter, 0, sizeof(*BallControlFB.Shooter));
	
	BallControlFB.BallControl->STS.StateInt = STATE_IDLE;

	TEST_DONE;
}

_TEST Test_Idle_StaysIdle_WhenNotRunning(void)
{
	BallControlFB.BallControl->STS.Running = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_TransitionsToRunning_WhenRunningTrue(void)
{
	BallControlFB.BallControl->STS.Running = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_TransitionsOnlyOnRunningTrue(void)
{
	/* cycle 1: not running */
	BallControlFB.BallControl->STS.Running = 0;
	FB_BallControl(&BallControlFB);
	TEST_ASSERT_EQUAL_INT(STATE_IDLE, BallControlFB.BallControl->STS.StateInt);

	/* cycle 2: running becomes true */
	BallControlFB.BallControl->STS.Running = 1;
	FB_BallControl(&BallControlFB);
	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 12:26:03Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Idle_StaysIdle_WhenNotRunning", Test_Idle_StaysIdle_WhenNotRunning), 
	new_TestFixture("Test_Idle_TransitionsToRunning_WhenRunningTrue", Test_Idle_TransitionsToRunning_WhenRunningTrue), 
	new_TestFixture("Test_Idle_TransitionsOnlyOnRunningTrue", Test_Idle_TransitionsOnlyOnRunningTrue), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_BallControl_Idle, "testSet_BallControl_Idle", setupTest, 0, fixtures, 0, 0, 0);

