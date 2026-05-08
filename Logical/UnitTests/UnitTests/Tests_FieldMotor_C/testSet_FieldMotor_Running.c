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
	FieldMotorFB.FieldMotor = &FieldMotorStruct;
	memset(	FieldMotorFB.FieldMotor, 0, sizeof(*FieldMotorFB.FieldMotor));
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_RUNNING;

	TEST_DONE;
}

_TEST Test_Running_SetsRunningAndPower(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.Running);
	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->CS.Power);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Idle);

	TEST_DONE;
}

_TEST Test_Running_ResetsMovementCommands(void)
{
	FieldMotorFB.FieldMotor->STS.AutoActive = 0;

	FieldMotorFB.FieldMotor->CS.MoveAbsolute = 1;
	FieldMotorFB.FieldMotor->CS.MoveJogNeg = 1;
	FieldMotorFB.FieldMotor->CS.MoveJogPos = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_IncreaseJogSpeed(void)
{
	FieldMotorFB.FieldMotor->STS.AutoActive = 0;

	FieldMotorFB.FieldMotor->PAR.JogVelocity = 10;
	FieldMotorFB.FieldMotor->HMI.IncreaseJogSpeed = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(11, FieldMotorFB.FieldMotor->PAR.JogVelocity);

	TEST_DONE;
}

_TEST Test_Running_MaxJogSpeedLimit(void)
{
	FieldMotorFB.FieldMotor->STS.AutoActive = 0;

	FieldMotorFB.FieldMotor->PAR.JogVelocity = MAX_VELOCITY;
	FieldMotorFB.FieldMotor->HMI.IncreaseJogSpeed = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(MAX_VELOCITY, FieldMotorFB.FieldMotor->PAR.JogVelocity);

	TEST_DONE;
}

_TEST Test_Running_DecreaseJogSpeed(void)
{
	FieldMotorFB.FieldMotor->STS.AutoActive = 0;

	FieldMotorFB.FieldMotor->PAR.JogVelocity = 1000;
	FieldMotorFB.FieldMotor->HMI.DecreaseJogSpeed = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(999, FieldMotorFB.FieldMotor->PAR.JogVelocity);

	TEST_DONE;
}

_TEST Test_Running_MinJogSpeedLimit(void)
{
	FieldMotorFB.FieldMotor->STS.AutoActive = 0;

	FieldMotorFB.FieldMotor->PAR.JogVelocity = MIN_VELOCITY;
	FieldMotorFB.FieldMotor->HMI.DecreaseJogSpeed = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(MIN_VELOCITY, FieldMotorFB.FieldMotor->PAR.JogVelocity);

	TEST_DONE;
}

_TEST Test_Running_AutoModeDisablesHMICommands(void)
{
	FieldMotorFB.FieldMotor->STS.AutoActive = 1;

	FieldMotorFB.FieldMotor->HMI.MoveAbsolute = 1;
	FieldMotorFB.FieldMotor->HMI.MoveJogNeg = 1;
	FieldMotorFB.FieldMotor->HMI.MoveJogPos = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->HMI.MoveAbsolute);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->HMI.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->HMI.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_EndButtonStopsPositiveMovement(void)
{
	FieldMotorFB.FieldMotor->IO.EndButton = 1;

	FieldMotorFB.FieldMotor->CS.MoveJogPos = 1;
	FieldMotorFB.FieldMotor->HMI.MoveJogPos = 1;
	FieldMotorFB.FieldMotor->CS.MoveAbsolute = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->HMI.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveAbsolute);

	TEST_DONE;
}

_TEST Test_Running_StopGameTransitionsToStopping(void)
{
	FieldMotorFB.FieldMotor->CS.StopGame = 1;
	FieldMotorFB.FieldMotor->STS.AlarmActive = 0;
	FieldMotorFB.FieldMotor->STS.Interlocked = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_StopBlockedByInterlock(void)
{
	FieldMotorFB.FieldMotor->CS.StopGame = 1;
	FieldMotorFB.FieldMotor->STS.Interlocked = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_RUNNING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Running_StandStillDetection(void)
{
	FieldMotorFB.FieldMotor->STS.ActVelocity = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.StandStill);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Moving);

	TEST_DONE;
}

_TEST Test_Running_MovingDetection(void)
{
	FieldMotorFB.FieldMotor->STS.ActVelocity = 100;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.StandStill);
	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.Moving);

	TEST_DONE;
}

_TEST Test_Running_XorMoveJogPos(void)
{
	FieldMotorFB.FieldMotor->CS.MoveJogPos = 0;
	FieldMotorFB.FieldMotor->HMI.MoveJogPos = 1;
	FieldMotorFB.digitalInput = ENDBUTTON_BITMASK_FIELD;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->IO.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_XorMoveJogPosBothHigh(void)
{
	FieldMotorFB.FieldMotor->CS.MoveJogPos = 1;
	FieldMotorFB.FieldMotor->HMI.MoveJogPos = 1;
	FieldMotorFB.digitalInput = ENDBUTTON_BITMASK_FIELD;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->IO.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_AlarmSourcePropagation(void)
{
	FieldMotorFB.FieldMotor->ALM.MotorError = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.AlarmActive);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-08 07:52:41Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Running_SetsRunningAndPower", Test_Running_SetsRunningAndPower), 
	new_TestFixture("Test_Running_ResetsMovementCommands", Test_Running_ResetsMovementCommands), 
	new_TestFixture("Test_Running_IncreaseJogSpeed", Test_Running_IncreaseJogSpeed), 
	new_TestFixture("Test_Running_MaxJogSpeedLimit", Test_Running_MaxJogSpeedLimit), 
	new_TestFixture("Test_Running_DecreaseJogSpeed", Test_Running_DecreaseJogSpeed), 
	new_TestFixture("Test_Running_MinJogSpeedLimit", Test_Running_MinJogSpeedLimit), 
	new_TestFixture("Test_Running_AutoModeDisablesHMICommands", Test_Running_AutoModeDisablesHMICommands), 
	new_TestFixture("Test_Running_EndButtonStopsPositiveMovement", Test_Running_EndButtonStopsPositiveMovement), 
	new_TestFixture("Test_Running_StopGameTransitionsToStopping", Test_Running_StopGameTransitionsToStopping), 
	new_TestFixture("Test_Running_StopBlockedByInterlock", Test_Running_StopBlockedByInterlock), 
	new_TestFixture("Test_Running_StandStillDetection", Test_Running_StandStillDetection), 
	new_TestFixture("Test_Running_MovingDetection", Test_Running_MovingDetection), 
	new_TestFixture("Test_Running_XorMoveJogPos", Test_Running_XorMoveJogPos), 
	new_TestFixture("Test_Running_XorMoveJogPosBothHigh", Test_Running_XorMoveJogPosBothHigh), 
	new_TestFixture("Test_Running_AlarmSourcePropagation", Test_Running_AlarmSourcePropagation), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldMotor_Running, "testSet_FieldMotor_Running", setupTest, 0, fixtures, 0, 0, 0);

