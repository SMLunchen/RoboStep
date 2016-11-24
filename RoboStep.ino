//#include <Arduino.h>
#include <Stepper.h>
#include <HardwareSerial.h>

//Steps per Rev
#define STEPS 200

//attached Motors
Stepper motorLeft(STEPS, 8, 9, 10, 11);
Stepper motorRight(STEPS, 4, 5, 6, 7);

// Variables
int _speedAccelerate = 2;
int _speedBreak = 4;
int _speedRotate = 10;

int _speedMax = 100;

int _currentSpeed = 0;
int _currentDirection = 1;

float _tireCircumference = 47;	// CM = 470mm
float _motorStepAngle = 1.8;	// step angle
float _distancePerStep = _tireCircumference/360*_motorStepAngle; // => 0.235 cm per step

void setup() {
	//init Serial Port for debugging (and slowing microprocessor)
	Serial.begin(9600);
}

void SerialDebug(String data){
	Serial.print(data);
	Serial.println();
}

void loop() {
	//SerialDebug("loop() start");
	/*
	_currentDirection = 1;
	drive(200);
	_currentDirection = -1;
	drive(200);
	*/
	//SerialDebug("loop() drive done");
	rotateLeft(90);	// rotate 90 degrees
	delay(1000);
	rotateRight(90);	// rotate 90 degrees
	delay(1000);
	//SerialDebug("loop() rotate done");
}

bool checkEmergencyInterrupt() {
	if(digitalRead(2) == 1)
		return true;
	return false;
}

void driveCurve(float distance, int angle, int orientation) {
	// TODO
}

void drive(float distance) {
	float stepsToBreak = _currentSpeed/_speedBreak;
	float stepsToTake = distance / _distancePerStep;

	// while no emergency break and distance given and distance to go bigger than distance to break
	while (!checkEmergencyInterrupt() && distance > 0 && (stepsToTake - stepsToBreak) > 0) {
		//Accelerate
		if (_currentSpeed < _speedMax) {
			_currentSpeed += _speedAccelerate;
			setSpeed(_currentSpeed, &motorLeft);
			setSpeed(_currentSpeed, &motorRight);

		} else if (_currentSpeed > _speedMax) {
			_currentSpeed -= _speedAccelerate;
			setSpeed(_currentSpeed, &motorLeft);
			setSpeed(_currentSpeed, &motorRight);
		}

		motorStep(1*_currentDirection, &motorLeft);
		motorStep(1*_currentDirection*-1, &motorRight);

		//decrease distance depending on tire size
		distance -= _distancePerStep;
		stepsToBreak = _currentSpeed/_speedBreak;
		stepsToTake = distance / _distancePerStep;

	} //end while
	Break();
}

void rotateRight(int angle) {
	rotate(angle, 1);
}

void rotateLeft(int angle) {
	rotate(angle, -1);
}

void rotate(int angle, int orientation) {
	_currentSpeed = _speedRotate;
	int StepsToRotate = angle * 4;// ???? TODO - how

	while (!checkEmergencyInterrupt() && StepsToRotate > 0) {
		setSpeed(_currentSpeed, &motorLeft);
		setSpeed(_currentSpeed, &motorRight);
		//if(orientation > 0)
			motorStep(1*orientation, &motorLeft);
		//else
			motorStep(1*orientation, &motorRight);
		StepsToRotate -= 1;
	}
	clearPins();
}

void Break() {
	while (_currentSpeed > 0) {
		setSpeed(_currentSpeed, &motorLeft);
		setSpeed(_currentSpeed, &motorRight);
		motorStep(1*_currentDirection, &motorLeft);
		motorStep(1*_currentDirection*-1, &motorRight);
		_currentSpeed -= _speedBreak;
	}
	clearPins();
}

void clearPins() {
	clearPinsLeft();
	clearPinsRight();
	_currentSpeed = 0;
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
	if(_currentSpeed > 0)
		motorIdentifier->step(Steps);
}

