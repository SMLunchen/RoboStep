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
  int temp;
  int volts;
  byte signal;
};


void setup()
{
	 Serial.begin(9600);
	 Serial.print("Ininittingting....");

	 sensors.begin();
	 pinMode(hbled, OUTPUT);
	 pinMode(trans, OUTPUT);
}

//void prepareData(int t_pre) {

   //byte p1[8];


//   for (int y = 0; y < 5; y++) {
//	 Serial.println(t_pre,BIN);

 //  }

 //  p1 = (byte) t_pre[1];

  // int i;
 //       for (int i = 0; i < 7; i++ ) {
 //       p1[i] = (byte)
 //       }
 //  = (byte) t_pre;



 // int x;
 //    for (int x = 0; x < 7; x++ ) {
  //   Serial.println(p1[i]);
  //   }


   //   for (int i = 0; i < 8; i++ ) {
   //   Serial.println(p2[i]);
   //       }

  //
//}

void loop()
{
	//signal Heartbeat
	digitalWrite(hbled, HIGH);
	delay (200);
	digitalWrite(hbled, LOW);
	delay (400);
	//leave LED high during measurement and transmission
	digitalWrite(hbled, HIGH);


	Serial.print(" Requesting temperatures...");
	sensors.requestTemperatures();
	Serial.println("DONE");
	Serial.print("Temperature is: ");
	Serial.println(sensors.getTempCByIndex(0));

	//converting Stuff
	float t_mess=(sensors.getTempCByIndex(0));
	int t_raw=t_mess*100;
	Serial.println(t_raw,BIN);
	//prepareData(t_raw);

//

	delay (200);
	digitalWrite(hbled, LOW);
	delay(1000);
}
