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
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	TEST_DONE;
}

_TEST Test_Idle_SetsIdleState(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->STS.Idle);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->STS.Disabled);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->STS.Shooting);

	TEST_DONE;
}

_TEST Test_Idle_ResetsInterlockCommand(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->CS.Interlock = 1;
	ShooterFB.Shooter->HMI.EnableFan = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->CS.Interlock);

	TEST_DONE;
}

_TEST Test_Idle_AutoModeResetsHMIShoot(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->STS.AutoActive = 1;
	ShooterFB.Shooter->HMI.Shoot = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->HMI.Shoot);

	TEST_DONE;
}

_TEST Test_Idle_InterlockSetWhenFanDisabled(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->STS.AutoActive = 0;
	ShooterFB.Shooter->HMI.EnableFan = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->CS.Interlock);

	TEST_DONE;
}

_TEST Test_Idle_NoInterlockWhenFanEnabled(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->STS.AutoActive = 0;
	ShooterFB.Shooter->HMI.EnableFan = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->CS.Interlock);

	TEST_DONE;
}

_TEST Test_Idle_ResetsShootCommand(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->STS.AutoActive = 0;
	ShooterFB.Shooter->CS.Shoot = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->CS.Shoot);

	TEST_DONE;
}

_TEST Test_Idle_TransitionsToShootingFromHMI(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_SHOOTING, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_TransitionsToShootingFromControl(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 0;
	ShooterFB.Shooter->CS.Shoot = 1;

	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 0;
	ShooterFB.Shooter->STS.AutoActive = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_SHOOTING, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_DoesNotTransitionWhenAlarmActive(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 1;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_DoesNotTransitionWhenInterlocked(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_SetsShootOutput(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->IO.Shoot);

	TEST_DONE;
}

_TEST Test_Idle_BlocksShootOutputWhenInterlocked(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	ShooterFB.Shooter->STS.Interlocked = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->IO.Shoot);

	TEST_DONE;
}

_TEST Test_Idle_BlocksShootOutputWhenAlarmActive(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->CS.Shoot = 0;

	ShooterFB.Shooter->STS.AlarmActive = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->IO.Shoot);

	TEST_DONE;
}

_TEST Test_Idle_EnableFanOutputMapping(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.EnableFan = 1;
	ShooterFB.Shooter->CS.EnableFan = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->IO.EnableFan);

	TEST_DONE;
}

_TEST Test_Idle_DigitalOutputMapping(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->HMI.EnableFan = 1;

	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT((1 << SHOOT_OUTPUT_BIT) | (1 << FAN_OUTPUT_BIT), ShooterFB.digitalOutput);

	TEST_DONE;
}

_TEST Test_Idle_MapsInterlockStatus(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->CS.Interlock = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->STS.Interlocked);

	TEST_DONE;
}

_TEST Test_Idle_MapsAutoModeToAutoActive(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->CS.AutoMode = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->STS.AutoActive);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 09:25:21Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Idle_SetsIdleState", Test_Idle_SetsIdleState), 
	new_TestFixture("Test_Idle_ResetsInterlockCommand", Test_Idle_ResetsInterlockCommand), 
	new_TestFixture("Test_Idle_AutoModeResetsHMIShoot", Test_Idle_AutoModeResetsHMIShoot), 
	new_TestFixture("Test_Idle_InterlockSetWhenFanDisabled", Test_Idle_InterlockSetWhenFanDisabled), 
	new_TestFixture("Test_Idle_NoInterlockWhenFanEnabled", Test_Idle_NoInterlockWhenFanEnabled), 
	new_TestFixture("Test_Idle_ResetsShootCommand", Test_Idle_ResetsShootCommand), 
	new_TestFixture("Test_Idle_TransitionsToShootingFromHMI", Test_Idle_TransitionsToShootingFromHMI), 
	new_TestFixture("Test_Idle_TransitionsToShootingFromControl", Test_Idle_TransitionsToShootingFromControl), 
	new_TestFixture("Test_Idle_DoesNotTransitionWhenAlarmActive", Test_Idle_DoesNotTransitionWhenAlarmActive), 
	new_TestFixture("Test_Idle_DoesNotTransitionWhenInterlocked", Test_Idle_DoesNotTransitionWhenInterlocked), 
	new_TestFixture("Test_Idle_SetsShootOutput", Test_Idle_SetsShootOutput), 
	new_TestFixture("Test_Idle_BlocksShootOutputWhenInterlocked", Test_Idle_BlocksShootOutputWhenInterlocked), 
	new_TestFixture("Test_Idle_BlocksShootOutputWhenAlarmActive", Test_Idle_BlocksShootOutputWhenAlarmActive), 
	new_TestFixture("Test_Idle_EnableFanOutputMapping", Test_Idle_EnableFanOutputMapping), 
	new_TestFixture("Test_Idle_DigitalOutputMapping", Test_Idle_DigitalOutputMapping), 
	new_TestFixture("Test_Idle_MapsInterlockStatus", Test_Idle_MapsInterlockStatus), 
	new_TestFixture("Test_Idle_MapsAutoModeToAutoActive", Test_Idle_MapsAutoModeToAutoActive), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_Shooter_Idle, "testSet_Shooter_Idle", setupTest, 0, fixtures, 0, 0, 0);

