/********************************************************************
 * COPYRIGHT - MyAutomation-IT
 ********************************************************************
 * Program: Tests_PaddleMotor_C::testSuite.c
 * Author: Raivo Berends
 * Created: 10-4-2026
 ********************************************************************
 * Test registration and handshake
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "Library.h"



void _INIT initTestSuite(void)
{
	utInit(&Testsuite);
}


void _CYCLIC cyclicWithTest(void)
{
	utCyclic(&Testsuite);
}


void _EXIT exitTestSuite(void)
{
	utExit(&Testsuite);
}


