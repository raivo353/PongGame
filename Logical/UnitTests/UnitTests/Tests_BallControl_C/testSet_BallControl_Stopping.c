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
	
	BallControlFB.BallControl->STS.StateInt = STATE_STOPPING;

	TEST_DONE;
}

_TEST Test_Stopping_StaysInStopping_WhenNotDisabled(void)
{
	BallControlFB.BallControl->STS.StateInt = STATE_STOPPING;
	BallControlFB.BallControl->STS.Disabled = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_TransitionsToDisabled_WhenDisabledTrue(void)
{
	BallControlFB.BallControl->STS.StateInt = STATE_STOPPING;
	BallControlFB.BallControl->STS.Disabled = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 12:33:52Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Stopping_StaysInStopping_WhenNotDisabled", Test_Stopping_StaysInStopping_WhenNotDisabled), 
	new_TestFixture("Test_Stopping_TransitionsToDisabled_WhenDisabledTrue", Test_Stopping_TransitionsToDisabled_WhenDisabledTrue), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_BallControl_Stopping, "testSet_BallControl_Stopping", setupTest, 0, fixtures, 0, 0, 0);

