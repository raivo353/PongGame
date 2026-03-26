
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
void FB_Shooter(struct FB_Shooter* inst)
{
	/*TODO: Add your code here*/
	inst->Shooter->IO.Shoot = inst->Shooter->HMI.Shoot;
	inst->Shooter->IO.EnableFan = inst->Shooter->HMI.EnableFan;
	
	inst->digitalOutput = 0;
	inst->digitalOutput |= (inst->Shooter->IO.Shoot << 3);
	inst->digitalOutput |= inst->Shooter->IO.EnableFan;
}
