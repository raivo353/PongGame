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
	PongGameFB.PongGame = &PongGameStruct;
	PongGameFB.BallControl = &BallControlStruct;
	PongGameFB.FieldControl = &FieldControlStruct;
	
	memset(PongGameFB.PongGame, 0, sizeof(*PongGameFB.PongGame));
	memset(PongGameFB.BallControl, 0, sizeof(*PongGameFB.BallControl));
	memset(PongGameFB.FieldControl, 0, sizeof(*PongGameFB.FieldControl));
	
	PongGameFB.PongGame->STS.StateInt = STATE_IDLE;

	TEST_DONE;
}

_TEST Test_Idle_SetsStateString(void)
{
	PongGameFB.PongGame->STS.Running = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_STRING("Idle", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}

_TEST Test_Idle_StaysIdle_WhenNotRunning(void)
{
	PongGameFB.PongGame->STS.Running = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_TransitionsToRunning(void)
{
	PongGameFB.PongGame->STS.Running = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Idle_RunningOverridesIdleState(void)
{
	PongGameFB.PongGame->STS.Running = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, PongGameFB.PongGame->STS.StateInt);

	TEST_ASSERT_EQUAL_STRING("Idle", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 13:59:14Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Idle_SetsStateString", Test_Idle_SetsStateString), 
	new_TestFixture("Test_Idle_StaysIdle_WhenNotRunning", Test_Idle_StaysIdle_WhenNotRunning), 
	new_TestFixture("Test_Idle_TransitionsToRunning", Test_Idle_TransitionsToRunning), 
	new_TestFixture("Test_Idle_RunningOverridesIdleState", Test_Idle_RunningOverridesIdleState), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PongGame_Idle, "testSet_PongGame_Idle", setupTest, 0, fixtures, 0, 0, 0);

