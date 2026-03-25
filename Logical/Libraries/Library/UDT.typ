
TYPE
	UDT_PongGame : 	STRUCT 
		ALM : UDT_PongGame_ALM;
		CS : UDT_PongGame_CS;
		HMI : UDT_PongGame_HMI;
		PAR : UDT_PongGame_PAR;
		STS : UDT_PongGame_STS;
	END_STRUCT;
	UDT_FieldControl : 	STRUCT 
		ALM : UDT_FieldControl_ALM;
		CS : UDT_FieldControl_CS;
		HMI : UDT_FieldControl_HMI;
		PAR : UDT_FieldControl_PAR;
		STS : UDT_FieldControl_STS;
	END_STRUCT;
	UDT_BallControl : 	STRUCT 
		ALM : UDT_BallControl_ALM;
		CS : UDT_BallControl_CS;
		HMI : UDT_BallControl_HMI;
		PAR : UDT_BallControl_PAR;
		STS : UDT_BallControl_STS;
	END_STRUCT;
	UDT_InclinoSensor : 	STRUCT 
		ALM : UDT_InclinoSensor_ALM;
		CS : UDT_InclinoSensor_CS;
		HMI : UDT_InclinoSensor_HMI;
		PAR : UDT_InclinoSensor_PAR;
		STS : UDT_InclinoSensor_STS;
	END_STRUCT;
	UDT_FieldMotor : 	STRUCT 
		ALM : UDT_FieldMotor_ALM;
		CS : UDT_FieldMotor_CS;
		HMI : UDT_FieldMotor_HMI;
		IO : UDT_FieldMotor_IO;
		PAR : UDT_FieldMotor_PAR;
		STS : UDT_FieldMotor_STS;
	END_STRUCT;
	UDT_Shooter : 	STRUCT 
		ALM : UDT_Shooter_ALM;
		CS : UDT_Shooter_CS;
		HMI : UDT_Shooter_HMI;
		IO : UDT_Shooter_IO;
		PAR : UDT_Shooter_PAR;
		STS : UDT_Shooter_STS;
	END_STRUCT;
	UDT_DistanceSensor : 	STRUCT 
		ALM : UDT_DistanceSensor_ALM;
		CS : UDT_DistanceSensor_CS;
		HMI : UDT_DistanceSensor_HMI;
		IO : UDT_DistanceSensor_IO;
		PAR : UDT_DistanceSensor_PAR;
		STS : UDT_DistanceSensor_STS;
	END_STRUCT;
	UDT_PaddleMotor : 	STRUCT 
		ALM : UDT_PaddleMotor_ALM;
		CS : UDT_PaddleMotor_CS;
		HMI : UDT_PaddleMotor_HMI;
		IO : UDT_PaddleMotor_IO;
		PAR : UDT_PaddleMotor_PAR;
		STS : UDT_PaddleMotor_STS;
	END_STRUCT;
END_TYPE
