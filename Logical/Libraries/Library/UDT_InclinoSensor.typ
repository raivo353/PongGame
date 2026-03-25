
TYPE
	UDT_InclinoSensor_PAR : 	STRUCT 
	END_STRUCT;
	UDT_InclinoSensor_CS : 	STRUCT 
		Power : BOOL;
		Reset : BOOL;
		SetCenterPoint : BOOL;
	END_STRUCT;
	UDT_InclinoSensor_STS : 	STRUCT 
		CurrentAngle : REAL;
		PowerOn : BOOL;
		StatusInt : USINT;
	END_STRUCT;
	UDT_InclinoSensor_ALM : 	STRUCT 
	END_STRUCT;
	UDT_InclinoSensor_HMI : 	STRUCT 
		Power : BOOL;
		Reset : BOOL;
		SetCenterPoint : BOOL;
	END_STRUCT;
END_TYPE
