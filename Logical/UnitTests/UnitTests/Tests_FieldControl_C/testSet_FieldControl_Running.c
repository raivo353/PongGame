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
	
	FieldControlFB.FieldControl->STS.StateInt = STATE_RUNNING;

	TEST_DONE;
}

_TEST Test_Running_ResetsStopCommand(void)
{
	FieldControlFB.FieldMotor->CS.Stop = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldMotor->CS.Stop);

	TEST_DONE;
}

_TEST Test_Running_DisablesJogNeg_WhenAtMaxAngle(void)
{
	FieldControlFB.FieldControl->STS.CurrentAngle = MAX_ANGLE;

	FieldControlFB.FieldMotor->HMI.MoveJogNeg = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldMotor->HMI.MoveJogNeg);

	TEST_DONE;
}

_TEST Test_Running_DisablesJogNeg_WhenAboveMaxAngle(void)
{
	FieldControlFB.FieldControl->STS.CurrentAngle = 25.0;

	FieldControlFB.FieldMotor->HMI.MoveJogNeg = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldMotor->HMI.MoveJogNeg);

	TEST_DONE;
}

_TEST Test_Running_DisablesJogPos_WhenAtMinAngle(void)
{
	FieldControlFB.FieldControl->STS.CurrentAngle = MIN_ANGLE;

	FieldControlFB.FieldMotor->HMI.MoveJogPos = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldMotor->HMI.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_DisablesJogPos_WhenBelowMinAngle(void)
{
	FieldControlFB.FieldControl->STS.CurrentAngle = 0.0;

	FieldControlFB.FieldMotor->HMI.MoveJogPos = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldMotor->HMI.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_DoesNotChangeJogCommands_WithinLimits(void)
{
	FieldControlFB.FieldControl->STS.CurrentAngle = 10.0;

	FieldControlFB.FieldMotor->HMI.MoveJogNeg = 1;
	FieldControlFB.FieldMotor->HMI.MoveJogPos = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(1, FieldControlFB.FieldMotor->HMI.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(1, FieldControlFB.FieldMotor->HMI.MoveJogPos);

	TEST_DONE;
}

_TEST Test_Running_MaxAngle_DoesNotChangeJogPos(void)
{
	FieldControlFB.FieldControl->STS.CurrentAngle = MAX_ANGLE;

	FieldControlFB.FieldMotor->HMI.MoveJogNeg = 1;
	FieldControlFB.FieldMotor->HMI.MoveJogPos = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(0, FieldControlFB.FieldMotor->HMI.MoveJogNeg);
	TEST_ASSERT_EQUAL_INT(1, FieldControlFB.FieldMotor->HMI.MoveJogPos);

	TEST_DONE;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-07 13:23:22Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Test_Running_ResetsStopCommand", Test_Running_ResetsStopCommand), 
	new_TestFixture("Test_Running_DisablesJogNeg_WhenAtMaxAngle", Test_Running_DisablesJogNeg_WhenAtMaxAngle), 
	new_TestFixture("Test_Running_DisablesJogNeg_WhenAboveMaxAngle", Test_Running_DisablesJogNeg_WhenAboveMaxAngle), 
	new_TestFixture("Test_Running_DisablesJogPos_WhenAtMinAngle", Test_Running_DisablesJogPos_WhenAtMinAngle), 
	new_TestFixture("Test_Running_DisablesJogPos_WhenBelowMinAngle", Test_Running_DisablesJogPos_WhenBelowMinAngle), 
	new_TestFixture("Test_Running_DoesNotChangeJogCommands_WithinLimits", Test_Running_DoesNotChangeJogCommands_WithinLimits), 
	new_TestFixture("Test_Running_MaxAngle_DoesNotChangeJogPos", Test_Running_MaxAngle_DoesNotChangeJogPos), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldControl_Running, "testSet_FieldControl_Running", setupTest, 0, fixtures, 0, 0, 0);

