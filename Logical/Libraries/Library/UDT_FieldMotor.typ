
TYPE
	UDT_FieldMotor_HMI : 	STRUCT 
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
	END_STRUCT;
	UDT_FieldMotor_CS : 	STRUCT 
		Home : BOOL;
		MoveAbsolute : BOOL;
		MoveJogNeg : BOOL;
		MoveJogPos : BOOL;
		Power : BOOL;
		Stop : BOOL;
		StopGame : BOOL;
		ErrorAcknowledge : BOOL;
		Start : BOOL;
		Interlock : BOOL;
		Initialize : BOOL;
		SetCenterPoint : BOOL;
	END_STRUCT;
	UDT_FieldMotor_PAR : 	STRUCT 
		Acceleration : REAL;
		Deceleration : REAL;
		JogVelocity : REAL;
		Velocity : REAL;
		Position : REAL;
	END_STRUCT;
	UDT_FieldMotor_IO : 	STRUCT 
		EndButton : BOOL;
		Power : BOOL;
		Home : BOOL;
		ErrorAcknowledge : BOOL;
		MoveJogNeg : BOOL;
		MoveJogPos : BOOL;
		Stop : BOOL;
		MoveAbsolute : BOOL;
		Acceleration : REAL;
		Deceleration : REAL;
		JogVelocity : REAL;
		Velocity : REAL;
		Position : REAL;
	END_STRUCT;
	UDT_FieldMotor_STS : 	STRUCT 
		Disabled : BOOL;
		Initializing : BOOL;
		Idle : BOOL;
		Running : BOOL;
		AlarmActive : BOOL;
		Moving : BOOL;
		StandStill : BOOL;
		AtTargetPosition : BOOL;
		ActPosition : REAL;
		Interlocked : BOOL;
		PowerOn : BOOL;
		AutoActive : BOOL;
		StateInt : USINT;
		ActVelocity : REAL;
		EndButtonHit : BOOL;
		TimerStarted : BOOL;
		TimerEnded : BOOL;
		ReferencePosition : REAL;
		AlarmActiveColour : USINT;
	END_STRUCT;
	UDT_FieldMotor_ALM : 	STRUCT 
		MotorError : BOOL;
		ErrorID : UINT;
		ErrorText : ARRAY[0..3]OF STRING[79];
	END_STRUCT;
END_TYPE
