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
	FieldMotorFB.FieldMotor->STS.StateInt = STATE_DISABLED;

	TEST_DONE;
}

_TEST test_Disabled_AllOutputsOff(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.Power);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.Home);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveJogPos);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->CS.MoveAbsolute);

	TEST_DONE;
}

_TEST test_Disabled_StatusFlags(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(1, FieldMotorFB.FieldMotor->STS.Disabled);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Initializing);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Running);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.Idle);

	TEST_DONE;
}

_TEST test_Disabled_InternalStateReset(void)
{
	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.EndButtonHit);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.TimerStarted);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.TimerEnded);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.ReferencePosition);
	TEST_ASSERT_EQUAL_INT(0, FieldMotorFB.FieldMotor->STS.AtTargetPosition);

	TEST_DONE;
}

_TEST test_Disabled_NoTransitionWithoutInit(void)
{
	FieldMotorFB.FieldMotor->CS.Initialize = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Disabled_TransitionsToInitializing(void)
{
	FieldMotorFB.FieldMotor->CS.Initialize = 1;
	FieldMotorFB.FieldMotor->STS.AlarmActive = 0;
	FieldMotorFB.FieldMotor->STS.Interlocked = 0;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_INITIALIZING, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Disabled_BlockedByAlarm(void)
{
	FieldMotorFB.FieldMotor->CS.Initialize = 1;
	FieldMotorFB.FieldMotor->STS.AlarmActive = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}

_TEST test_Disabled_BlockedByInterlock(void)
{
	FieldMotorFB.FieldMotor->CS.Initialize = 1;
	FieldMotorFB.FieldMotor->STS.Interlocked = 1;

	FB_FieldMotor(&FieldMotorFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, FieldMotorFB.FieldMotor->STS.StateInt);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 12:38:40Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_Disabled_AllOutputsOff", test_Disabled_AllOutputsOff), 
	new_TestFixture("test_Disabled_StatusFlags", test_Disabled_StatusFlags), 
	new_TestFixture("test_Disabled_InternalStateReset", test_Disabled_InternalStateReset), 
	new_TestFixture("test_Disabled_NoTransitionWithoutInit", test_Disabled_NoTransitionWithoutInit), 
	new_TestFixture("test_Disabled_TransitionsToInitializing", test_Disabled_TransitionsToInitializing), 
	new_TestFixture("test_Disabled_BlockedByAlarm", test_Disabled_BlockedByAlarm), 
	new_TestFixture("test_Disabled_BlockedByInterlock", test_Disabled_BlockedByInterlock), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldMotor_Disabled, "testSet_FieldMotor_Disabled", setupTest, 0, fixtures, 0, 0, 0);

