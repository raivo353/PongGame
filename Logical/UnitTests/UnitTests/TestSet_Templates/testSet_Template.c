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

_SETUP_TEST(void)
{
	PaddleMotorFB.PaddleMotor = &PaddleMotorStruct;
	PaddleMotorFB.PaddleMotor->STS.StateInt = STATE_IDLE;
	
	TEST_DONE;
}

_TEST test_Template(void)
{
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-05-01 11:23:13Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Idle, "testSet_Template", setupTest, 0, fixtures, 0, 0, 0);

