/*
   -- Arduino8266 --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.6 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.8.01 or later version;
     - for iOS 1.5.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_WIFI_CLOUD
#include <WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "27802"
#define REMOTEXY_WIFI_PASSWORD "3d90f44d"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "d6513b2044c18aea49e3ddd1abbab9f7"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,58,0,13,13,1,
  1,0,4,49,12,12,2,31,49,0,
  4,128,4,32,50,7,2,26,2,0,
  11,13,40,13,2,26,31,31,79,78,
  0,79,70,70,0,1,0,23,49,12,
  12,2,31,50,0,1,0,44,49,12,
  12,2,31,51,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 
  int8_t slider_1; // =0..100 slider position 
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 13
#define RXp2 16
#define TXp2 17
int isRun=0;
int slider=0;

void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON_1, OUTPUT);
  
  // TODO you setup code
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}

void senddata(char key, int val)
{
  Serial2.print(key);
  Serial2.print(val);
}

void loop() 
{ 
  char key;
  int val;
  RemoteXY_Handler ();

  // Вкл/Выкл
  if (RemoteXY.switch_1==1 and isRun==0) {
    senddata('f',0);
    isRun=1;
    digitalWrite(PIN_BUTTON_1, HIGH);
    Serial.println("f");
  }
  if (RemoteXY.switch_1==0 and isRun==1) {
    senddata('r',0);
    isRun=0;
    digitalWrite(PIN_BUTTON_1, LOW);
    Serial.println("r");
  }
  
  // Скорость
  if (RemoteXY.slider_1!=slider) {
    val=map(RemoteXY.slider_1,0,100,0,255);
    senddata('s',val);
    slider=RemoteXY.slider_1;
    Serial.println("s - "+String(val, DEC));
  }
  
  
  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
