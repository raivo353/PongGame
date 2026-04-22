
TYPE
	UDT_BallControl_CS : 	STRUCT 
		AutoMode : BOOL;
		Initialize : BOOL;
		Shoot : BOOL;
		Start : BOOL;
		Stop : BOOL;
		Interlock : BOOL;
		ChangePosition : BOOL;
		ErrorAcknowledge : BOOL;
		StopGame : BOOL;
	END_STRUCT;
	UDT_BallControl_HMI : 	STRUCT 
		dummy : BOOL;
	END_STRUCT;
	UDT_BallControl_PAR : 	STRUCT 
		Position : UINT;
	END_STRUCT;
	UDT_BallControl_STS : 	STRUCT 
		Disabled : BOOL;
		Idle : BOOL;
		AlarmActive : BOOL;
		Initializing : BOOL;
		Running : BOOL;
		Interlocked : BOOL;
		StateInt : USINT;
		AutoActive : BOOL;
		BallVelocity : USINT;
		Direction : BOOL;
		ShootState : USINT;
		SpeedTimeElapsed : UINT;
		ShootTimeElapsed : UINT;
	END_STRUCT;
	UDT_BallControl_ALM : 	STRUCT 
		ShooterAlarm : BOOL;
		MotorAlarm : BOOL;
		DistanceSensorAlarm : BOOL;
	END_STRUCT;
END_TYPE
