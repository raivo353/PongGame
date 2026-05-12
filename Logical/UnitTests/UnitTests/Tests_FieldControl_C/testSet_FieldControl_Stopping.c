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
	
	FieldControlFB.FieldControl->STS.StateInt = STATE_STOPPING;

	TEST_DONE;
}

_TEST Test_Stopping_StaysStopping_WhenNotDisabled(void)
{
	FieldControlFB.FieldControl->STS.Disabled = 0;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_STOPPING, FieldControlFB.FieldControl->STS.StateInt);

	TEST_DONE;
}

_TEST Test_Stopping_TransitionsToDisabled(void)
{
	FieldControlFB.FieldControl->STS.Disabled = 1;

	FB_FieldControl(&FieldControlFB);

	TEST_ASSERT_EQUAL_INT(STATE_DISABLED, FieldControlFB.FieldControl->STS.StateInt);

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
	new_TestFixture("Test_Stopping_StaysStopping_WhenNotDisabled", Test_Stopping_StaysStopping_WhenNotDisabled), 
	new_TestFixture("Test_Stopping_TransitionsToDisabled", Test_Stopping_TransitionsToDisabled), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_FieldControl_Stopping, "testSet_FieldControl_Stopping", setupTest, 0, fixtures, 0, 0, 0);

