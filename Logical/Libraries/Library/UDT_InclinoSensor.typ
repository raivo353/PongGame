
TYPE
	UDT_InclinoSensor_PAR : 	STRUCT 
		dummy : USINT;
	END_STRUCT;
	UDT_InclinoSensor_CS : 	STRUCT 
		Power : BOOL;
		Reset : BOOL;
		SetCenterPoint : BOOL;
	END_STRUCT;
	UDT_InclinoSensor_STS : 	STRUCT 
		CurrentAngle : REAL;
		PowerOn : BOOL;
		AlarmActive : BOOL;
		AlarmActiveColour : USINT;
	END_STRUCT;
	UDT_InclinoSensor_ALM : 	STRUCT 
		dummy : USINT;
	END_STRUCT;
	UDT_InclinoSensor_HMI : 	STRUCT 
		Power : BOOL;
		Reset : BOOL;
	END_STRUCT;
	UDT_InclinoSensor_IO : 	STRUCT 
		DataMSB : USINT;
		DataLSB : USINT;
		SetCenterPoint : USINT; (*waarde 3 naar schrijven*)
	END_STRUCT;
END_TYPE
