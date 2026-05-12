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
	FieldControlFB.FieldControl = &FieldControlStruct;
	FieldControlFB.FieldMotor = &FieldMotorStruct;
	FieldControlFB.InclinoSensor = &InclinoSensorStruct;
	
	memset(FieldControlFB.FieldControl, 0, sizeof(*FieldControlFB.FieldControl));
	memset(FieldControlFB.FieldMotor, 0, sizeof(*FieldControlFB.FieldMotor));
	memset(FieldControlFB.InclinoSensor, 0, sizeof(*FieldControlFB.InclinoSensor));
	
	FieldControlFB.FieldControl->STS.StateInt = STATE_INITIALIZING;

	TEST_DONE;
}

_TEST Test_Initializing_TransitionsToIdle(void)
{
	FieldControlFB.FieldControl->STS.Idle = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldControlFB.FieldControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Initializing_SetsAtTargetPosition_WhenAligned(void)
{
	FieldControlFB.FieldControl->STS.Idle = 0;

	FieldControlFB.FieldControl->STS.CurrentAngle = 9.38;
	FieldControlFB.FieldControl->PAR.Angle = 10.0;

	FieldControlFB.FieldControl->STS.AtTargetPosition = 0;

	FieldControlFB.FieldMotor->STS.EndButtonHit = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(1, FieldControlFB.FieldControl->STS.AtTargetPosition);

	TEST_DONE;
}

_TEST Test_Initializing_DoesNotSetTarget_WhenAngleNotReached(void)
{
	FieldControlFB.FieldControl->STS.Idle = 0;

	FieldControlFB.FieldControl->STS.CurrentAngle = 1.0;
	FieldControlFB.FieldControl->PAR.Angle = 15.0;

	FieldControlFB.FieldControl->STS.AtTargetPosition = 0;

	FieldControlFB.FieldMotor->STS.EndButtonHit = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldControl->STS.AtTargetPosition);

	TEST_DONE;
}

_TEST Test_Initializing_DoesNotSetTarget_WhenAlreadyAtTarget(void)
{
	FieldControlFB.FieldControl->STS.Idle = 0;

	FieldControlFB.FieldControl->STS.CurrentAngle = 10.0;
	FieldControlFB.FieldControl->PAR.Angle = 10.0;

	FieldControlFB.FieldControl->STS.AtTargetPosition = 1;

	FieldControlFB.FieldMotor->STS.EndButtonHit = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(1, FieldControlFB.FieldControl->STS.AtTargetPosition);

	TEST_DONE;
}

_TEST Test_Initializing_DoesNotSetTarget_WithoutEndButton(void)
{
	FieldControlFB.FieldControl->STS.Idle = 0;

	FieldControlFB.FieldControl->STS.CurrentAngle = 10.0;
	FieldControlFB.FieldControl->PAR.Angle = 10.0;

	FieldControlFB.FieldControl->STS.AtTargetPosition = 0;

	FieldControlFB.FieldMotor->STS.EndButtonHit = 0;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldControl->STS.AtTargetPosition);

	TEST_DONE;
}

_TEST Test_Initializing_IdleHasPriorityOverAlignment(void)
{
	FieldControlFB.FieldControl->STS.Idle = 1;

	FieldControlFB.FieldControl->STS.CurrentAngle = 10.0;
	FieldControlFB.FieldControl->PAR.Angle = 10.0;

	FieldControlFB.FieldControl->STS.AtTargetPosition = 0;

	FieldControlFB.FieldMotor->STS.EndButtonHit = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_IDLE, FieldControlFB.FieldControl->STS.StateInt);
	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldControl->STS.AtTargetPosition);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 13:11:07Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Initializing_TransitionsToIdle", Test_Initializing_TransitionsToIdle), 
	new_TestFixture("Test_Initializing_SetsAtTargetPosition_WhenAligned", Test_Initializing_SetsAtTargetPosition_WhenAligned), 
	new_TestFixture("Test_Initializing_DoesNotSetTarget_WhenAngleNotReached", Test_Initializing_DoesNotSetTarget_WhenAngleNotReached), 
	new_TestFixture("Test_Initializing_DoesNotSetTarget_WhenAlreadyAtTarget", Test_Initializing_DoesNotSetTarget_WhenAlreadyAtTarget), 
	new_TestFixture("Test_Initializing_DoesNotSetTarget_WithoutEndButton", Test_Initializing_DoesNotSetTarget_WithoutEndButton), 
	new_TestFixture("Test_Initializing_IdleHasPriorityOverAlignment", Test_Initializing_IdleHasPriorityOverAlignment), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldControl_Initializing, "testSet_FieldControl_Initializing", setupTest, 0, fixtures, 0, 0, 0);

