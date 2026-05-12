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
	
	BallControlFB.BallControl->STS.StateInt = STATE_INITIALIZING;

	TEST_DONE;
}

_TEST Test_Initializing_ResetsStates(void)
{
	BallControlFB.BallControl->STS.PrevShootState = 5;
	BallControlFB.BallControl->STS.ShootState = 10;
	BallControlFB.BallControl->STS.GameOver = 1;
	BallControlFB.BallControl->STS.FirstRun = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.PrevShootState);
	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.ShootState);
	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.GameOver);
	TEST_ASSERT_EQUAL_INT(1, BallControlFB.BallControl->STS.FirstRun);

	TEST_DONE;
}

_TEST Test_Initializing_TransitionsToIdle(void)
{
	BallControlFB.BallControl->STS.Idle = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Initializing_NoIdleStaysInState(void)
{;
	BallControlFB.BallControl->STS.Idle = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 12:20:57Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Initializing_ResetsStates", Test_Initializing_ResetsStates), 
	new_TestFixture("Test_Initializing_TransitionsToIdle", Test_Initializing_TransitionsToIdle), 
	new_TestFixture("Test_Initializing_NoIdleStaysInState", Test_Initializing_NoIdleStaysInState), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_BallControl_Initializing, "testSet_BallControl_Initializing", setupTest, 0, fixtures, 0, 0, 0);

