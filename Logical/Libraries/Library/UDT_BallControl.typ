
TYPE
	UDT_BallControl_CS : 	STRUCT 
		AutoMode : BOOL;
		Initialize : BOOL;
		Shoot : BOOL;
		Start : BOOL;
		Stop : BOOL;
		Interlock : BOOL;
		ChangePosition : BOOL;
		New_Member : BOOL;
	END_STRUCT;
	UDT_BallControl_HMI : 	STRUCT 
		Start : BOOL;
		Stop : BOOL;
	END_STRUCT;
	UDT_BallControl_PAR : 	STRUCT 
		Position : UINT;
	END_STRUCT;
	UDT_BallControl_STS : 	STRUCT 
		Disabled : BOOL;
		Idle : BOOL;
		AlarmActive : BOOL;
		Initializing : BOOL;
		Running : BOOL;
		Stopping : BOOL;
		Interlocked : BOOL;
		StatusInt : BOOL;
		AutoActive : BOOL;
	END_STRUCT;
	UDT_BallControl_ALM : 	STRUCT 
		ShooterAlarm : BOOL;
		MotorAlarm : BOOL;
	END_STRUCT;
END_TYPE
