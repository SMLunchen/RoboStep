//#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HardwareSerial.h>

#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int hbled = 13;
int trans = 7;



#define PACKET_SIZE 11

typedef struct sensorData_t{
  byte stat;
  byte sensorId;
  byte sensortype;
  float temp;
  float volts;
  byte signal;
};


void setup()
{
	 Serial.begin(9600);
	 Serial.print("Dallas Temperature IC Control Library Demo");
	 // Start up the library
	 sensors.begin();
	 pinMode(hbled, OUTPUT);
	 pinMode(trans, OUTPUT);
}


void loop()
{
	//signal Heartbeat
	digitalWrite(hbled, HIGH);
	delay (200);
	digitalWrite(hbled, LOW);
	delay (400);
	digitalWrite(hbled, HIGH);


	Serial.print(" Requesting temperatures...");
	 sensors.requestTemperatures();
	 Serial.println("DONE");
	 Serial.print("Temperature is: ");
	 Serial.println(sensors.getTempCByIndex(0));
	 delay(1000);
	 byte test =  (sensors.getTempCByIndex(0));
	 Serial.println(test);
	 float test2 = (test);
	 Serial.println(test2);
		
	 delay (200);
	 digitalWrite(hbled, LOW);

}
