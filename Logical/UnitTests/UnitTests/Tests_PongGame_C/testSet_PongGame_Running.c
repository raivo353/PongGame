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
	
	PongGameFB.PongGame->STS.StateInt = STATE_RUNNING;

	TEST_DONE;
}

_TEST Test_Running_SetsStateString(void)
{
	PongGameFB.BallControl->STS.ShootCycleCompleted = 0;
	PongGameFB.BallControl->STS.GameOver = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_STRING("Running", PongGameFB.PongGame->STS.StateString);

	TEST_DONE;
}

_TEST Test_Running_IncrementsScore_OnShootCycleCompleted(void)
{
	PongGameFB.PongGame->PAR.Score = 10;

	PongGameFB.BallControl->STS.ShootCycleCompleted = 1;
	PongGameFB.BallControl->STS.GameOver = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(11, PongGameFB.PongGame->PAR.Score);

	TEST_DONE;
}

_TEST Test_Running_DoesNotIncrementScore_WhenNoCycleCompleted(void)
{
	PongGameFB.PongGame->PAR.Score = 10;

	PongGameFB.BallControl->STS.ShootCycleCompleted = 0;
	PongGameFB.BallControl->STS.GameOver = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(10, PongGameFB.PongGame->PAR.Score);

	TEST_DONE;
}

_TEST Test_Running_GameOver_SetsStopGame(void)
{
	PongGameFB.BallControl->STS.GameOver = 1;
	PongGameFB.BallControl->STS.ShootCycleCompleted = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(1, PongGameFB.PongGame->CS.StopGame);

	TEST_DONE;
}

_TEST Test_Running_NoGameOver_DoesNotStopGame(void)
{
	PongGameFB.PongGame->CS.StopGame = 0;

	PongGameFB.BallControl->STS.GameOver = 0;
	PongGameFB.BallControl->STS.ShootCycleCompleted = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->CS.StopGame);

	TEST_DONE;
}

_TEST Test_Running_BothEvents_ScoreAndStop(void)
{
	PongGameFB.PongGame->PAR.Score = 5;
	PongGameFB.PongGame->CS.StopGame = 0;

	PongGameFB.BallControl->STS.ShootCycleCompleted = 1;
	PongGameFB.BallControl->STS.GameOver = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(6, PongGameFB.PongGame->PAR.Score);
	TEST_ASSERT_EQUAL_INT(1, PongGameFB.PongGame->CS.StopGame);

	TEST_DONE;
}

_TEST Test_Running_StopGame_TransitionsToStopping(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;
	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_StopGame_CS_TransitionsToStopping(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;
	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_StopGame_HMI_TransitionsToStopping(void)
{
	PongGameFB.PongGame->HMI.StopGame = 1;
	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_StopGame_BlockedByInterlock(void)
{
	PongGameFB.PongGame->CS.StopGame = 1;
	PongGameFB.PongGame->STS.AlarmActive = 0;
	PongGameFB.PongGame->STS.Interlocked = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, PongGameFB.PongGame->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_XOR_Start_Command(void)
{
	PongGameFB.PongGame->HMI.Start = 1;
	PongGameFB.PongGame->CS.Start = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.BallControl->CS.Start);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.FieldControl->CS.Start);

	TEST_DONE;
}

_TEST Test_Running_XOR_Start_HMI_Only(void)
{
	PongGameFB.PongGame->HMI.Start = 1;
	PongGameFB.PongGame->CS.Start = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(1, PongGameFB.BallControl->CS.Start);
	TEST_ASSERT_EQUAL_INT(1, PongGameFB.FieldControl->CS.Start);

	TEST_DONE;
}

_TEST Test_Running_XOR_StopGame_Conflict(void)
{
	PongGameFB.PongGame->HMI.StopGame = 1;
	PongGameFB.PongGame->CS.StopGame = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.BallControl->CS.StopGame);
	TEST_ASSERT_EQUAL_INT(0, PongGameFB.FieldControl->CS.StopGame);

	TEST_DONE;
}

_TEST Test_Running_SubsystemMapping_True(void)
{
	PongGameFB.BallControl->STS.Running = 1;
	PongGameFB.FieldControl->STS.Running = 1;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(1, PongGameFB.PongGame->STS.Running);

	TEST_DONE;
}

_TEST Test_Running_SubsystemMapping_False(void)
{
	PongGameFB.BallControl->STS.Running = 1;
	PongGameFB.FieldControl->STS.Running = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(0, PongGameFB.PongGame->STS.Running);

	TEST_DONE;
}

_TEST Test_Running_Interlock_Propagation(void)
{
	PongGameFB.BallControl->STS.Interlocked = 1;
	PongGameFB.FieldControl->STS.Interlocked = 0;

	FB_PongGame(&PongGameFB);

	TEST_ASSERT_EQUAL_INT(1, PongGameFB.PongGame->STS.Interlocked);

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
	new_TestFixture("Test_Running_SetsStateString", Test_Running_SetsStateString), 
	new_TestFixture("Test_Running_IncrementsScore_OnShootCycleCompleted", Test_Running_IncrementsScore_OnShootCycleCompleted), 
	new_TestFixture("Test_Running_DoesNotIncrementScore_WhenNoCycleCompleted", Test_Running_DoesNotIncrementScore_WhenNoCycleCompleted), 
	new_TestFixture("Test_Running_GameOver_SetsStopGame", Test_Running_GameOver_SetsStopGame), 
	new_TestFixture("Test_Running_NoGameOver_DoesNotStopGame", Test_Running_NoGameOver_DoesNotStopGame), 
	new_TestFixture("Test_Running_BothEvents_ScoreAndStop", Test_Running_BothEvents_ScoreAndStop), 
	new_TestFixture("Test_Running_StopGame_TransitionsToStopping", Test_Running_StopGame_TransitionsToStopping), 
	new_TestFixture("Test_Running_StopGame_CS_TransitionsToStopping", Test_Running_StopGame_CS_TransitionsToStopping), 
	new_TestFixture("Test_Running_StopGame_HMI_TransitionsToStopping", Test_Running_StopGame_HMI_TransitionsToStopping), 
	new_TestFixture("Test_Running_StopGame_BlockedByInterlock", Test_Running_StopGame_BlockedByInterlock), 
	new_TestFixture("Test_Running_XOR_Start_Command", Test_Running_XOR_Start_Command), 
	new_TestFixture("Test_Running_XOR_Start_HMI_Only", Test_Running_XOR_Start_HMI_Only), 
	new_TestFixture("Test_Running_XOR_StopGame_Conflict", Test_Running_XOR_StopGame_Conflict), 
	new_TestFixture("Test_Running_SubsystemMapping_True", Test_Running_SubsystemMapping_True), 
	new_TestFixture("Test_Running_SubsystemMapping_False", Test_Running_SubsystemMapping_False), 
	new_TestFixture("Test_Running_Interlock_Propagation", Test_Running_Interlock_Propagation), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PongGame_Running, "testSet_PongGame_Running", setupTest, 0, fixtures, 0, 0, 0);

