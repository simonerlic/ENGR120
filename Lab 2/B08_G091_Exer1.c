#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// WHEN YOU FINISH EACH EXERCISE, INCREMENT THIS VALUE
#define EXERCISE_NUMBER 	1

bool button1_pushed; //flag to store button1 input
bool button2_pushed; //flag to store button2 input


/* monitorInput()
*
*  Used to flag button inputs
*       - this avoids errors caused by program recognizing input, taking action, and
*         reading input again before button is released
*/
void monitorInput()
{
	if (SensorValue(button1) && !button1_pushed)
	{
		button1_pushed = true;
	}

	if (SensorValue(button2) && !button2_pushed)
	{
		button2_pushed = true;
	}
}

void exercise_1()
{
	// Define tag for enumerated type for exercise 2
	enum T_exercise1_state {
		MOTOR_STOPPED = 0,
		MOTOR_RUNNING
	};

	// Declare variable to hold state, intialize to MOTOR_STOP state.
	T_exercise1_state exercise1_state = MOTOR_STOP;

	while (true)
	{
		// This function updates the button1_pushed and button2_pushed flags.
		monitorInput();

		// Switch the states.
		switch (exercise1_state) {

			// Code for MOTOR_STOP state:
		case MOTOR_STOPPED:
			// Turn motor off.
			motor[motor1] = 0;
			if (button1_pushed) {
				// If button1 pushed, change to the MOTOR_RUNNING state.
				exercise1_state = MOTOR_RUNNING;
				// Clear flag to indicate button 1 processed.
				button1_pushed = false;
			}
			break;
		case MOTOR_RUNNING:
			// Turn motor on.
			motor[motor1] = 50;
			// If button2 is pushed or motor has turned 627 ticks (one revolution)
			if (button2_pushed) {
				// If button 2 pushed, transition to MOTOR_STOP state.
				exercise1_state = MOTOR_STOPPED;
				// Clear flag to indicate that button 2 processed.
				button2_pushed = false;
			}
			break;
		default:
		}

	}//end while
}

void exercise_2()
{
	//Do we need to use these?
	enum T_test_state {
		STATE1 = 0,
		STATE2,
		STATE3
	};

	// Define tag for enumerated type for exercise 1
	enum T_motor_state {
		MOTOR_STOPPED = 0,
		MOTOR_RUNNING
	};

	T_test_state test_state = STATE1;
	// Declare variable to hold state, intialize to MOTOR_STOP state.
	T_motor_state motor_state = MOTOR_STOPPED;

	while (true)
	{
		// This function updates the button1_pushed and button2_pushed flags.
		monitorInput();

		// Switch the states.
		switch (motor_state) {

			// Code for MOTOR_STOP state:
		case MOTOR_STOPPED:
			// Turn motor off.
			motor[motor1] = 0;
			// Reset the encoder
			resetMotorEncoder(motor1);
			if (button1_pushed) {
				// If button1 pushed, change to the MOTOR_RUNNING state.
				motor_state = MOTOR_RUNNING;
				// Clear flag to indicate button 1 processed.
				button1_pushed = false;
			}
			break;
		case MOTOR_RUNNING:
			// Turn motor on.
			motor[motor1] = 50;
			while (getMotorEncoder(motor1) < 627) {
				//do nothing but allow motor to turn one full rotation
			}
			// If button2 is pushed or motor has turned more than 627 ticks (one revolution)
			if (button2_pushed || getMotorEncoder(motor1) >= 627) {
				// If button 2 pushed, transition to MOTOR_STOP state.
				motor_state = MOTOR_STOPPED;
				// Clear flag to indicate that button 2 processed.
				button2_pushed = false;
			}
			break;
		default:
		}
	}// end while

} // end exercise_2

void exercise_3()
{

	// Define tag for enumerated type for exercise 1
	enum T_motor_state {
		MOTOR_STOPPED = 0,
		MOTOR_FORWARDS,
		MOTOR_BACKWARDS
	};

	// Declare variable to hold state, intialize to MOTOR_STOP state.
	T_motor_state motor_state = MOTOR_STOPPED;

	while (true)
	{
		// This function updates the button1_pushed and button2_pushed flags.
		monitorInput();

		// Switch the states.
		switch (motor_state) {

			// Code for MOTOR_STOP state:
		case MOTOR_STOPPED:
			// Turn motor off.
			motor[motor1] = 0;
			// Reset the encoder
			resetMotorEncoder(motor1);
			if (button1_pushed) {
				// If button1 pushed, change to the MOTOR_FORWARDS state.
				motor_state = MOTOR_FORWARDS;
				// Clear flag to indicate button 1 processed.
				button1_pushed = false;
			}
			else if (button2_pushed) {
				// If button2 pushed, change to the MOTOR_BACKWARDS state.
				motor_state = MOTOR_BACKWARDS;
				// Clear flag to indicate button 2 processed.
				button2_pushed = false;
			}
			break;
		case MOTOR_FORWARDS:
			// Turn motor on.
			motor[motor1] = 50;
			while (getMotorEncoder(motor1) < 3000) {
				//Do nothing but wait for motor to continue for 3000 ticks.
			}
			// If button2 is pushed or motor has turned over 3000 ticks (one revolution)
			if (button2_pushed || getMotorEncoder(motor1) > 3000) {
				motor_state = MOTOR_BACKWARDS;
				// Clear flag to indicate that button 2 processed.
				button2_pushed = false;
			}
			else if (button1_pushed) {
				//Do nothing but set the  button1 pushed flag.
				button1_pushed = true;
			}
			break;
		case MOTOR_BACKWARDS:
			// Turn motor on.
			motor[motor1] = -50;
			while (getMotorEncoder(m1) < 3000) {
				//Do nothing but wait for motor to continue for 3000 ticks.
			}
			// If button1 is pushed or motor has turned over 3000 ticks (one revolution)
			if (button1_pushed || getMotorEncoder(motor1) > 3000) {
				motor_state = MOTOR_FORWARDS;
				// Clear flag to indicate that button 2 processed.
				button1_pushed = false;
			}
			else if (button2_pushed) {
				//Do nothing but set the button2 pushed flag.
				button2_pushed = true;
			}
			break;
		default:
		}
	}// end while


}//end exercse_3


task main()
{
	button1_pushed = button2_pushed = false;

	switch (EXERCISE_NUMBER)
	{
	case 1:
		exercise_1();
		break;
	case 2:
		exercise_2();
		break;
	case 3:
		exercise_3();
		break;
	default: //should never get here.
	} // end switch

}// end main
