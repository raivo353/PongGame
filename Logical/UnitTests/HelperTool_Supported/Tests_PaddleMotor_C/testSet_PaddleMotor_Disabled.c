/********************************************************************
 * COPYRIGHT --
 ********************************************************************
 * Program: -
 * Author:
 * Created: 
 ********************************************************************
 * Tests for ... 
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "Library.h"



_TEST test_States(void)
{
	/* TODO:  add assertions here */
	PaddleMotorFB.digitalInput = 0;
	PaddleMotorFB.PaddleMotor = &PaddleMotorStruct;
	PaddleMotorFB.PaddleMotor->STS.StateInt = 10;
	
	FB_PaddleMotor(&PaddleMotorFB);


	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->STS.Disabled);
	TEST_ASSERT_EQUAL_INT(1, PaddleMotorFB.PaddleMotor->CS.Power);
	/* test is done */
	TEST_DONE;
}




/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2026-04-10 11:10:30Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("test_States", test_States), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(testSet_PaddleMotor_Disabled, "testSet_PaddleMotor_Disabled", 0, 0, fixtures, 0, 0, 0);

