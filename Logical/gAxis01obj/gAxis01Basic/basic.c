#ifdef _DEFAULT_INCLUDES
 #include <AsDefault.h>
#endif
#include <string.h>

/* defines of the state-constants */
#define STATE_WAIT              0  
#define STATE_POWER_ON          1  
#define STATE_HOME              2

#define STATE_READY             10
#define STATE_HALT              11
#define STATE_STOP              12
#define STATE_JOG_POSITIVE      13
#define STATE_JOG_NEGATIVE      14
#define STATE_MOVE_ABSOLUTE     15
#define STATE_MOVE_ADDITIVE     16
#define STATE_MOVE_VELOCITY     17

#define STATE_ERROR_AXIS        100
#define STATE_ERROR             101
#define STATE_ERROR_RESET       102

_INIT void BasicControl_init(void)
{

/* get axis object */
Axis1Obj = (UDINT)&gAxis01;

AxisStep = STATE_WAIT;  /* start step */

BasicControl.Parameter.Velocity              = 1000;  /*velocity for movement*/
BasicControl.Parameter.Acceleration          = 5000;  /*acceleration for movement*/
BasicControl.Parameter.Deceleration          = 5000;  /*deceleration for movement*/
BasicControl.Parameter.JogVelocity           = 400;   /*velocity for jogging */

}

_CYCLIC void BasicControl_cyclic(void)
{

/***************************************************************
        Control Sequence
***************************************************************/

/* status information is read before the step sequencer to attain a shorter reaction time */
/************************ MC_READSTATUS *************************/
MC_ReadStatus_0.Enable = !MC_ReadStatus_0.Error;
MC_ReadStatus_0.Axis = Axis1Obj;
MC_ReadStatus(&MC_ReadStatus_0);
BasicControl.AxisState.Disabled             = MC_ReadStatus_0.Disabled;
BasicControl.AxisState.StandStill           = MC_ReadStatus_0.StandStill;
BasicControl.AxisState.Stopping             = MC_ReadStatus_0.Stopping;
BasicControl.AxisState.Homing               = MC_ReadStatus_0.Homing;
BasicControl.AxisState.DiscreteMotion       = MC_ReadStatus_0.DiscreteMotion;
BasicControl.AxisState.ContinuousMotion     = MC_ReadStatus_0.ContinuousMotion;
BasicControl.AxisState.SynchronizedMotion   = MC_ReadStatus_0.SynchronizedMotion;
BasicControl.AxisState.ErrorStop            = MC_ReadStatus_0.Errorstop;

/********************MC_BR_READDRIVESTATUS***********************/
MC_BR_ReadDriveStatus_0.Enable = !MC_BR_ReadDriveStatus_0.Error;
MC_BR_ReadDriveStatus_0.Axis = Axis1Obj; 
MC_BR_ReadDriveStatus_0.AdrDriveStatus = (UDINT)&(BasicControl.Status.DriveStatus);
MC_BR_ReadDriveStatus(&MC_BR_ReadDriveStatus_0);

/******************** MC_READACTUALPOSITION *********************/
MC_ReadActualPosition_0.Enable = (!MC_ReadActualPosition_0.Error);
MC_ReadActualPosition_0.Axis = Axis1Obj;
MC_ReadActualPosition(&MC_ReadActualPosition_0);
if(MC_ReadActualPosition_0.Valid == 1)
{
    BasicControl.Status.ActPosition = MC_ReadActualPosition_0.Position;
}

/******************** MC_READACTUALVELOCITY *********************/
MC_ReadActualVelocity_0.Enable = (!MC_ReadActualVelocity_0.Error);
MC_ReadActualVelocity_0.Axis = Axis1Obj;
MC_ReadActualVelocity(&MC_ReadActualVelocity_0);
if(MC_ReadActualVelocity_0.Valid == 1)
{
    BasicControl.Status.ActVelocity = MC_ReadActualVelocity_0.Velocity;
}

/************************ MC_READAXISERROR **********************/
MC_ReadAxisError_0.Enable = !MC_ReadAxisError_0.Error;
MC_ReadAxisError_0.Axis = Axis1Obj;
MC_ReadAxisError_0.DataAddress = (UDINT)&(BasicControl.Status.ErrorText);
MC_ReadAxisError_0.DataLength = sizeof(BasicControl.Status.ErrorText);
strcpy((void*)&MC_ReadAxisError_0.DataObjectName,"acp10etxen");
MC_ReadAxisError(&MC_ReadAxisError_0);

/**************** CHECK FOR GENERAL AXIS ERROR ******************/
    if ((MC_ReadAxisError_0.AxisErrorID != 0) && (MC_ReadAxisError_0.Valid == 1))
    {
        AxisStep = STATE_ERROR_AXIS;
    }
/***************** CHECK IF POWER SHOULD BE OFF *******************/
    else if ((BasicControl.Command.Power == 0) && (MC_ReadAxisError_0.Valid == 1))
    {
        if ((MC_ReadStatus_0.Errorstop == 1) && (MC_ReadStatus_0.Valid == 1))
        {
            AxisStep = STATE_ERROR_RESET;
        }
        else
        {
            AxisStep = STATE_WAIT;
        }
    }

/* central monitoring of stop command attains a shorter reaction time in case of emergency stop */
/******************CHECK for STOP COMMAND************************/
    if (BasicControl.Command.Stop == 1)
    {
        if ((AxisStep >= STATE_HOME) && (AxisStep <= STATE_ERROR))
        {
            /* reset all FB execute inputs we use */
            MC_Home_0.Execute = 0;
            MC_Stop_0.Execute = 0;
            MC_MoveAbsolute_0.Execute = 0;
            MC_MoveAdditive_0.Execute = 0;
            MC_MoveVelocity_0.Execute = 0;
            MC_Halt_0.Execute = 0;
            MC_ReadAxisError_0.Acknowledge = 0;
            MC_Reset_0.Execute = 0;

            /* reset user commands */
            BasicControl.Command.Halt = 0;
            BasicControl.Command.Home = 0;
            BasicControl.Command.MoveJogPos = 0;
            BasicControl.Command.MoveJogNeg = 0;
            BasicControl.Command.MoveVelocity = 0;
            BasicControl.Command.MoveAbsolute = 0;
            BasicControl.Command.MoveAdditive = 0;
            AxisStep = STATE_STOP;
        }
    }

switch(AxisStep)
{
/******************** WAIT *************************/
    case STATE_WAIT:  /* STATE: Wait */
        if (BasicControl.Command.Power == 1)
        {
            AxisStep = STATE_POWER_ON;
        }
        else
        {
            MC_Power_0.Enable = 0;
        }

        /* reset all FB execute inputs we use */
        MC_Home_0.Execute = 0;
        MC_Stop_0.Execute = 0;
        MC_MoveAbsolute_0.Execute = 0;
        MC_MoveAdditive_0.Execute = 0;
        MC_MoveVelocity_0.Execute = 0;
        MC_Halt_0.Execute = 0;
        MC_ReadAxisError_0.Acknowledge = 0;
        MC_Reset_0.Execute = 0;

        /* reset user commands */
        BasicControl.Command.Halt = 0;
        BasicControl.Command.Home = 0;
        BasicControl.Command.MoveJogPos = 0;
        BasicControl.Command.MoveJogNeg = 0;
        BasicControl.Command.MoveVelocity = 0;
        BasicControl.Command.MoveAbsolute = 0;
        BasicControl.Command.MoveAdditive = 0;

        BasicControl.Status.ErrorID = 0;
    break;

/******************** POWER ON **********************/
    case STATE_POWER_ON:  /* STATE: Power on */
        MC_Power_0.Enable = 1;
        if (MC_Power_0.Status == 1)
        {
            AxisStep = STATE_READY;
        }
        /* if a power error occured go to error state */
        if (MC_Power_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_Power_0.ErrorID;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** READY **********************/
    case STATE_READY:  /* STATE: Waiting for commands */
        if (BasicControl.Command.Home == 1)
        {
            BasicControl.Command.Home = 0;
            AxisStep = STATE_HOME;
        }
        else if (BasicControl.Command.Stop == 1)
        {
            AxisStep = STATE_STOP;
        }
        else if (BasicControl.Command.MoveJogPos == 1)
        {
            AxisStep = STATE_JOG_POSITIVE;
        }
        else if (BasicControl.Command.MoveJogNeg == 1)
        {
            AxisStep = STATE_JOG_NEGATIVE;
        }
        else if (BasicControl.Command.MoveAbsolute == 1)
        {
            BasicControl.Command.MoveAbsolute = 0;
            AxisStep = STATE_MOVE_ABSOLUTE;
        }
        else if (BasicControl.Command.MoveAdditive == 1)
        {
            BasicControl.Command.MoveAdditive = 0;
            AxisStep = STATE_MOVE_ADDITIVE;
        }
        else if (BasicControl.Command.MoveVelocity == 1)
        {
            BasicControl.Command.MoveVelocity = 0;
            AxisStep = STATE_MOVE_VELOCITY;
        }
        else if (BasicControl.Command.Halt == 1)
        {
            BasicControl.Command.Halt = 0;
            AxisStep = STATE_HALT;   
        }
    break;

/******************** HOME **********************/
    case STATE_HOME:  /* STATE: start homing process */
        MC_Home_0.Position = BasicControl.Parameter.HomePosition;
        MC_Home_0.HomingMode = BasicControl.Parameter.HomeMode;
        MC_Home_0.Execute = 1;
        if (MC_Home_0.Done == 1)
        {
            MC_Home_0.Execute = 0;
            AxisStep = STATE_READY;
        }
        /* if a homing error occured go to error state */
        if (MC_Home_0.Error == 1)
        {
            MC_Home_0.Execute = 0;
            BasicControl.Status.ErrorID = MC_Home_0.ErrorID;
            AxisStep = STATE_ERROR;
        }
    break;
    
/************************HALT MOVEMENT**************************/    
    case STATE_HALT:  /* STATE: Stop the active movement */
        MC_Halt_0.Deceleration = BasicControl.Parameter.Deceleration;
        MC_Halt_0.Execute = 1;
        if (MC_Halt_0.Done == 1)
        {
            MC_Halt_0.Execute = 0;
            AxisStep = STATE_READY;  
        }
        /*check if error occured */
        if (MC_Halt_0.Error == 1)
        {
            MC_Halt_0.Execute = 0;
            BasicControl.Status.ErrorID = MC_Halt_0.ErrorID;
            AxisStep = STATE_ERROR;   
        }
    break;

/*********************** STOP MOVEMENT *************************/
    case STATE_STOP: /* STATE: Stop movement as long as command is set */
        MC_Stop_0.Deceleration = BasicControl.Parameter.Deceleration;
        MC_Stop_0.Execute = 1;
        /* if axis is stopped go to ready state */
        if ((MC_Stop_0.Done == 1) && (BasicControl.Command.Stop == 0))
        {
            MC_Stop_0.Execute = 0;
            AxisStep = STATE_READY;
        }
        /* check if error occured */
        if (MC_Stop_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_Stop_0.ErrorID;
            MC_Stop_0.Execute = 0;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** START JOG MOVEMENT POSITVE **********************/
    case STATE_JOG_POSITIVE:  /* STATE: Start jog movement in positive direction */
        MC_MoveVelocity_0.Velocity      = BasicControl.Parameter.JogVelocity;
        MC_MoveVelocity_0.Acceleration  = BasicControl.Parameter.Acceleration;
        MC_MoveVelocity_0.Deceleration  = BasicControl.Parameter.Deceleration;
        MC_MoveVelocity_0.Direction     = mcPOSITIVE_DIR;
        MC_MoveVelocity_0.Execute = 1;
        /* check if jog movement should be stopped */
        if (BasicControl.Command.MoveJogPos == 0)
        {
            MC_MoveVelocity_0.Execute = 0;
            AxisStep = STATE_HALT;
        }
        /* check if error occured */
        if (MC_MoveVelocity_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_MoveVelocity_0.ErrorID;
            MC_MoveVelocity_0.Execute = 0;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** START JOG MOVEMENT NEGATIVE **********************/
    case STATE_JOG_NEGATIVE:  /* STATE: Start jog movement in negative direction */
        MC_MoveVelocity_0.Velocity      = BasicControl.Parameter.JogVelocity;
        MC_MoveVelocity_0.Acceleration  = BasicControl.Parameter.Acceleration;
        MC_MoveVelocity_0.Deceleration  = BasicControl.Parameter.Deceleration;
        MC_MoveVelocity_0.Direction     = mcNEGATIVE_DIR;
        MC_MoveVelocity_0.Execute = 1;        
        /* check if jog movement should be stopped */
        if (BasicControl.Command.MoveJogNeg == 0)
        {
            MC_MoveVelocity_0.Execute = 0;
            AxisStep = STATE_HALT;
        }
        /* check if error occured */
        if (MC_MoveVelocity_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_MoveVelocity_0.ErrorID;
            MC_MoveVelocity_0.Execute = 0;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** START ABSOLUTE MOVEMENT **********************/
    case STATE_MOVE_ABSOLUTE:  /* STATE: Start absolute movement */
        MC_MoveAbsolute_0.Position      = BasicControl.Parameter.Position;
        MC_MoveAbsolute_0.Velocity      = BasicControl.Parameter.Velocity;
        MC_MoveAbsolute_0.Acceleration  = BasicControl.Parameter.Acceleration;
        MC_MoveAbsolute_0.Deceleration  = BasicControl.Parameter.Deceleration;
        MC_MoveAbsolute_0.Direction     = BasicControl.Parameter.Direction;
        MC_MoveAbsolute_0.Execute = 1;
        /* check if commanded position is reached */
        if (BasicControl.Command.Halt == 1)
        {
            BasicControl.Command.Halt = 0;
            MC_MoveAbsolute_0.Execute = 0;
            AxisStep = STATE_HALT;   
        }
        else if (MC_MoveAbsolute_0.Done == 1)
        {
            MC_MoveAbsolute_0.Execute = 0;
             AxisStep = STATE_READY;
        }
        /* check if error occured */
        if (MC_MoveAbsolute_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_MoveAbsolute_0.ErrorID;
            MC_MoveAbsolute_0.Execute = 0;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** START ADDITIVE MOVEMENT **********************/
    case STATE_MOVE_ADDITIVE:  /* STATE: Start additive movement */
        MC_MoveAdditive_0.Distance      = BasicControl.Parameter.Distance;
        MC_MoveAdditive_0.Velocity      = BasicControl.Parameter.Velocity;
        MC_MoveAdditive_0.Acceleration  = BasicControl.Parameter.Acceleration;
        MC_MoveAdditive_0.Deceleration  = BasicControl.Parameter.Deceleration;
        MC_MoveAdditive_0.Execute = 1;
        /* check if commanded distance is reached */
        if (BasicControl.Command.Halt == 1)
        {
            BasicControl.Command.Halt = 0;
            MC_MoveAdditive_0.Execute = 0;
            AxisStep = STATE_HALT;   
        }
        else if (MC_MoveAdditive_0.Done == 1)
        {
            MC_MoveAdditive_0.Execute = 0;
             AxisStep = STATE_READY;
        }
        /* check if error occured */
        if (MC_MoveAdditive_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_MoveAdditive_0.ErrorID;
            MC_MoveAdditive_0.Execute = 0;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** START VELOCITY MOVEMENT **********************/
    case STATE_MOVE_VELOCITY:  /* STATE: Start velocity movement */
        MC_MoveVelocity_0.Velocity      = BasicControl.Parameter.Velocity;
        MC_MoveVelocity_0.Acceleration  = BasicControl.Parameter.Acceleration;
        MC_MoveVelocity_0.Deceleration  = BasicControl.Parameter.Deceleration;
        MC_MoveVelocity_0.Direction     = BasicControl.Parameter.Direction;
        MC_MoveVelocity_0.Execute = 1;
        /* check if commanded velocity is reached */
        if (BasicControl.Command.Halt == 1)
        {
            BasicControl.Command.Halt = 0;
            MC_MoveVelocity_0.Execute = 0;
            AxisStep = STATE_HALT;    
        }
        else if (MC_MoveVelocity_0.InVelocity == 1)
        {
            MC_MoveVelocity_0.Execute = 0;
             AxisStep = STATE_READY;
        }
        /* check if error occured */
        if (MC_MoveVelocity_0.Error == 1)
        {
            BasicControl.Status.ErrorID = MC_MoveVelocity_0.ErrorID;
            MC_MoveVelocity_0.Execute = 0;
            AxisStep = STATE_ERROR;
        }
    break;

/******************** FB-ERROR OCCURED *************************/
    case STATE_ERROR:  /* STATE: Error */
        /* check if FB indicates an axis error */
        if (MC_ReadAxisError_0.AxisErrorCount != 0)
        {
            AxisStep = STATE_ERROR_AXIS;
        }
        else
        {
            if (BasicControl.Command.ErrorAcknowledge == 1)
            {
                BasicControl.Command.ErrorAcknowledge = 0;
                BasicControl.Status.ErrorID = 0;
                /* reset axis if it is in axis state ErrorStop */
                if ((MC_ReadStatus_0.Errorstop == 1) && (MC_ReadStatus_0.Valid == 1))
                {
                    AxisStep = STATE_ERROR_RESET;
                }
                else
                {
                    AxisStep = STATE_WAIT;
                }
            }
        }
    break;

/******************** AXIS-ERROR OCCURED *************************/
    case STATE_ERROR_AXIS:  /* STATE: Axis Error */
        if (MC_ReadAxisError_0.Valid == 1)
        {
            if (MC_ReadAxisError_0.AxisErrorID != 0)
            {
                BasicControl.Status.ErrorID = MC_ReadAxisError_0.AxisErrorID;
            }
            MC_ReadAxisError_0.Acknowledge = 0;
            if (BasicControl.Command.ErrorAcknowledge == 1)
            {
                BasicControl.Command.ErrorAcknowledge = 0;
                /* acknowledge axis error */
                if (MC_ReadAxisError_0.AxisErrorID != 0)
                {
                    MC_ReadAxisError_0.Acknowledge = 1;
                }
            }
            if (MC_ReadAxisError_0.AxisErrorCount == 0)
            {
                BasicControl.Status.ErrorID = 0;
                /* reset axis if it is in axis state ErrorStop */
                if ((MC_ReadStatus_0.Errorstop == 1) && (MC_ReadStatus_0.Valid == 1))
                {
                    AxisStep = STATE_ERROR_RESET;
                }
                else
                {
                    AxisStep = STATE_WAIT;
                }
            }
        }
    break;

/******************** RESET DONE *************************/
    case STATE_ERROR_RESET:  /* STATE: Wait for reset done */
        MC_Reset_0.Execute = 1;
        /* reset MC_Power.Enable if this FB is in Error*/
        if(MC_Power_0.Error == 1)
        {
            MC_Power_0.Enable = 0;
        }
        if(MC_Reset_0.Done == 1)
        {
            MC_Reset_0.Execute = 0;
            AxisStep = STATE_WAIT;
        }
        else if (MC_Reset_0.Error == 1)
        {
            MC_Reset_0.Execute = 0;
            AxisStep = STATE_ERROR;   
        }
    break;
    
/******************** SEQUENCE END *************************/
}

/***************************************************************
        Function Block Calls
***************************************************************/

/************************** MC_POWER ****************************/
MC_Power_0.Axis = Axis1Obj;  /* pointer to axis */
MC_Power(&MC_Power_0);

/************************** MC_HOME *****************************/
MC_Home_0.Axis = Axis1Obj;
MC_Home(&MC_Home_0);

/********************** MC_MOVEABSOLUTE *************************/
MC_MoveAbsolute_0.Axis = Axis1Obj;
MC_MoveAbsolute(&MC_MoveAbsolute_0);

/********************** MC_MOVEADDITIVE *************************/
MC_MoveAdditive_0.Axis = Axis1Obj;
MC_MoveAdditive(&MC_MoveAdditive_0);

/********************** MC_MOVEVELOCITY *************************/
MC_MoveVelocity_0.Axis = Axis1Obj;
MC_MoveVelocity(&MC_MoveVelocity_0);

/************************** MC_STOP *****************************/
MC_Stop_0.Axis = Axis1Obj;
MC_Stop(&MC_Stop_0);

/**************************MC_HALT*******************************/
MC_Halt_0.Axis = Axis1Obj;
MC_Halt(&MC_Halt_0);

/************************** MC_RESET ****************************/
MC_Reset_0.Axis = Axis1Obj;
MC_Reset(&MC_Reset_0);

}


