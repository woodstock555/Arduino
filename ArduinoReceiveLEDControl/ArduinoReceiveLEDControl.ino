// Receives 65 from JAVA Programrunning on PC and lights up LED connected to Pin 7 

void setup() 
{
  pinMode(13, OUTPUT);            // sets the digital pin 7 as output
  Serial.begin(9600,SERIAL_8N1); // set up the arduino serial 
}

void loop() 
{
  
    byte ReceivedByte = 0;
    char TextToSend[32];
    uint8_t n=0;
    
    if(Serial.available()>0)
    {
      delay(100);
      //TextToSend = Serial.read();
      while (Serial.available() && n<32) 
      { 
        TextToSend[n++] = Serial.read(); 
      }
//      if(ReceivedByte == 65)
//      {
//          digitalWrite(13, HIGH); // sets the digital pin 7 on
//          delay(5000);            // waits for a second
//          digitalWrite(13, LOW);  // sets the digital pin 7 off
//          delay(1000);           // waits for a second
//      }    
      Serial.println("="+String(TextToSend));
      
    }//end of serial
}//end of loop() 
