
TYPE
	UDT_DistanceSensor_STS : 	STRUCT 
		Distance : INT;
		Reflectivity : INT;
		TooClose : BOOL;
		TooFar : BOOL;
		Valid : BOOL;
		DeviceStatus : UINT;
		PowerOn : BOOL;
		StatusInt : USINT;
	END_STRUCT;
	UDT_DistanceSensor_CS : 	STRUCT 
		Power : BOOL;
	END_STRUCT;
	UDT_DistanceSensor_PAR : 	STRUCT 
	END_STRUCT;
	UDT_DistanceSensor_IO : 	STRUCT 
		OUT1 : BOOL;
		OUT2 : BOOL;
	END_STRUCT;
	UDT_DistanceSensor_ALM : 	STRUCT 
		OutOfBounds : BOOL;
	END_STRUCT;
	UDT_DistanceSensor_HMI : 	STRUCT 
	END_STRUCT;
END_TYPE
