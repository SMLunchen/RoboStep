//#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HardwareSerial.h>

#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int hbled = 13;
int trans = 7;
int dts = 0;
int debugpi = 9;
int debugpi2 = 8;
int msstate = 1;
float vref = 5.0;
int vBat_raw = 0;
float vBat = 0;



//so solls mal aussehen... :X
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
	 pinMode(debugpi, OUTPUT);
	 pinMode(debugpi2, OUTPUT);

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
	digitalWrite(hbled, 1);
	delay (200);
	digitalWrite(hbled, 0);
	delay (400);
	//leave LED high during measurement and transmission
	digitalWrite(hbled, 1);

	//get LiPo voltage to estimate charging status
	Serial.println();
	int vBat_raw = analogRead(A0);
	vBat = vBat_raw*vref/1024;
	Serial.print("Bat Voltage: ");
	Serial.println(vBat);


	Serial.print(" Requesting temperatures...");
	sensors.requestTemperatures();
	Serial.println("DONE");
	Serial.print("Temperature is: ");
	Serial.println(sensors.getTempCByIndex(0));

	//get temp
	float t_mess=(sensors.getTempCByIndex(0));
	//convert float to int
	int t_raw=t_mess*100;
	//debugvalue:
	//int t_raw=25600;

	//debug
	Serial.print("T-RAWR: ");
	Serial.println(t_raw,BIN);

	//build 5 digit array
	char buffer[5];

	dtostrf(t_raw, 5, 0, buffer);
		for (int i = 0; i < 5 ; i++)
		{
				//sub T prepare to send
				int t_pts = buffer[i];
				//serial debug the whole buffer as bin
				Serial.print("BufferVAL: ");
				Serial.print(char(t_pts));
				Serial.print(" - ");
				Serial.println(char(t_pts),BIN);
				delay(50);

				//clocking data out of Pin 7
				for (int ii = 0; ii < 6; ii++)
				{
				//take it bitvise! -- ready to send
				int t_rts = bitRead(t_pts,ii);

				//only debug
				Serial.print(t_rts);
				Serial.print(" : ");
				if (ii == 5){
					Serial.println();
				}



				//main function
				for (int iii = 0; iii < 2; iii++)
				{

				//debugging clock part 1
				digitalWrite(debugpi, msstate);
				//delay(1);
				//debugging data part 1
				digitalWrite(debugpi2, t_rts);

				switch (t_rts)
				{
				case 0:
				{
						if   (msstate == 1) {
						//clocking dataline -> rising edge
						dts = 1;
						digitalWrite(trans, dts);
						delay(1);
					}
						else if (msstate == 0) {
						//clocking dataline -> falling edge
						dts = 0;
						digitalWrite(trans, dts);
						delay(1);
						}
					}
				break;

				case 1:
				{
					if  ( msstate == 0 ) {
						//clocking dataline -> rising edge
						dts = 1;
						digitalWrite(trans, dts);
						delay(1);
						}
					else if ( msstate == 1 ) {
						//clocking dataline -> rising edge
						dts = 0;
						digitalWrite(trans, dts);
						delay(1);
						}
				}
				break;
				//end Switch
				}

				//clocking msstate
				if (msstate == 1 ) {
					msstate = 0;
				}
				else{
					msstate = 1;
				}



				//end for
				}




		}
		}
	Serial.println();
	delay (200);
	digitalWrite(hbled, 0);
	delay(1000);


}
