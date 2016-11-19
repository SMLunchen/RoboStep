//#include <Arduino.h>
#include <Stepper.h>
#include <HardwareSerial.h>

//definition-shittyboxxything

//Steps per Rev
#define STEPS 200
//Motor-identifiers //notusedanymore
#define RIGHT R
#define LEFT L

//attached Motors
Stepper motorLeft(STEPS, 8, 9, 10, 11); //L
Stepper motorRight(STEPS, 4, 5, 6, 7);  //R

//define vars

int stepSpeed = 5;
int stepsPerIteration = 20;

//define base values
int currentSpeed = 5;
int currentDirection = 1;



void setup() {
	//init Serial Port for debugging (and slowing microprocessor)
	Serial.begin(9600);

}


void loop() {
	Serial.print("Current Speed: "+String(currentSpeed));
	Serial.println();

	if (currentSpeed==0){
			currentSpeed=5;
		}
	//actually does nothing at the moment..
driveForward(200, 500);
rotateRight(90);
driveReverse(20,50);
rotateRight(90);
driveForward(200,500);
rotateLeft(90);
driveReverse(20,50);
rotateLeft(90);


}

int checkEmerInterrupt(){
	int emerStop = digitalRead(2);
	switch (emerStop){
	case 0:
	   {
		return 0;
	   }
		break;
	case 1:
	   {
		return 1;
	   }
		break;
	}
}


void driveForward(int targetSpeed, int distance) {
	if (currentSpeed==0){
		currentSpeed=5;
	}

  while(checkEmerInterrupt() == 0 && distance > 0) {
	if (currentSpeed < targetSpeed){
		Serial.print("accel d: "+String(distance));
		Serial.println();
		 setSpeed(currentSpeed, motorLeft);
		 setSpeed(currentSpeed, motorRight);
		 motorStep(stepsPerIteration, motorLeft);
		 motorStep(stepsPerIteration, motorRight);
		 currentSpeed += stepSpeed;
		 distance = distance-10;
	}
		 else if (currentSpeed == targetSpeed){
		Serial.print("hold d: "+String(distance));
		Serial.println();
		 motorStep(stepsPerIteration, motorLeft);
		 motorStep(stepsPerIteration, motorRight);
		 distance = distance-10;
	}
		 else if (currentSpeed > targetSpeed){
		Serial.print("decel d: "+String(distance));
		Serial.println();
		 setSpeed(currentSpeed, motorLeft);
		 setSpeed(currentSpeed, motorRight);
		 motorStep(stepsPerIteration, motorLeft);
		 motorStep(stepsPerIteration, motorRight);
		 currentSpeed -= stepSpeed;
		 distance = distance-10;
	} //endif

  } //ende whine
  Fbreak();

}

void driveReverse(int targetSpeed, int distance) {
	if (currentSpeed==0){
			currentSpeed=5;
		}

  while(checkEmerInterrupt() == 0 && distance > 0) {
	if (currentSpeed < targetSpeed){
		 setSpeed(currentSpeed, motorLeft);
		 setSpeed(currentSpeed, motorRight);
		 motorStep((stepsPerIteration*-1), motorLeft);
		 motorStep((stepsPerIteration*-1), motorRight);
		 currentSpeed += stepSpeed;
		 distance = distance-10;
	}
		 else if (currentSpeed == targetSpeed){
		 motorStep((stepsPerIteration*-1), motorLeft);
		 motorStep((stepsPerIteration*-1), motorRight);
		 distance = distance-10;
	}
		 else if (currentSpeed > targetSpeed){
		 setSpeed(currentSpeed, motorLeft);
		 setSpeed(currentSpeed, motorRight);
		 motorStep((stepsPerIteration*-1), motorLeft);
		 motorStep((stepsPerIteration*-1), motorRight);
		 currentSpeed -= stepSpeed;
		 distance = distance-10;
	} //endif

  } //ende whine
  Rbreak();
}

void rotateRight(int angle){
	//calculate steps
	int StepsToRotate = (int)(angle/(360/200));
	Serial.print("Rotating..: "+String(StepsToRotate));
	Serial.println();
	while(checkEmerInterrupt() == 0 && angle > 0 && StepsToRotate > 0) {
		setSpeed(20, motorLeft);
		setSpeed(20, motorRight);
		motorStep(1, motorLeft);
		motorStep(-1, motorRight);
		StepsToRotate -= StepsToRotate;

	}
	clearPins();
}

void rotateLeft(int angle){
	//calculate steps
	int StepsToRotate = (int)(angle/(360/200));
	while(checkEmerInterrupt() == 0 && angle > 0 && StepsToRotate > 0) {
		setSpeed(20, motorLeft);
		setSpeed(20, motorRight);
		motorStep(-1, motorLeft);
		motorStep(1, motorRight);
		StepsToRotate -= StepsToRotate;

	}
	clearPins();
}

/*
void decelerate(int targetSpeed) {
  while(currentSpeed > targetSpeed) {
    setSpeed(currentSpeed);
    motorLeft.step(currentDirection * stepsPerIteration);
    currentSpeed -= stepSpeed;
  }
  if(targetSpeed == 0)
    clearPins();
}
*/

//forward-Break --well actually it's a break ramp
void Fbreak(){
	while(currentSpeed > 0) {
		if (currentSpeed==0){
				currentSpeed=5;
			}
		setSpeed(currentSpeed, motorLeft);
		setSpeed(currentSpeed, motorRight);
	    motorStep(stepsPerIteration/2, motorLeft);
	    motorStep(stepsPerIteration/2, motorRight);
	    currentSpeed -= (stepSpeed * 5);
	  }

	  clearPins();
}

//reverse-Break --well actually it's a break ramp
void Rbreak(){
	if (currentSpeed==0){
			currentSpeed=5;
		}
	while(currentSpeed < 0) {
		setSpeed(currentSpeed, motorLeft);
		setSpeed(currentSpeed, motorRight);
	    motorStep((stepsPerIteration*-1)/2, motorLeft);
	    motorStep((stepsPerIteration*-1)/2, motorRight);
	    currentSpeed += (stepSpeed * 5);
	  }

	  clearPins();
}

//emergency breakythingy rampipipuuuh...<3
void emergencyBreak(int forceFactor) {
	while(currentSpeed > 0) {
			setSpeed(currentSpeed, motorLeft);
			setSpeed(currentSpeed, motorRight);
		    motorStep(stepsPerIteration/2, motorLeft);
		    motorStep(stepsPerIteration/2, motorRight);
		    currentSpeed -= (stepSpeed * forceFactor);
		  }

		  clearPins();
}


void clearPins(){
	clearPinsLeft();
	clearPinsRight();
	currentSpeed=5;
}

void clearPinsLeft() {
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  Serial.print("Pins Left Cleared");
  Serial.println();
}

void clearPinsRight() {
	digitalWrite(7, 0);
	digitalWrite(6, 0);
	digitalWrite(5, 0);
	digitalWrite(4, 0);
	Serial.print("Pins Right Cleared");
	Serial.println();
}

void setSpeed(int speed, Stepper motorIdentifier) {
	if(speed < 0)
    speed = 1;
  motorIdentifier.setSpeed(speed);
}

void motorStep(int Steps, Stepper motorIdentifier){
	motorIdentifier.step(Steps);
}


