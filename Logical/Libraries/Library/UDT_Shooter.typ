
TYPE
	UDT_Shooter_PAR : 	STRUCT 
		Intensity : REAL;
	END_STRUCT;
	UDT_Shooter_HMI : 	STRUCT 
		EnableFan : BOOL;
		Shoot : BOOL;
		IncreaseIntensity : BOOL;
		DecreaseIntensity : BOOL;
	END_STRUCT;
	UDT_Shooter_CS : 	STRUCT 
		Interlock : BOOL;
		EnableFan : BOOL;
		Shoot : BOOL;
		StopGame : BOOL;
		Start : BOOL;
		AutoMode : BOOL;
	END_STRUCT;
	UDT_Shooter_STS : 	STRUCT 
		Disabled : BOOL;
		Idle : BOOL;
		Interlocked : BOOL;
		AlarmActive : BOOL;
		AutoActive : BOOL;
		Shooting : BOOL;
		StateInt : USINT;
	END_STRUCT;
	UDT_Shooter_ALM : 	STRUCT 
		dummy : BOOL;
	END_STRUCT;
	UDT_Shooter_IO : 	STRUCT 
		EnableFan : BOOL;
		Shoot : BOOL;
	END_STRUCT;
END_TYPE
