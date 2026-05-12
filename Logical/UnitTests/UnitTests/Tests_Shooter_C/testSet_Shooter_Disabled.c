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
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	TEST_DONE;
}

_TEST Test_Disabled_SetsDisabledState(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->STS.Disabled);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->STS.Idle);

	TEST_DONE;
}

_TEST Test_Disabled_ResetsHMICommands(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->HMI.EnableFan = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->HMI.Shoot);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->HMI.EnableFan);

	TEST_DONE;
}

_TEST Test_Disabled_ResetsControlCommands(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->CS.Shoot = 1;
	ShooterFB.Shooter->CS.EnableFan = 1;
	ShooterFB.Shooter->CS.Interlock = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->CS.Shoot);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->CS.EnableFan);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->CS.Interlock);

	TEST_DONE;
}

_TEST Test_Disabled_ResetsIOOutputs(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->IO.Shoot = 1;
	ShooterFB.Shooter->IO.EnableFan = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->IO.Shoot);
	TEST_ASSERT_EQUAL_INT(0, ShooterFB.Shooter->IO.EnableFan);

	TEST_DONE;
}

_TEST Test_Disabled_ResetsPhysicalOutputs(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->HMI.Shoot = 1;
	ShooterFB.Shooter->HMI.EnableFan = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(0, ShooterFB.digitalOutput);

	TEST_DONE;
}

_TEST Test_Disabled_TransitionsToIdle(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->CS.Start = 1;
	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_DoesNotTransitionWhenAlarmActive(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->CS.Start = 1;
	ShooterFB.Shooter->STS.AlarmActive = 1;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_DoesNotTransitionWhenInterlocked(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->CS.Start = 1;
	ShooterFB.Shooter->STS.AlarmActive = 0;
	ShooterFB.Shooter->STS.Interlocked = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_AlarmColourGreen(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(GREEN_COLOUR, ShooterFB.Shooter->STS.AlarmActiveColour);

	TEST_DONE;
}

_TEST Test_Disabled_AlarmColourRed(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;
	ShooterFB.Shooter->STS.Interlocked = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(RED_COLOUR, ShooterFB.Shooter->STS.AlarmActiveColour);

	TEST_DONE;
}

_TEST Test_Disabled_StopGameForcesDisabled(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->CS.StopGame = 1;
	ShooterFB.Shooter->STS.Interlocked = 0;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_StopGameBlockedByInterlock(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_IDLE;

	ShooterFB.Shooter->CS.StopGame = 1;
	ShooterFB.Shooter->STS.Interlocked = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, ShooterFB.Shooter->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_MapsAutoModeToAutoActive(void)
{
	ShooterFB.Shooter->STS.StateInt = STATE_DISABLED;

	ShooterFB.Shooter->CS.AutoMode = 1;

	FB_Shooter(&ShooterFB);

	TEST_ASSERT_EQUAL_INT(1, ShooterFB.Shooter->STS.AutoActive);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 09:17:24Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Disabled_SetsDisabledState", Test_Disabled_SetsDisabledState), 
	new_TestFixture("Test_Disabled_ResetsHMICommands", Test_Disabled_ResetsHMICommands), 
	new_TestFixture("Test_Disabled_ResetsControlCommands", Test_Disabled_ResetsControlCommands), 
	new_TestFixture("Test_Disabled_ResetsIOOutputs", Test_Disabled_ResetsIOOutputs), 
	new_TestFixture("Test_Disabled_ResetsPhysicalOutputs", Test_Disabled_ResetsPhysicalOutputs), 
	new_TestFixture("Test_Disabled_TransitionsToIdle", Test_Disabled_TransitionsToIdle), 
	new_TestFixture("Test_Disabled_DoesNotTransitionWhenAlarmActive", Test_Disabled_DoesNotTransitionWhenAlarmActive), 
	new_TestFixture("Test_Disabled_DoesNotTransitionWhenInterlocked", Test_Disabled_DoesNotTransitionWhenInterlocked), 
	new_TestFixture("Test_Disabled_AlarmColourGreen", Test_Disabled_AlarmColourGreen), 
	new_TestFixture("Test_Disabled_AlarmColourRed", Test_Disabled_AlarmColourRed), 
	new_TestFixture("Test_Disabled_StopGameForcesDisabled", Test_Disabled_StopGameForcesDisabled), 
	new_TestFixture("Test_Disabled_StopGameBlockedByInterlock", Test_Disabled_StopGameBlockedByInterlock), 
	new_TestFixture("Test_Disabled_MapsAutoModeToAutoActive", Test_Disabled_MapsAutoModeToAutoActive), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_Shooter_Disabled, "testSet_Shooter_Disabled", setupTest, 0, fixtures, 0, 0, 0);

