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

#define MIDDLE_POSITION 1450
#define ENDBUTTON_BITMASK 0x2


_SETUP_TEST(void)
{
	PaddleMotorFB.PaddleMotor = &PaddleMotorStruct;
	memset(PaddleMotorFB.PaddleMotor, 0, sizeof(*PaddleMotorFB.PaddleMotor));
	PaddleMotorFB.PaddleMotor->STS.StateInt = STATE_INITIALIZING;

	TEST_DONE;
}

_TEST test_Initializing_SetsParameters(void)
{
	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.Initializing);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->STS.Disabled);

	TEST_ASSERT_EQUAL_INT(MAX_ACC_DEC, PaddleMotorFB.PaddleMotor->PAR.Acceleration);
	TEST_ASSERT_EQUAL_INT(MAX_ACC_DEC, PaddleMotorFB.PaddleMotor->PAR.Deceleration);
	TEST_ASSERT_EQUAL_INT(1000, PaddleMotorFB.PaddleMotor->PAR.JogVelocity);
	TEST_ASSERT_EQUAL_INT(1000, PaddleMotorFB.PaddleMotor->PAR.Velocity);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.Power);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.Stop);

	TEST_DONE;
}

_TEST test_Initializing_StartsHoming(void)
{
	PaddleMotorFB.digitalInput = 0; // EndButton = inactive

	PaddleMotorFB.PaddleMotor->STS.EndButtonHit = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.Home);
	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.TimerStarted);

	TEST_DONE;
}

_TEST test_Initializing_EndButtonHit(void)
{
	PaddleMotorFB.digitalInput = 0x1;

	PaddleMotorFB.PaddleMotor->STS.EndButtonHit = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.EndButtonHit);
	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.Home);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveJogPos);

	TEST_DONE;
}

_TEST test_Initializing_ToIdle(void)
{
	PaddleMotorFB.PaddleMotor->STS.EndButtonHit = 1;
	PaddleMotorFB.PaddleMotor->STS.TimerEnded = 1;
	PaddleMotorFB.PaddleMotor->STS.ReferenceSet = 1;

	PaddleMotorFB.PaddleMotor->PAR.Position = 3000;
	PaddleMotorFB.PaddleMotor->STS.ActPosition = 3000;

	PaddleMotorFB.PaddleMotor->STS.AlarmActive = 0;
	PaddleMotorFB.PaddleMotor->STS.Interlocked = 0;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, PaddleMotorFB.PaddleMotor->STS.StateInt);
	TEST_ASSERT_EQUAL_INT(0, PaddleMotorFB.PaddleMotor->CS.MoveAbsolute);

	TEST_DONE;
}

_TEST test_Initializing_ReferencePosition(void)
{
	PaddleMotorFB.PaddleMotor->STS.EndButtonHit = 1;
	PaddleMotorFB.PaddleMotor->STS.TimerEnded = 1;
	PaddleMotorFB.PaddleMotor->STS.ReferenceSet = 0;

	PaddleMotorFB.PaddleMotor->STS.ActPosition = 5000;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(
		PaddleMotorFB.PaddleMotor->STS.ActPosition + 25,
		PaddleMotorFB.PaddleMotor->STS.ReferencePosition
		);

	TEST_DONE;
}

_TEST test_Initializing_StartMoveAbsolute(void)
{
	PaddleMotorFB.PaddleMotor->STS.EndButtonHit = 1;
	PaddleMotorFB.PaddleMotor->STS.TimerEnded = 1;
	PaddleMotorFB.PaddleMotor->STS.ReferenceSet = 0;

	PaddleMotorFB.PaddleMotor->STS.ActPosition = 4000;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.MoveAbsolute);

	TEST_DONE;
}

_TEST test_Initializing_TargetPosition(void)
{
	PaddleMotorFB.PaddleMotor->STS.EndButtonHit = 1;
	PaddleMotorFB.PaddleMotor->STS.TimerEnded = 1;
	PaddleMotorFB.PaddleMotor->STS.ReferenceSet = 0;

	PaddleMotorFB.PaddleMotor->STS.ActPosition = 5000;

	FB_PaddleMotor(&PaddleMotorFB);

	TEST_ASSERT_EQUAL_INT(
		PaddleMotorFB.PaddleMotor->STS.ReferencePosition - MIDDLE_POSITION,
		PaddleMotorFB.PaddleMotor->PAR.Position
		);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 11:41:13Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Initializing_SetsParameters", test_Initializing_SetsParameters), 
	new_TestFixture("test_Initializing_StartsHoming", test_Initializing_StartsHoming), 
	new_TestFixture("test_Initializing_EndButtonHit", test_Initializing_EndButtonHit), 
	new_TestFixture("test_Initializing_ToIdle", test_Initializing_ToIdle), 
	new_TestFixture("test_Initializing_ReferencePosition", test_Initializing_ReferencePosition), 
	new_TestFixture("test_Initializing_StartMoveAbsolute", test_Initializing_StartMoveAbsolute), 
	new_TestFixture("test_Initializing_TargetPosition", test_Initializing_TargetPosition), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Initializing, "testSet_PaddleMotor_Initializing", setupTest, 0, fixtures, 0, 0, 0);

