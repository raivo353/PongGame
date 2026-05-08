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
	
	BallControlFB.BallControl->STS.StateInt = STATE_DISABLED;

	TEST_DONE;
}

_TEST Test_Disabled_ResetsShoot(void)
{
	BallControlFB.BallControl->CS.Shoot = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->CS.Shoot);

	TEST_DONE;
}

_TEST Test_Disabled_IntensityIncrease(void)
{
	BallControlFB.Shooter->HMI.IncreaseIntensity = 1;
	BallControlFB.Shooter->PAR.Intensity = 5;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT(BallControlFB.Shooter->PAR.Intensity > 5);

	TEST_DONE;
}

_TEST Test_Disabled_IntensityDecrease(void)
{
	BallControlFB.Shooter->HMI.DecreaseIntensity = 1;
	BallControlFB.Shooter->PAR.Intensity = 5;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT(BallControlFB.Shooter->PAR.Intensity < 5);

	TEST_DONE;
}

_TEST Test_Disabled_IntensityUpperLimit(void)
{
	BallControlFB.Shooter->HMI.IncreaseIntensity = 1;
	BallControlFB.Shooter->PAR.Intensity = MAX_INTENSITY;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(MAX_INTENSITY, BallControlFB.Shooter->PAR.Intensity);

	TEST_DONE;
}

_TEST Test_Disabled_IntensityLowerLimit(void)
{
	BallControlFB.Shooter->HMI.DecreaseIntensity = 1;
	BallControlFB.Shooter->PAR.Intensity = MIN_INTENSITY;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(MIN_INTENSITY, BallControlFB.Shooter->PAR.Intensity);

	TEST_DONE;
}

_TEST Test_Disabled_TransitionsToInitializing(void)
{
	BallControlFB.BallControl->STS.Initializing = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_NoTransitionWithoutInit(void)
{
	BallControlFB.BallControl->STS.Initializing = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_StopsOnlyShootCommand(void)
{
	BallControlFB.BallControl->CS.Shoot = 1;
	BallControlFB.BallControl->CS.AutoMode = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->CS.Shoot);
	TEST_ASSERT_EQUAL_INT(1, BallControlFB.BallControl->CS.AutoMode);

	TEST_DONE;
}




/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 11:56:27Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Disabled_ResetsShoot", Test_Disabled_ResetsShoot), 
	new_TestFixture("Test_Disabled_IntensityIncrease", Test_Disabled_IntensityIncrease), 
	new_TestFixture("Test_Disabled_IntensityDecrease", Test_Disabled_IntensityDecrease), 
	new_TestFixture("Test_Disabled_IntensityUpperLimit", Test_Disabled_IntensityUpperLimit), 
	new_TestFixture("Test_Disabled_IntensityLowerLimit", Test_Disabled_IntensityLowerLimit), 
	new_TestFixture("Test_Disabled_TransitionsToInitializing", Test_Disabled_TransitionsToInitializing), 
	new_TestFixture("Test_Disabled_NoTransitionWithoutInit", Test_Disabled_NoTransitionWithoutInit), 
	new_TestFixture("Test_Disabled_StopsOnlyShootCommand", Test_Disabled_StopsOnlyShootCommand), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_BallControl_Disabled, "testSet_BallControl_Disabled", setupTest, 0, fixtures, 0, 0, 0);

