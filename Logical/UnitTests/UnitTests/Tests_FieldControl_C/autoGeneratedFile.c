/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (List of TestSets).
LastUpdated: 2026-05-07 13:11:07Z
By B+R UnitTest Helper Version: 2.0.2.35
*/
#include "UnitTest.h"



UNITTEST_TESTSET_DECLARATION  testSet_FieldControl_Disabled;
UNITTEST_TESTSET_DECLARATION  testSet_FieldControl_Initializing;
UNITTEST_TESTSET_DECLARATION  testSet_FieldControl_Idle;
UNITTEST_TESTSET_DECLARATION  testSet_FieldControl_Running;
UNITTEST_TESTSET_DECLARATION  testSet_FieldControl_Stopping;



UNITTEST_TESTSET_FIXTURES(utTestSets)
{
	new_TestSet(testSet_FieldControl_Disabled),
	new_TestSet(testSet_FieldControl_Initializing),
	new_TestSet(testSet_FieldControl_Idle),
	new_TestSet(testSet_FieldControl_Running),
	new_TestSet(testSet_FieldControl_Stopping),
};
UNTITTEST_TESTSET_HANDLER();

