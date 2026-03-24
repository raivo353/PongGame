
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

FUNCTION DistanceSensor : INT
	VAR_INPUT
		DistanceMSB : USINT;
		DistanceLSB : USINT;
	END_VAR
END_FUNCTION
