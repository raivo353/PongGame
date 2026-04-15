
TYPE
	UDT_DistanceSensor_STS : 	STRUCT 
		Distance : INT;
		Reflectivity : INT;
		TooClose : BOOL;
		TooFar : BOOL;
		Valid : BOOL;
		DeviceStatus : UINT;
		PowerOn : BOOL;
		StateInt : USINT;
		AlarmActive : BOOL;
		AlarmActiveColour : USINT;
	END_STRUCT;
	UDT_DistanceSensor_CS : 	STRUCT 
		Power : BOOL;
	END_STRUCT;
	UDT_DistanceSensor_PAR : 	STRUCT 
		dummy : USINT;
	END_STRUCT;
	UDT_DistanceSensor_IO : 	STRUCT 
		OUT1 : BOOL;
		OUT2 : BOOL;
		DataMSB : USINT;
		DataLSB : USINT;
		SensorInfo : USINT; (*bit 0 = OUT1 (1 als <300mm) , bit 1 = OUT2 (1 als <30mm) , bit 4-7 device status*)
	END_STRUCT;
	UDT_DistanceSensor_ALM : 	STRUCT 
		OutOfBounds : BOOL;
	END_STRUCT;
	UDT_DistanceSensor_HMI : 	STRUCT 
		Power : BOOL;
	END_STRUCT;
END_TYPE
