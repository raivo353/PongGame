
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_FieldMotor(struct FB_FieldMotor* inst)
{
	/*TODO: Add your code here*/
	inst->FieldMotor->IO.EndButton = !((inst->digitalInput & 0x4) >> 2);
	
}
