
{REDUND_ERROR} FUNCTION_BLOCK FB_PaddleMotor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		digitalInput : USINT;
	END_VAR
	VAR_IN_OUT
		PaddleMotor : UDT_PaddleMotor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_DistanceSensor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		DistanceSensorLeft : UDT_DistanceSensor;
		DistanceSensorMiddle : UDT_DistanceSensor;
		DistanceSensorRight : UDT_DistanceSensor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Shooter (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_OUTPUT
		digitalOutput : USINT;
	END_VAR
	VAR_IN_OUT
		Shooter : UDT_Shooter;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_FieldMotor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		digitalInput : USINT;
	END_VAR
	VAR_IN_OUT
		FieldMotor : UDT_FieldMotor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_InclinoSensor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		InclinoSensor : UDT_InclinoSensor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_BallControl (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		BallControl : UDT_BallControl;
		PaddleMotor : UDT_PaddleMotor;
		Shooter : UDT_Shooter;
		DistanceSensorLeft : UDT_DistanceSensor;
		DistanceSensorMiddle : UDT_DistanceSensor;
		DistanceSensorRight : UDT_DistanceSensor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_FieldControl (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		FieldMotor : UDT_FieldMotor;
		FieldControl : UDT_FieldControl;
		InclinoSensor : UDT_InclinoSensor;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_PongGame (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_IN_OUT
		PongGame : UDT_PongGame;
		BallControl : UDT_BallControl;
		FieldControl : UDT_FieldControl;
	END_VAR
END_FUNCTION_BLOCK
