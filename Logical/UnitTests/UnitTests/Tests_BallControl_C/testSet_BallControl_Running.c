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
	
	BallControlFB.BallControl->STS.StateInt = STATE_RUNNING;

	TEST_DONE;
}

_TEST Test_Running_AutoActive_SetsOutputs(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.PaddleMotor->CS.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(1, BallControlFB.Shooter->CS.EnableFan);
	TEST_ASSERT_EQUAL_INT(AUTOMODE_VELOCITY, BallControlFB.PaddleMotor->PAR.Velocity);

	TEST_DONE;
}

_TEST Test_Running_WhenAutoInactive_DisablesShoot(void)
{
	BallControlFB.BallControl->STS.AutoActive = 0;

	BallControlFB.BallControl->CS.Shoot = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->CS.Shoot);

	TEST_DONE;
}

_TEST Test_Running_State0_RightSensor_GoesToState5(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 0;
	BallControlFB.BallControl->STS.FirstRun = 1;

	BallControlFB.DistanceSensorRight->STS.BallDetected = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(5, BallControlFB.BallControl->STS.ShootState);
	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.FirstRun);

	TEST_DONE;
}

_TEST Test_Running_State10_MiddleSensor_GoesToState20(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 10;
	BallControlFB.DistanceSensorMiddle->STS.BallDetected = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(20, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_State20_LeftSensor_GoesToState30(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 20;
	BallControlFB.DistanceSensorLeft->STS.BallDetected = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(30, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_State30_FiresShootAndResets(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 30;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(1, BallControlFB.BallControl->CS.Shoot);
	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_FirstRun_OnlyResetsOnce(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 0;
	BallControlFB.BallControl->STS.FirstRun = 1;

	BallControlFB.DistanceSensorRight->STS.BallDetected = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.FirstRun);

	TEST_DONE;
}

_TEST Test_Running_State0_NoBallDetected_StaysInState0(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 0;
	BallControlFB.BallControl->STS.FirstRun = 1;

	BallControlFB.DistanceSensorRight->STS.BallDetected = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.ShootState);
	TEST_ASSERT_EQUAL_INT(1, BallControlFB.BallControl->STS.FirstRun);

	TEST_DONE;
}

_TEST Test_Running_State10_NoMiddleDetection_StaysInState10(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 10;

	BallControlFB.DistanceSensorMiddle->STS.BallDetected = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(10, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_State20_NoLeftDetection_StaysInState20(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.ShootState = 20;

	BallControlFB.DistanceSensorLeft->STS.BallDetected = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(20, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_State0_FirstRunFalse_DoesNotTriggerState5(void)
{
	BallControlFB.BallControl->STS.AutoActive = 1;

	BallControlFB.BallControl->STS.FirstRun = 0;
	BallControlFB.BallControl->STS.ShootState = 0;

	BallControlFB.DistanceSensorRight->STS.BallDetected = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(0, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_AutoInactive_DoesNotChangeShootState(void)
{
	BallControlFB.BallControl->STS.AutoActive = 0;

	BallControlFB.BallControl->STS.ShootState = 20;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(20, BallControlFB.BallControl->STS.ShootState);

	TEST_DONE;
}

_TEST Test_Running_StopGame_TransitionsToStopping(void)
{
	BallControlFB.BallControl->CS.StopGame = 1;

	BallControlFB.BallControl->STS.AlarmActive = 0;
	BallControlFB.BallControl->STS.Interlocked = 0;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_StopGame_WithInterlock_DoesNotStop(void)
{
	BallControlFB.BallControl->CS.StopGame = 1;

	BallControlFB.BallControl->STS.AlarmActive = 0;
	BallControlFB.BallControl->STS.Interlocked = 1;

	FB_BallControl(&BallControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, BallControlFB.BallControl->STS.StateInt);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-08 07:54:53Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Running_AutoActive_SetsOutputs", Test_Running_AutoActive_SetsOutputs), 
	new_TestFixture("Test_Running_WhenAutoInactive_DisablesShoot", Test_Running_WhenAutoInactive_DisablesShoot), 
	new_TestFixture("Test_Running_State0_RightSensor_GoesToState5", Test_Running_State0_RightSensor_GoesToState5), 
	new_TestFixture("Test_Running_State10_MiddleSensor_GoesToState20", Test_Running_State10_MiddleSensor_GoesToState20), 
	new_TestFixture("Test_Running_State20_LeftSensor_GoesToState30", Test_Running_State20_LeftSensor_GoesToState30), 
	new_TestFixture("Test_Running_State30_FiresShootAndResets", Test_Running_State30_FiresShootAndResets), 
	new_TestFixture("Test_Running_FirstRun_OnlyResetsOnce", Test_Running_FirstRun_OnlyResetsOnce), 
	new_TestFixture("Test_Running_State0_NoBallDetected_StaysInState0", Test_Running_State0_NoBallDetected_StaysInState0), 
	new_TestFixture("Test_Running_State10_NoMiddleDetection_StaysInState10", Test_Running_State10_NoMiddleDetection_StaysInState10), 
	new_TestFixture("Test_Running_State20_NoLeftDetection_StaysInState20", Test_Running_State20_NoLeftDetection_StaysInState20), 
	new_TestFixture("Test_Running_State0_FirstRunFalse_DoesNotTriggerState5", Test_Running_State0_FirstRunFalse_DoesNotTriggerState5), 
	new_TestFixture("Test_Running_AutoInactive_DoesNotChangeShootState", Test_Running_AutoInactive_DoesNotChangeShootState), 
	new_TestFixture("Test_Running_StopGame_TransitionsToStopping", Test_Running_StopGame_TransitionsToStopping), 
	new_TestFixture("Test_Running_StopGame_WithInterlock_DoesNotStop", Test_Running_StopGame_WithInterlock_DoesNotStop), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_BallControl_Running, "testSet_BallControl_Running", setupTest, 0, fixtures, 0, 0, 0);

