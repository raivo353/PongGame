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

#define ENDBUTTON_BITMASK 0x4

_SETUP_TEST(void)
{
	FieldMotorFB.FieldMotor = &FieldMotorStruct;
	memset(FieldMotorFB.FieldMotor, 0, sizeof(*FieldMotorFB.FieldMotor));
	FieldMotorFB.digitalInput = 0;
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_INITIALIZING;

	TEST_DONE;
}

_TEST test_Initializing_SetsPowerAndParameters(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->CS.Power);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.Stop);

	TEST_ASSERT_EQUAL_INT(MAX_ACC_DEC, FieldMotorFB.FieldMotor->PAR.Acceleration);
	TEST_ASSERT_EQUAL_INT(MAX_ACC_DEC, FieldMotorFB.FieldMotor->PAR.Deceleration);

	TEST_DONE;
}

_TEST test_Initializing_StartsHomingSequence(void)
{
	FieldMotorFB.digitalInput = ENDBUTTON_BITMASK;
	FieldMotorFB.FieldMotor->STS.EndButtonHit = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->CS.Home);
	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.TimerStarted);

	TEST_DONE;
}

_TEST test_Initializing_EndButtonHit_TriggersCentering(void)
{
	FieldMotorFB.digitalInput = 0;
	FieldMotorFB.FieldMotor->STS.EndButtonHit = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.EndButtonHit);
	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->CS.Home);
	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->CS.SetCenterPoint);

	TEST_DONE;
}

_TEST test_Initializing_TransitionsToIdle(void)
{
	FieldMotorFB.FieldMotor->STS.EndButtonHit = 1;
	FieldMotorFB.FieldMotor->STS.AtTargetPosition = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Initializing_BlockedByAlarm(void)
{
	FieldMotorFB.FieldMotor->STS.EndButtonHit = 1;
	FieldMotorFB.FieldMotor->STS.AtTargetPosition = 1;
	FieldMotorFB.FieldMotor->STS.AlarmActive = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Initializing_BlockedByInterlock(void)
{
	FieldMotorFB.FieldMotor->STS.EndButtonHit = 1;
	FieldMotorFB.FieldMotor->STS.AtTargetPosition = 1;
	FieldMotorFB.FieldMotor->STS.Interlocked = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 13:01:47Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Initializing_SetsPowerAndParameters", test_Initializing_SetsPowerAndParameters), 
	new_TestFixture("test_Initializing_StartsHomingSequence", test_Initializing_StartsHomingSequence), 
	new_TestFixture("test_Initializing_EndButtonHit_TriggersCentering", test_Initializing_EndButtonHit_TriggersCentering), 
	new_TestFixture("test_Initializing_TransitionsToIdle", test_Initializing_TransitionsToIdle), 
	new_TestFixture("test_Initializing_BlockedByAlarm", test_Initializing_BlockedByAlarm), 
	new_TestFixture("test_Initializing_BlockedByInterlock", test_Initializing_BlockedByInterlock), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldMotor_Initializing, "testSet_FieldMotor_Initializing", setupTest, 0, fixtures, 0, 0, 0);

