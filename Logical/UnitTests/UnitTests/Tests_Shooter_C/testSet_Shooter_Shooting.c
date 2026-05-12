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
	ShooterFB.Shooter = &ShooterStruct;
	memset(	ShooterFB.Shooter, 0, sizeof(*ShooterFB.Shooter));
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	TEST_DONE;
}

_TEST Test_Shooting_SetsShootingState(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->STS.Shooting);

	TEST_DONE;
}

_TEST Test_Shooting_ReturnsToIdleWhenNoRequest(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->CS.Shoot = 0;
	ShooterFB.Shooter->HMI.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Shooting_DoesNotReturnToIdleWhenHMIRequestExists(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->CS.Shoot = 0;
	ShooterFB.Shooter->HMI.Shoot = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_SHOOTING, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Shooting_DoesNotReturnToIdleWhenCSRequestExists(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->CS.Shoot = 1;
	ShooterFB.Shooter->HMI.Shoot = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_SHOOTING, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Shooting_DoesNotReturnToIdleWhenAlarmActive(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->CS.Shoot = 0;
	ShooterFB.Shooter->HMI.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_SHOOTING, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Shooting_DoesNotReturnToIdleWhenInterlocked(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->CS.Shoot = 0;
	ShooterFB.Shooter->HMI.Shoot = 0;

	ShooterFB.Shooter->STS.Interlocked = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_SHOOTING, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Shooting_OutputNotUpdatedWhenUnsafe(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->STS.Interlocked = 1;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->IO.Shoot);

	TEST_DONE;
}

_TEST Test_Shooting_OutputMappingActiveWhenSafe(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_SHOOTING;

	ShooterFB.Shooter->STS.Interlocked = 0;
	ShooterFB.Shooter->STS.AlarmActive = 0;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->IO.Shoot);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 09:31:14Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Shooting_SetsShootingState", Test_Shooting_SetsShootingState), 
	new_TestFixture("Test_Shooting_ReturnsToIdleWhenNoRequest", Test_Shooting_ReturnsToIdleWhenNoRequest), 
	new_TestFixture("Test_Shooting_DoesNotReturnToIdleWhenHMIRequestExists", Test_Shooting_DoesNotReturnToIdleWhenHMIRequestExists), 
	new_TestFixture("Test_Shooting_DoesNotReturnToIdleWhenCSRequestExists", Test_Shooting_DoesNotReturnToIdleWhenCSRequestExists), 
	new_TestFixture("Test_Shooting_DoesNotReturnToIdleWhenAlarmActive", Test_Shooting_DoesNotReturnToIdleWhenAlarmActive), 
	new_TestFixture("Test_Shooting_DoesNotReturnToIdleWhenInterlocked", Test_Shooting_DoesNotReturnToIdleWhenInterlocked), 
	new_TestFixture("Test_Shooting_OutputNotUpdatedWhenUnsafe", Test_Shooting_OutputNotUpdatedWhenUnsafe), 
	new_TestFixture("Test_Shooting_OutputMappingActiveWhenSafe", Test_Shooting_OutputMappingActiveWhenSafe), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_Shooter_Shooting, "testSet_Shooter_Shooting", setupTest, 0, fixtures, 0, 0, 0);

