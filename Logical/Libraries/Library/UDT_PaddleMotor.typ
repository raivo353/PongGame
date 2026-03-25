
TYPE
	UDT_PaddleMotor_IO : 	STRUCT 
		EndButton : BOOL;
	END_STRUCT;
	UDT_PaddleMotor_CS : 	STRUCT 
		Home : BOOL;
		MoveAbsolute : BOOL;
		MoveJogNeg : BOOL;
		MoveJogPos : BOOL;
		Power : BOOL;
		Stop : BOOL;
		ErrorAcknowledge : BOOL;
		Start : BOOL;
		Interlock : BOOL;
		AutoMode : BOOL;
	END_STRUCT;
	UDT_PaddleMotor_HMI : 	STRUCT 
		Home : BOOL;
		MoveAbsolute : BOOL;
		MoveJogNeg : BOOL;
		MoveJogPos : BOOL;
		Power : BOOL;
		Stop : BOOL;
		Start : BOOL;
		IncreaseJogSpeed : BOOL;
		DecreaseJogSpeed : BOOL;
		ErrorAcknowledge : BOOL;
		IncreaseAccDec : BOOL;
		DecreaseAccDec : BOOL;
	END_STRUCT;
	UDT_PaddleMotor_PAR : 	STRUCT 
		Acceleration : REAL;
		Deceleration : REAL;
		JogVelocity : REAL;
		Velocity : REAL;
		TargetPosition : REAL;
	END_STRUCT;
	UDT_PaddleMotor_ALM : 	STRUCT 
		MotorError : BOOL;
		ErrorID : UINT;
		ErrorText : ARRAY[0..3]OF STRING[79];
	END_STRUCT;
	UDT_PaddleMotor_STS : 	STRUCT 
		Disabled : BOOL;
		Homed : BOOL;
		Homing : BOOL;
		Idle : BOOL;
		AlarmActive : BOOL;
		Moving : BOOL;
		StandStill : BOOL;
		AtTargetPosition : BOOL;
		ActPosition : REAL;
		Interlocked : BOOL;
		PowerOn : BOOL;
		AutoActive : BOOL;
		StatusInt : USINT;
		ActVelocity : REAL;
	END_STRUCT;
END_TYPE
