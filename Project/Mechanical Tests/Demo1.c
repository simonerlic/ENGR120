#pragma config(Sensor, dgtl1,  button1,          sensorTouch)
#pragma config(Sensor, dgtl2,  button2,          sensorTouch)
#pragma config(Sensor, dgtl5,  grab_left,      sensorTouch)
#pragma config(Sensor, dgtl6,  grab_right,     sensorTouch)
#pragma config(Sensor, dgtl10, sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port1,           motor_left,    tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           grabber,       tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          motor_right,   tmotorVex393_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

enum T_STATES{STOPPED,FORWARD,REVERSE,SCANNING,FINISH, RELEASE};
bool is_completed = false;
const int threshold = 2;//distance in centimeters
const int slow = 50;
const int fast = 127;


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
		writeDebugStreamLine("button1_pushed=true");
		button1_pushed = true;
	}

	if (SensorValue(button2) && !button2_pushed)
	{
		writeDebugStreamLine("button2_pushed=true");
		button2_pushed = true;
	}
}


bool is_grabbed(){
	writeDebugStreamLine("Checking if grabbed");
	bool isGrabbed = SensorValue[grab_left]==1 && SensorValue[grab_right]==1;
	writeDebugStreamLine("is_Grabbed = %d",isGrabbed);
	return isGrabbed;
}

bool is_released(){
	writeDebugStreamLine("Checking if released");
	bool isReleased = !is_grabbed();
	writeDebugStreamLine("is_Released = %d",isReleased);
	return isReleased;
}

void do_grab(int speed){
	writeDebugStreamLine("Grabbing at speed %d ...",speed);
	while(! is_grabbed()){
		motor[grabber] = speed;
	}
	motor[grabber] = 0;
}

void turn_right(int speed){// We may need a time variable here.
	writeDebugStreamLine("Turning right at speed %d ...",speed);
	motor[motor_left] = speed;
	motor[motor_right] = 0;
}

void turn_left(int speed){
	writeDebugStreamLine("Turning left at speed %d ...",speed);
	motor[motor_left] = 0;
	motor[motor_right] = speed;
}

void move_forward(int speed){
	writeDebugStreamLine("Moving forward at speed %d ...",speed);
	motor[motor_left] = speed;
	motor[motor_right] = speed;
}

void move_reverse(int speed){
	writeDebugStreamLine("Reversing at speed %d ...",speed);
	motor[motor_left] = -speed;
	motor[motor_right] = -speed;
}

void stop(){
	writeDebugStreamLine("Stopping motors...");
	motor[motor_left] = 0;
	motor[motor_right] = 0;
}

bool at_target(){
	writeDebugStreamLine("Checking if we are at target ...");
	bool atTarget = (SensorValue(sonarSensor)<=threshold && is_grabbed());//Add infrared sensed value as well
	writeDebugStreamLine("at_Target = %d",atTarget);
	return atTarget;
}

void do_release(int speed){
	writeDebugStreamLine("Releasing at speed %d ...",speed);
	while(is_grabbed()){
		motor[grabber] = -speed;
	}
	motor[grabber] = 0;
}
task main()
{
	T_STATES STATE = STOPPED;
	while(true){
		monitorInput();

		switch(STATE){
		case STOPPED:
			stop();
			if(button1_pushed){
				clearTimer(T1);
				while(time1[T1]<2000){
					move_forward(slow);
				}
				button1_pushed = false;
				STATE=STOPPED;
			}
			if(button2_pushed){
				clearTimer(T2);
				while(time1[T2]<1000){//Want this to be 90degree rotation
					turn_right(slow);
				}
				button2_pushed = false;
				STATE=STOPPED;
			}
		}
	}
}
