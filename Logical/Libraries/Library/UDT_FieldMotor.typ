
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
		ErrorAcknowledge : BOOL;
		Start : BOOL;
		Interlock : BOOL;
		AutoMode : BOOL;
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
		Idle : BOOL;
		Homing : BOOL;
		Homed : BOOL;
		Moving : BOOL;
		AtTargetPosition : BOOL;
		Alarm : BOOL;
		AutoActive : BOOL;
		StatusInt : USINT;
		AlarmActive : BOOL;
		ActPosition : REAL;
		ActVelocity : REAL;
	END_STRUCT;
	UDT_FieldMotor_ALM : 	STRUCT 
		MotorError : BOOL;
		ErrorID : UINT;
		ErrorText : ARRAY[0..3]OF STRING[79];
	END_STRUCT;
END_TYPE
