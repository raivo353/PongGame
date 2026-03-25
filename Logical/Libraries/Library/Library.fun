
{REDUND_ERROR} FUNCTION ActPositionToMM : UINT (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		ActPosition : REAL;
	END_VAR
END_FUNCTION

FUNCTION SetOutputs : USINT
	VAR_INPUT
		digitalOutputs : USINT;
		ventilator : BOOL;
		solenoid : BOOL;
	END_VAR
END_FUNCTION

FUNCTION SensorDataConverter : INT
	VAR_INPUT
		MSB : USINT;
		LSB : USINT;
	END_VAR
END_FUNCTION

FUNCTION InclineSensorDataToAngle : REAL
	VAR_INPUT
		InclineSensorData : INT;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION_BLOCK FB_PaddleMotor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		PaddleMotor : UDT_PaddleMotor;
	END_VAR
	VAR
		digitalInput : USINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_DistanceSensor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		DistanceSensor : UDT_DistanceSensor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Shooter (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		Shooter : UDT_Shooter;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_FieldMotor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		FieldMotor : UDT_FieldMotor;
	END_VAR
	VAR
		digitalInput : USINT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_InclinoSensor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		InclinoSensor : UDT_InclinoSensor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_BallControl (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		BallControl : UDT_BallControl;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_FieldControl (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		FieldControl : UDT_FieldControl;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_PongGame (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		PongGame : UDT_PongGame;
	END_VAR
END_FUNCTION_BLOCK
