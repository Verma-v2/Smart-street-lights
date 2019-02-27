/****   Copyright [2019] [Gyanendra Verma]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.**/
#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
/***************** ESP configuration******************************************************************************************************************/

SoftwareSerial EspSerial(3,2); // tx ,rx
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 115200


char auth[] = "cecefdac9c004b568ca7ba31386e641e";
/*********************************************Wi-Fi credentials****************************************************************************************/
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Gyan's phone";
char pass[] = "12345678";

/*************************************************************PINS SETUP*********************************************************************************/
int led1=8, led2=9, led3=10;
int pir1=11, pir2=12, pir3=7;
int ldr= A0;

/***************************************************************Void SETUP******************************************************************************/

void setup() {
  Serial.begin(9600);
   EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  pinMode(pir3,INPUT);
  pinMode(ldr,INPUT);
}
/**********************************************************************Void LOOP********************************************************************************************/
void loop() {
    Blynk.run();
int sens1=digitalRead(pir1);
int sens2=digitalRead(pir2);
int sens3=digitalRead(pir3);
int visibility=analogRead(ldr);
Serial.print("SENS1");
Serial.println(sens1);
Serial.print("SENS2");
Serial.println(sens2);
Serial.print("SENS3");
Serial.println(sens3);
Serial.print("visibility");
Serial.println(visibility);
delay(500);
if (sens1 == 1) {
analogWrite(led1,255);

}

else if ( sens2 == 1 ) {
  analogWrite(led2,255);

}
else if(sens3 == 1) {
 
  analogWrite(led3,255);

}
else if (visibility<=350) {
   analogWrite(led1,255);
  analogWrite(led2,255);
  analogWrite(led3,255);
}
 else{
  analogWrite(led1,5);
analogWrite(led2,5);
analogWrite(led3,5);
}
}

/***************************************** Blynk FUNCTIONS Here***********************************************************************************************************************/

// Virtual write for button not required
BLYNK_WRITE(V2) {
  int ledState = param.asInt();
  digitalWrite(led1, ledState);
  digitalWrite(led2, ledState);
  digitalWrite(led3, ledState);
}
BLYNK_WRITE(V6)
{
  // You'll get HIGH/1 at startTime and LOW/0 at stopTime.
  // this method will be triggered every day
  // until you remove widget or stop project or
  int ledState = param.asInt();
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
  digitalWrite(led3, ledState);
 if(ledState==1) {
  Blynk.notify("Hey, lamp 3 is on now!");
 Serial.print("Hey, lamp 3 is on now!");
 }
}
 
 BLYNK_WRITE(V7)
 {
  // You'll get HIGH/1 at startTime and LOW/0 at stopTime.
  // this method will be triggered every day
  // until you remove widget or stop project or
  int ledState = param.asInt();
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
  digitalWrite(led3, ledState);
 if(ledState==1) {
  Blynk.notify("Hey, lamp 3 is on now!");
 Serial.print("Hey, lamp 3 is on now!");
 }
 }
