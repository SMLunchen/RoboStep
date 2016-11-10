//#include <Arduino.h>
#include <Stepper.h>
#include <HardwareSerial.h>

#define STEPS 200

Stepper motor0(STEPS, 8, 9, 10, 11);

int stepSpeed = 5;
int stepsPerIteration = 20;

int currentSpeed = 5;
int currentDirection = -1;

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.print("Current Speed: "+String(currentSpeed));
	Serial.println();

  accelerate(200);

  motor0.step(currentDirection * STEPS * 10);

  decelerate(50);

  motor0.step(currentDirection * STEPS * 5);

  accelerate(100);

  motor0.step(currentDirection * STEPS * 2);

  //emergencyBreak(2);

  driveBackwards();

	Serial.print("Current Speed: "+String(currentSpeed));
	Serial.println();

  accelerate(200);

  motor0.step(currentDirection * STEPS * 10);

  decelerate(50);

  motor0.step(currentDirection * STEPS * 5);

  accelerate(100);

  motor0.step(currentDirection * STEPS * 2);

 // emergencyBreak(2);

  driveForward();

  delay(2000);
}

/*
void switchDirection() {
  currentDirection = currentDirection * -1;
}
*/

void driveBackwards(){
  currentDirection = -1;
}

void driveForward(){
  currentDirection = 1;
}

void accelerate(int targetSpeed) {
  while(currentSpeed < targetSpeed) {
    setSpeed(currentSpeed);
    motor0.step(currentDirection * stepsPerIteration);
    currentSpeed += stepSpeed;
  }
}

void decelerate(int targetSpeed) {
  while(currentSpeed > targetSpeed) {
    setSpeed(currentSpeed);
    motor0.step(currentDirection * stepsPerIteration);
    currentSpeed -= stepSpeed;
  }
  if(targetSpeed == 0)
    clearPins();
}

void emergencyBreak(int forceFactor) {
  while(currentSpeed > 0) {
    setSpeed(currentSpeed);
    motor0.step(currentDirection * stepsPerIteration/10);
    currentSpeed -= (stepSpeed * forceFactor);
  }

  clearPins();
}

void clearPins() {
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  Serial.print("Pins Cleared");
  Serial.println();
  currentSpeed = 0;
}

void setSpeed(int speed) {
  if(speed < 0)
    speed = 1;
  motor0.setSpeed(speed);
}
