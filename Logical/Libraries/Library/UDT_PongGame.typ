
TYPE
	UDT_PongGame_CS : 	STRUCT 
		AutoMode : BOOL;
		ErrorAcknowledge : BOOL;
		Initialize : BOOL;
		Start : BOOL;
		StopGame : BOOL;
	END_STRUCT;
	UDT_PongGame_HMI : 	STRUCT 
		AutoMode : BOOL;
		ErrorAcknowledge : BOOL;
		Initialize : BOOL;
		Start : BOOL;
		StopGame : BOOL;
	END_STRUCT;
	UDT_PongGame_PAR : 	STRUCT 
		Highscore : UINT;
		Score : UINT;
	END_STRUCT;
	UDT_PongGame_STS : 	STRUCT 
		Disabled : BOOL;
		AlarmActive : BOOL;
		Idle : BOOL;
		Initializing : BOOL;
		Running : BOOL;
		StateInt : USINT;
		AutoActive : BOOL;
		Interlocked : BOOL;
		AlarmActiveColour : USINT;
		GameStopped : BOOL;
		StateString : STRING[80];
	END_STRUCT;
	UDT_PongGame_ALM : 	STRUCT 
		dummy : BOOL;
	END_STRUCT;
END_TYPE
