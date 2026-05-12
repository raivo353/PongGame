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
	
	PongGameFB.PongGame->STS.StateInt = STATE_STOPPING;

	TEST_DONE;
}

_TEST Test_Stopping_ResetsStopGame(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->CS.StopGame);

	TEST_DONE;
}

_TEST Test_Stopping_SetsStateString(void)
{
	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_STRING("Stopping...", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}

_TEST Test_Stopping_UpdatesHighscore_WhenScoreHigher(void)
{
	PongGameFB.PongGame->PAR.Score = 10;
	PongGameFB.PongGame->PAR.Highscore = 5;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(10, PongGameFB.PongGame->PAR.Highscore);

	TEST_DONE;
}

_TEST Test_Stopping_DoesNotUpdateHighscore_WhenScoreLower(void)
{
	PongGameFB.PongGame->PAR.Score = 5;
	PongGameFB.PongGame->PAR.Highscore = 10;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(10, PongGameFB.PongGame->PAR.Highscore);

	TEST_DONE;
}

_TEST Test_Stopping_TransitionsToDisabled(void)
{
	PongGameFB.PongGame->STS.Disabled = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_StaysStopping_WhenNotDisabled(void)
{
	PongGameFB.PongGame->STS.Disabled = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_FullFlow_UpdateAndTransition(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;
	PongGameFB.PongGame->PAR.Score = 12;
	PongGameFB.PongGame->PAR.Highscore = 10;

	PongGameFB.PongGame->STS.Disabled = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->CS.StopGame);
	TEST_ASSERT_EQUAL_INT(12, PongGameFB.PongGame->PAR.Highscore);
	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, PongGameFB.PongGame->STS.StateInt);

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
	new_TestFixture("Test_Stopping_ResetsStopGame", Test_Stopping_ResetsStopGame), 
	new_TestFixture("Test_Stopping_SetsStateString", Test_Stopping_SetsStateString), 
	new_TestFixture("Test_Stopping_UpdatesHighscore_WhenScoreHigher", Test_Stopping_UpdatesHighscore_WhenScoreHigher), 
	new_TestFixture("Test_Stopping_DoesNotUpdateHighscore_WhenScoreLower", Test_Stopping_DoesNotUpdateHighscore_WhenScoreLower), 
	new_TestFixture("Test_Stopping_TransitionsToDisabled", Test_Stopping_TransitionsToDisabled), 
	new_TestFixture("Test_Stopping_StaysStopping_WhenNotDisabled", Test_Stopping_StaysStopping_WhenNotDisabled), 
	new_TestFixture("Test_Stopping_FullFlow_UpdateAndTransition", Test_Stopping_FullFlow_UpdateAndTransition), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PongGame_Stopping, "testSet_PongGame_Stopping", setupTest, 0, fixtures, 0, 0, 0);

