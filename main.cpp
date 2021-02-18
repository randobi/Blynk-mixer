



#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DNSServer.h>
char auth[] = "70jLqZ_WIgoghZDbeBGL2B8Gg2FJ39dM";
char ssid[] = "RoboLand";
char pass[] = "P0pShop9724";

//ButtonPin is GP13
//const int buttonPin = 4;
const int ledPin = 5;
//int pinValueCycle;
int cycleCount;
int mixTime;
int minutes = 1000; //millis
//int mixTime;
int stirTime;
int restTime;
int reading;
int runTime;
int waitTime;
int value;

void setup() {
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,165),8080);
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  waitTime = restTime * minutes;
  stirTime = mixTime * minutes;

  //timer.setInterval(500,incrementCycle);
}
//Establish Cycle parameters: Cycles,mix time, rest time
  
    BLYNK_WRITE(V2){    //CYCLES this is the number of cycles button pin
    if(param.asInt() == 1) { //this is a Blynk function: assigning incoming value from pin V1 to a variable
      cycleCount++;            // is this the param?
        if(cycleCount > 10){
          cycleCount = 1;
        }      
      }
    Blynk.virtualWrite(1,cycleCount); // 1 is Blynk widget that increments count with button push
    Serial.print("Cycle count = "); Serial.print(cycleCount); Serial.println(" cycles.");
    //Blynk.virtualWrite(3, 127); //blynk LED blob, this has to be a value 0-255;
    }

  BLYNK_WRITE(V3){    //REST is the time between mix periods
    if(param.asInt() == 1) { //this is a Blynk function: assigning incoming value from pin V1 to a variable
      restTime++;            // is this the param?
        if(restTime > 10){
          restTime = 1;
        }            
      }
    Blynk.virtualWrite(6,restTime); // 1 is Blynk widget that increments count with button push
    Serial.print("Rest time = "); Serial.print(restTime); Serial.println(" minutes.");   
    //Blynk.virtualWrite(3, 127); //blynk LED blob, this has to be a value 0-255;
    } 

  BLYNK_WRITE(V4){ //MIX is the duration of mix period
    if(param.asInt() == 1) {//this is a Blynk function: assigning incoming value from pin V4 to a variable
      mixTime++; 
        if(mixTime > 10){
          mixTime = 1;//Serial.print (mixTime);
        }
      }
      Blynk.virtualWrite(5,mixTime); 
      Serial.print("Mix time = "); Serial.print(mixTime); Serial.print(" minutes.\n");     
    } 

  BLYNK_WRITE(V0){ //this is the program start button

      if (param.asInt()==1){
      for (int i = cycleCount; i > 0; i--)
      {
       
        Serial.print("Cycle "); Serial.println(cycleCount);
        Serial.print("Mix "); Serial.println(mixTime);
        digitalWrite(5,HIGH);
        delay(mixTime * minutes);
        digitalWrite(5,LOW);
        delay(restTime * minutes);
        cycleCount--;
        Blynk.virtualWrite(1,cycleCount);
        Serial.print("Mix cycles remaining " ); Serial.println(cycleCount);
    
      }
    }
  } 
     
    
void loop() {
 // incrementCycle();
  Blynk.run();
  //timer.run();
}