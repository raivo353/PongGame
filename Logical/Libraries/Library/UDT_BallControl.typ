
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
		Position : REAL;
		DesiredPosition : REAL;
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
		BallVelocity : REAL;
		ShootState : USINT;
		TimeToPaddleMS : DINT;
		ShootCycleCompleted : BOOL;
		PrevShootState : USINT;
		NewShootCycleTimerET : UINT;
		GameOver : BOOL;
	END_STRUCT;
	UDT_BallControl_ALM : 	STRUCT 
		ShooterAlarm : BOOL;
		MotorAlarm : BOOL;
		DistanceSensorAlarm : BOOL;
	END_STRUCT;
END_TYPE
