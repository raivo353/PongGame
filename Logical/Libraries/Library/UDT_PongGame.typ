
TYPE
	UDT_PongGame_CS : 	STRUCT 
		AutoMode : BOOL;
		ErrorAcknowledge : BOOL;
		Initialize : BOOL;
		Start : BOOL;
		Stop : BOOL;
	END_STRUCT;
	UDT_PongGame_HMI : 	STRUCT 
		AutoMode : BOOL;
		ErrorAcknowledge : BOOL;
		Initialize : BOOL;
		Start : BOOL;
		Stop : BOOL;
	END_STRUCT;
	UDT_PongGame_STS : 	STRUCT 
		Disabled : BOOL;
		AlarmActive : BOOL;
		Idle : BOOL;
		Initializing : BOOL;
		Running : BOOL;
		Stopping : BOOL;
		StatusInt : USINT;
		AutoActive : BOOL;
	END_STRUCT;
	UDT_PongGame_PAR : 	STRUCT 
		Highscore : USINT;
		Score : USINT;
	END_STRUCT;
	UDT_PongGame_ALM : 	STRUCT 
		PaddleAxisError : BOOL;
		ShooterError : BOOL;
		TiltAxisError : BOOL;
	END_STRUCT;
END_TYPE
