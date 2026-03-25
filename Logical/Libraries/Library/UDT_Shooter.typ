
TYPE
	UDT_Shooter_PAR : 	STRUCT 
		Intensity : USINT;
	END_STRUCT;
	UDT_Shooter_HMI : 	STRUCT 
		EnableFan : BOOL;
		Shoot : BOOL;
		IncreaseIntensity : BOOL;
		New_Member : BOOL;
	END_STRUCT;
	UDT_Shooter_CS : 	STRUCT 
		Interlock : BOOL;
		EnableFan : BOOL;
		Shoot : BOOL;
		AutoMode : BOOL;
	END_STRUCT;
	UDT_Shooter_STS : 	STRUCT 
		Idle : BOOL;
		Interlocked : BOOL;
		AlarmActive : BOOL;
		AutoActive : BOOL;
		Shooting : BOOL;
		StatusInt : BOOL;
	END_STRUCT;
	UDT_Shooter_ALM : 	STRUCT 
		FanNotEnabled : BOOL;
	END_STRUCT;
	UDT_Shooter_IO : 	STRUCT 
		Shoot : BOOL;
		EnableFan : BOOL;
	END_STRUCT;
END_TYPE
