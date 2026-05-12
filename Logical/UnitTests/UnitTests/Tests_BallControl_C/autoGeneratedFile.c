/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (List of TestSets).
LastUpdated: 2026-05-07 12:26:03Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
#include "UnitTest.h"



UNITTEST_TESTSET_DECLARATION  testSet_BallControl_Disabled;
UNITTEST_TESTSET_DECLARATION  testSet_BallControl_Initializing;
UNITTEST_TESTSET_DECLARATION  testSet_BallControl_Idle;
UNITTEST_TESTSET_DECLARATION  testSet_BallControl_Running;
UNITTEST_TESTSET_DECLARATION  testSet_BallControl_Stopping;



UNITTEST_TESTSET_FIXTURES(utTestSets)
{
	new_TestSet(testSet_BallControl_Disabled),
	new_TestSet(testSet_BallControl_Initializing),
	new_TestSet(testSet_BallControl_Idle),
	new_TestSet(testSet_BallControl_Running),
	new_TestSet(testSet_BallControl_Stopping),
};
UNTITTEST_TESTSET_HANDLER();

