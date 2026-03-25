
TYPE
	UDT_FieldControl_CS : 	STRUCT 
		MoveToAngle : BOOL;
		Initialize : BOOL;
		Start : BOOL;
		Stop : BOOL;
		ErrorAcknowledge : BOOL;
		Interlock : BOOL;
		Automode : BOOL;
	END_STRUCT;
	UDT_FieldControl_STS : 	STRUCT 
		Disabled : BOOL;
		Idle : BOOL;
		AlarmActive : BOOL;
		Initializing : BOOL;
		Error : BOOL;
		Moving : BOOL;
		StatusInt : USINT;
		Interlocked : BOOL;
		AutoActive : BOOL;
	END_STRUCT;
	UDT_FieldControl_PAR : 	STRUCT 
		Angle : USINT;
	END_STRUCT;
	UDT_FieldControl_HMI : 	STRUCT 
		Stop : BOOL;
		Start : BOOL;
	END_STRUCT;
	UDT_FieldControl_ALM : 	STRUCT 
		MotorAlarm : BOOL;
	END_STRUCT;
END_TYPE
