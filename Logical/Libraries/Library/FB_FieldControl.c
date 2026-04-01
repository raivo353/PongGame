
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
void FB_FieldControl(struct FB_FieldControl* inst)
{
	/*TODO: Add your code here*/
	inst->FieldMotor->CS.Initialize = inst->FieldControl->CS.Initialize;
	inst->FieldMotor->CS.Start = inst->FieldControl->CS.Start;
	inst->FieldMotor->CS.StopGame = inst->FieldControl->CS.StopGame;
	inst->FieldMotor->CS.ErrorAcknowledge = inst->FieldControl->CS.ErrorAcknowledge;

}
