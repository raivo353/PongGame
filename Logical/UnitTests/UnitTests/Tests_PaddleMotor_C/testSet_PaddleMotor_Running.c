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
	PaddleMotorFB.PaddleMotor = &PaddleMotorStruct;

	// volledige reset van alles
	memset(PaddleMotorFB.PaddleMotor, 0, sizeof(*PaddleMotorFB.PaddleMotor));

	// minimale state voor RUNNING tests
	PaddleMotorFB.PaddleMotor->STS.StateInt = STATE_RUNNING;

	TEST_DONE;
}

_TEST test_Running_SetsFlagsCorrectly(void)
{
	PaddleMotorFB.PaddleMotor->STS.Idle = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.Running);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.Idle);

	TEST_DONE;
}

_TEST test_Running_ManualMode_StopsJogging(void)
{
	PaddleMotorFB.PaddleMotor->CS.AutoMode = 0;

	PaddleMotorFB.PaddleMotor->CS.MoveJogNeg = 1;
	PaddleMotorFB.PaddleMotor->CS.MoveJogPos = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST test_Running_IncreaseJogSpeed(void)
{
	PaddleMotorFB.PaddleMotor->CS.AutoMode = 0;

	PaddleMotorFB.PaddleMotor->PAR.JogVelocity = 500;
	PaddleMotorFB.PaddleMotor->HMI.IncreaseJogSpeed = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(501, PaddleMotorFB.PaddleMotor->PAR.JogVelocity);

	TEST_DONE;
}

_TEST test_Running_DecreaseJogSpeed(void)
{
	PaddleMotorFB.PaddleMotor->CS.AutoMode = 0;

	PaddleMotorFB.PaddleMotor->PAR.JogVelocity = 500;
	PaddleMotorFB.PaddleMotor->HMI.DecreaseJogSpeed = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(499, PaddleMotorFB.PaddleMotor->PAR.JogVelocity);

	TEST_DONE;
}

_TEST test_Running_AutoMode_ResetsHMIInputs(void)
{
	PaddleMotorFB.PaddleMotor->STS.AutoActive = 1;

	PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg = 1;
	PaddleMotorFB.PaddleMotor->HMI.MoveJogPos = 1;
	PaddleMotorFB.PaddleMotor->HMI.MoveAbsolute = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->HMI.MoveAbsolute);

	TEST_DONE;
}

_TEST test_Running_LowerLimitProtection(void)
{
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 5000;
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 1000;
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogNeg);

	TEST_DONE;
}

_TEST test_Running_UpperLimitProtection_EndButton(void)
{
	PaddleMotorFB.digitalInput = 0x1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST test_Running_UpperLimitProtection_Position(void)
{
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 5000;
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 4900;
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST test_Running_StoppingOffset_HighVelocityLimitsMovement(void)
{
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 5000;

	// Hoge snelheid ? grote stopping offset
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 1000;

	// Dicht bij ondergrens
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 2300;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogNeg);

	TEST_DONE;
}

_TEST test_Running_LowerLimit_AdjustsTargetPosition(void)
{
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 5000;
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 0;

	// Onder minimum grens
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 1000;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(PaddleMotorFB.PaddleMotor->STS.ActPosition + 100, PaddleMotorFB.PaddleMotor->PAR.Position);

	TEST_DONE;
}

_TEST test_Running_UpperLimit_AdjustsTargetPosition(void)
{
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 5000;
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 0;

	// Dicht bij bovengrens
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 4950;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(PaddleMotorFB.PaddleMotor->STS.ReferencePosition - 100, PaddleMotorFB.PaddleMotor->PAR.Position);

	TEST_DONE;
}

_TEST test_Running_EndButton_ForcesStopJogPos(void)
{
	// Activeer endbutton
	PaddleMotorFB.digitalInput = 0x1;

	PaddleMotorFB.PaddleMotor->CS.MoveJogPos = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST test_Running_StopGame_TransitionsToStopping(void)
{
	PaddleMotorFB.PaddleMotor->CS.StopGame = 1;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, PaddleMotorFB.PaddleMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Running_StoppingOffset_AffectsUpperLimit(void)
{
	PaddleMotorFB.PaddleMotor->STS.ReferencePosition = 5000;

	// Zonder velocity ? geen offset
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 0;
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 4900;

	FB_PaddleMotor(&PaddleMotorFB);

	int pos_no_offset = PaddleMotorFB.PaddleMotor->PAR.Position;

	// Reset situatie
	PaddleMotorFB.PaddleMotor->STS.ActVelocity = 1000;
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 4900;

	FB_PaddleMotor(&PaddleMotorFB);

	int pos_with_offset = PaddleMotorFB.PaddleMotor->PAR.Position;

	TEST_ASSERT(pos_with_offset <= pos_no_offset);

	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 08:15:55Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Running_SetsFlagsCorrectly", test_Running_SetsFlagsCorrectly), 
	new_TestFixture("test_Running_ManualMode_StopsJogging", test_Running_ManualMode_StopsJogging), 
	new_TestFixture("test_Running_IncreaseJogSpeed", test_Running_IncreaseJogSpeed), 
	new_TestFixture("test_Running_DecreaseJogSpeed", test_Running_DecreaseJogSpeed), 
	new_TestFixture("test_Running_AutoMode_ResetsHMIInputs", test_Running_AutoMode_ResetsHMIInputs), 
	new_TestFixture("test_Running_LowerLimitProtection", test_Running_LowerLimitProtection), 
	new_TestFixture("test_Running_UpperLimitProtection_EndButton", test_Running_UpperLimitProtection_EndButton), 
	new_TestFixture("test_Running_UpperLimitProtection_Position", test_Running_UpperLimitProtection_Position), 
	new_TestFixture("test_Running_StoppingOffset_HighVelocityLimitsMovement", test_Running_StoppingOffset_HighVelocityLimitsMovement), 
	new_TestFixture("test_Running_LowerLimit_AdjustsTargetPosition", test_Running_LowerLimit_AdjustsTargetPosition), 
	new_TestFixture("test_Running_UpperLimit_AdjustsTargetPosition", test_Running_UpperLimit_AdjustsTargetPosition), 
	new_TestFixture("test_Running_EndButton_ForcesStopJogPos", test_Running_EndButton_ForcesStopJogPos), 
	new_TestFixture("test_Running_StopGame_TransitionsToStopping", test_Running_StopGame_TransitionsToStopping), 
	new_TestFixture("test_Running_StoppingOffset_AffectsUpperLimit", test_Running_StoppingOffset_AffectsUpperLimit), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Running, "testSet_PaddleMotor_Running", setupTest, 0, fixtures, 0, 0, 0);

