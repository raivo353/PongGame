
TYPE
	UDT_FieldControl_CS : 	STRUCT 
		MoveToAngle : BOOL;
		Initialize : BOOL;
		Stop : BOOL;
		StopGame : BOOL;
		Start : BOOL;
		ErrorAcknowledge : BOOL;
		Interlock : BOOL;
		Automode : BOOL;
	END_STRUCT;
	UDT_FieldControl_STS : 	STRUCT 
		Disabled : BOOL;
		Idle : BOOL;
		Running : BOOL;
		AlarmActive : BOOL;
		Initializing : BOOL;
		Moving : BOOL;
		StateInt : USINT;
		Interlocked : BOOL;
		AutoActive : BOOL;
	END_STRUCT;
	UDT_FieldControl_PAR : 	STRUCT 
		Angle : USINT;
	END_STRUCT;
	UDT_FieldControl_HMI : 	STRUCT 
		dummy : BOOL;
	END_STRUCT;
	UDT_FieldControl_ALM : 	STRUCT 
		MotorAlarm : BOOL;
	END_STRUCT;
END_TYPE
