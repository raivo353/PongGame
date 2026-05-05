/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (List of TestSets).
LastUpdated: 2026-05-01 12:04:37Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
#include "UnitTest.h"



UNITTEST_TESTSET_DECLARATION  testSet_PaddleMotor_Disabled;
UNITTEST_TESTSET_DECLARATION  testSet_PaddleMotor_Initializing;
UNITTEST_TESTSET_DECLARATION  testSet_PaddleMotor_Idle;
UNITTEST_TESTSET_DECLARATION  testSet_PaddleMotor_Running;
UNITTEST_TESTSET_DECLARATION  testSet_PaddleMotor_Stopping;



UNITTEST_TESTSET_FIXTURES(utTestSets)
{
	new_TestSet(testSet_PaddleMotor_Disabled),
	new_TestSet(testSet_PaddleMotor_Initializing),
	new_TestSet(testSet_PaddleMotor_Idle),
	new_TestSet(testSet_PaddleMotor_Running),
	new_TestSet(testSet_PaddleMotor_Stopping),
};
UNTITTEST_TESTSET_HANDLER();

