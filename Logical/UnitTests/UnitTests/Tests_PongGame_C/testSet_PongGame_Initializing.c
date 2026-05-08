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
	
	PongGameFB.PongGame->STS.StateInt = STATE_INITIALIZING;

	TEST_DONE;
}

_TEST Test_Initializing_SetsStateString(void)
{
	PongGameFB.PongGame->STS.Idle = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_STRING("Initializing...", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}

_TEST Test_Initializing_StaysWhenNotIdle(void)
{
	PongGameFB.PongGame->STS.Idle = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Initializing_TransitionsToIdle(void)
{
	PongGameFB.PongGame->STS.Idle = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Initializing_IdleHasPriority(void)
{
	PongGameFB.PongGame->STS.Idle = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PongGameFB.PongGame->STS.StateInt);
	TEST_ASSERT_EQUAL_STRING("Initializing...", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 13:54:36Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Initializing_SetsStateString", Test_Initializing_SetsStateString), 
	new_TestFixture("Test_Initializing_StaysWhenNotIdle", Test_Initializing_StaysWhenNotIdle), 
	new_TestFixture("Test_Initializing_TransitionsToIdle", Test_Initializing_TransitionsToIdle), 
	new_TestFixture("Test_Initializing_IdleHasPriority", Test_Initializing_IdleHasPriority), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PongGame_Initializing, "testSet_PongGame_Initializing", setupTest, 0, fixtures, 0, 0, 0);

