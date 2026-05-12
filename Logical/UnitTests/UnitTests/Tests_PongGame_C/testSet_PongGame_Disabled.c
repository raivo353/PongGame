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
	
	PongGameFB.PongGame->STS.StateInt = STATE_DISABLED;

	TEST_DONE;
}

_TEST Test_Disabled_ResetsRuntimeValues(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;
	PongGameFB.PongGame->HMI.StopGame = 0;

	PongGameFB.PongGame->STS.GameStopped = 1;
	PongGameFB.PongGame->PAR.Score = 99;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->STS.GameStopped);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->CS.StopGame);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->PAR.Score);

	TEST_DONE;
}

_TEST Test_Disabled_SetsStateString(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;
	PongGameFB.PongGame->HMI.StopGame = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_STRING("Disabled", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}

_TEST Test_Disabled_TransitionsToInitializing(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;
	PongGameFB.PongGame->HMI.StopGame = 0;

	PongGameFB.PongGame->STS.Initializing = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_StaysDisabled_WhenNotInitializing(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;
	PongGameFB.PongGame->HMI.StopGame = 0;

	PongGameFB.PongGame->STS.Initializing = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_OverwriteExistingValues(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;
	PongGameFB.PongGame->HMI.StopGame = 0;

	PongGameFB.PongGame->STS.GameStopped = 1;
	PongGameFB.PongGame->PAR.Score = 1234;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->STS.GameStopped);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->CS.StopGame);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->PAR.Score);

	TEST_DONE;
}

_TEST Test_Disabled_StillResetsValues_BeforeInitializingTransition(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;
	PongGameFB.PongGame->HMI.StopGame = 0;

	PongGameFB.PongGame->STS.GameStopped = 1;
	PongGameFB.PongGame->PAR.Score = 50;

	PongGameFB.PongGame->STS.Initializing = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->STS.GameStopped);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->CS.StopGame);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->PAR.Score);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_StopGame_TransitionsToStopping(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;

	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_HMIStopGame_TransitionsToStopping(void)
{
	PongGameFB.PongGame->HMI.StopGame = 1;

	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Disabled_StopGameBlockedByInterlock(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;

	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-08 07:49:02Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Disabled_ResetsRuntimeValues", Test_Disabled_ResetsRuntimeValues), 
	new_TestFixture("Test_Disabled_SetsStateString", Test_Disabled_SetsStateString), 
	new_TestFixture("Test_Disabled_TransitionsToInitializing", Test_Disabled_TransitionsToInitializing), 
	new_TestFixture("Test_Disabled_StaysDisabled_WhenNotInitializing", Test_Disabled_StaysDisabled_WhenNotInitializing), 
	new_TestFixture("Test_Disabled_OverwriteExistingValues", Test_Disabled_OverwriteExistingValues), 
	new_TestFixture("Test_Disabled_StillResetsValues_BeforeInitializingTransition", Test_Disabled_StillResetsValues_BeforeInitializingTransition), 
	new_TestFixture("Test_Disabled_StopGame_TransitionsToStopping", Test_Disabled_StopGame_TransitionsToStopping), 
	new_TestFixture("Test_Disabled_HMIStopGame_TransitionsToStopping", Test_Disabled_HMIStopGame_TransitionsToStopping), 
	new_TestFixture("Test_Disabled_StopGameBlockedByInterlock", Test_Disabled_StopGameBlockedByInterlock), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PongGame_Disabled, "testSet_PongGame_Disabled", setupTest, 0, fixtures, 0, 0, 0);

