//#include <Arduino.h>
#include <Stepper.h>
#include <HardwareSerial.h>

//definition-shittyboxxything

//Steps per Rev
#define STEPS 200

//attached Motors
Stepper motorLeft(STEPS, 8, 9, 10, 11);
Stepper motorRight(STEPS, 4, 5, 6, 7);

//define vars
int stepSpeed = 2;
int stepsPerIteration = 1;

//define base values
int currentSpeed = 5;
int currentDirection = 1;

void setup() {
	//init Serial Port for debugging (and slowing microprocessor)
	Serial.begin(9600);

}

void loop() {
	Serial.print("Current Speed: " + String(currentSpeed));
	Serial.println();

	//actually does nothing at the moment..
	driveForward(50, 1000);
	rotateRight(90);
	//driveReverse(20, 50);
	//driveForward(200, 2000);
	//rotateRight(90);
	//rotateLeft(90);
	//driveReverse(20, 50);
	//rotateLeft(90);

}

int checkEmerInterrupt() {
	int emerStop = digitalRead(2);
	switch (emerStop) {
	case 0: {
		return 0;
	}
		break;
	case 1: {
		return 1;
	}
		break;
	}
}

void driveForward(int targetSpeed, int distance) {
	while (checkEmerInterrupt() == 0 && distance > 0) {
		if (currentSpeed < targetSpeed) {
			Serial.print("accel d: " + String(distance) + " - " + String(currentSpeed));
			Serial.println();
			setSpeed(currentSpeed, &motorLeft);
			setSpeed(currentSpeed, &motorRight);
			motorStep(stepsPerIteration, &motorLeft);
			motorStep(stepsPerIteration*-1, &motorRight);
			currentSpeed += stepSpeed;
			distance = distance - 10;
		} else if (currentSpeed == targetSpeed) {
			Serial.print("hold d: " + String(distance) + " - " + String(currentSpeed));
			Serial.println();
			motorStep(stepsPerIteration, &motorLeft);
			motorStep(stepsPerIteration*-1, &motorRight);
			distance = distance - 10;
		} else if (currentSpeed > targetSpeed) {
			Serial.print("decel d: " + String(distance) + " - " + String(currentSpeed));
			Serial.println();
			setSpeed(currentSpeed, &motorLeft);
			setSpeed(currentSpeed, &motorRight);
			motorStep(stepsPerIteration, &motorLeft);
			motorStep(stepsPerIteration*-1, &motorRight);
			currentSpeed -= stepSpeed;
			distance = distance - 10;
		} //endif

	} //ende whine
	Fbreak();

}

/*
void driveReverse(int targetSpeed, int distance) {
	while (checkEmerInterrupt() == 0 && distance > 0) {
		if (currentSpeed < targetSpeed) {
			setSpeed(currentSpeed, &motorLeft);
			setSpeed(currentSpeed, &motorRight);
			motorStep((stepsPerIteration * -1), &motorLeft);
			motorStep((stepsPerIteration), &motorRight);
			currentSpeed += stepSpeed;
			distance = distance - 10;
		} else if (currentSpeed == targetSpeed) {
			motorStep((stepsPerIteration * -1), &motorLeft);
			motorStep((stepsPerIteration), &motorRight);
			distance = distance - 10;
		} else if (currentSpeed > targetSpeed) {
			setSpeed(currentSpeed, &motorLeft);
			setSpeed(currentSpeed, &motorRight);
			motorStep((stepsPerIteration * -1), &motorLeft);
			motorStep((stepsPerIteration), &motorRight);
			currentSpeed -= stepSpeed;
			distance = distance - 10;
		} //endif

	} //ende whine
	Rbreak();
}
*/


void rotateRight(int angle) {
	rotate(angle, 1);
}

void rotateLeft(int angle) {
	rotate(angle, -1);
}

void rotate(int angle, int step) {
	//calculate steps
	currentSpeed = 20;
	int StepsToRotate = (int) (angle * 1.8); // 1.8 = 360 Grad / 200 Steps per round
	Serial.print("Rotating..: " + String(StepsToRotate));
	Serial.println();
	while (checkEmerInterrupt() == 0 && StepsToRotate > 0) {
		setSpeed(currentSpeed, &motorLeft);
		setSpeed(currentSpeed, &motorRight);
		motorStep(step, &motorLeft);
		motorStep(step, &motorRight);
		StepsToRotate -= 1;
		//Serial.print("#");
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
void Fbreak() {
	while (currentSpeed > 0) {
		setSpeed(currentSpeed, &motorLeft);
		setSpeed(currentSpeed, &motorRight);
		motorStep(stepsPerIteration / 2, &motorLeft);
		motorStep(stepsPerIteration / 2, &motorRight);
		currentSpeed -= (stepSpeed * 2);
	}
	clearPins();
}

//reverse-Break --well actually it's a break ramp
void Rbreak() {
	while (currentSpeed < 0) {
		setSpeed(currentSpeed, &motorLeft);
		setSpeed(currentSpeed, &motorRight);
		motorStep((stepsPerIteration * -1) / 2, &motorLeft);
		motorStep((stepsPerIteration * -1) / 2, &motorRight);
		currentSpeed += (stepSpeed * 5);
	}

	clearPins();
}

//emergency breakythingy rampipipuuuh...<3
void emergencyBreak(int forceFactor) {
	while (currentSpeed > 0) {
		setSpeed(currentSpeed, &motorLeft);
		setSpeed(currentSpeed, &motorRight);
		motorStep(stepsPerIteration / 2, &motorLeft);
		motorStep(stepsPerIteration / 2, &motorRight);
		currentSpeed -= (stepSpeed * forceFactor);
	}

	clearPins();
}

void clearPins() {
	clearPinsLeft();
	clearPinsRight();
	currentSpeed = 0;
}

void clearPinsLeft() {
	digitalWrite(8, 0);
	digitalWrite(9, 0);
	digitalWrite(10, 0);
	digitalWrite(11, 0);
	//Serial.print("Pins Left Cleared");
	//Serial.println();
}

void clearPinsRight() {
	digitalWrite(7, 0);
	digitalWrite(6, 0);
	digitalWrite(5, 0);
	digitalWrite(4, 0);
	//Serial.print("Pins Right Cleared");
	//Serial.println();
}

void setSpeed(int speed, Stepper *motorIdentifier) {
	//Serial.print("Set: "+ String(speed));
	//Serial.println();
	if (speed < 0)
		speed = 0;
	motorIdentifier->setSpeed(speed);
}

void motorStep(int Steps, Stepper *motorIdentifier) {
	//Serial.print("Step: "+ String(Steps));
	//Serial.println();
	if(currentSpeed > 0)
		motorIdentifier->step(Steps);
}

