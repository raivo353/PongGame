
#include <bur/plctypes.h>
#include "variables.h"
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _CYCLIC ProgramCyclic(void)
{
	// Insert code here 
	if(i_HMI_Button_1)
	{
		o_HMI_Button_1 = true;
		o_HMI_Button_2 = false;
		o_HMI_Button_3 = false;
	}
	else if(i_HMI_Button_2)
	{
		o_HMI_Button_1 = false;
		o_HMI_Button_2 = true;
		o_HMI_Button_3 = false;
	}
	else if(i_HMI_Button_3)
	{
		o_HMI_Button_1 = false;
		o_HMI_Button_2 = false;
		o_HMI_Button_3 = true;
	}
}
