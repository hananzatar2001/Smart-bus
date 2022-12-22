#include <ThingSpeak.h>               // add librery
#include <WiFi.h>

#define sensorPin1 18
#define sensorPin2 5
#define pirPin 32
#define frs1 35
#define frs2 34

const int FieldNumber1 = 1;
const int FieldNumber2= 2;
const int FieldNumber3= 3;
const int FieldNumber4= 4;
const int FieldNumber5= 5;


WiFiClient  client;
unsigned long counterChannelNumber = 1977231;               // Channel ID
const char * myCounterReadAPIKey = "VPA7H7PR1THI249Q";      // Read API Key
const char * myCounterwiteAPIKey = "TW4MASDX89KO47KY";




void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); 
    pinMode (sensorPin1,INPUT_PULLUP);
    pinMode (sensorPin2, INPUT_PULLUP);
    pinMode(pirPin, INPUT);     
    pinMode(frs1, INPUT);
    pinMode(frs2, INPUT);
    WiFi.begin("H.R.Z.","(CaP)!.9997");                       // write wifi name & password           
      Serial.println("Connecting");
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
        }
        Serial.println();
        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP());
        ThingSpeak.begin(client);


}

int state = 0;
int countIR=0;
int countFSR=0;
int pirStat = 0;                   // PIR status
//int isfirstSensorPassed =0 ;
//int isSecondSensorPassed =0 ;
int IRsensor(int isfirstSensorPassed,int isSecondSensorPassed){
  if (state == 0) {
    if (isfirstSensorPassed==LOW) {
      state = 1;
      }
      else if (isSecondSensorPassed==LOW) {
        state = 2;
        }
        }
  else if (state == 1) {
    if (isSecondSensorPassed==LOW) {
      countIR++;
      state = 0;
      }
      }
  else if (state == 2) {
    if (isfirstSensorPassed==LOW) {
      countIR--;
      state = 0;
      }
      }
      if(countIR>0){
        Serial.print("Visitors:   ");
        //Serial.println(countIR);
        }
        else {
          Serial.println("No visitors.......");  
          //Serial.println(countIR);
          }
        ThingSpeak.writeField(counterChannelNumber,FieldNumber5,countIR, myCounterwiteAPIKey);
  int IR = ThingSpeak.readLongField(counterChannelNumber, FieldNumber5, myCounterReadAPIKey);
   Serial.println(IR);
   digitalWrite(countIR,IR);
   return countIR;

}
void pressursensor(int pressureReadingsensor1){

     Serial.println(pressureReadingsensor1);
        if(pressureReadingsensor1 <100) {}    
           else{
             Serial.println("have parson in sensor 1");
             delay(500);
             
             }
   ThingSpeak.writeField(counterChannelNumber,FieldNumber1,pressureReadingsensor1, myCounterwiteAPIKey);
  int pres1 = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
   Serial.println(pres1);
   digitalWrite(pressureReadingsensor1,pres1);
  
}
void pressursensor2(int pressureReadingsensor2){

     Serial.println(pressureReadingsensor2);
        if( pressureReadingsensor2 <100) {
           }    
           else{
             Serial.println("have parson in sensor 2");
             }
   ThingSpeak.writeField(counterChannelNumber,FieldNumber2,pressureReadingsensor2, myCounterwiteAPIKey);
  int pres2 = ThingSpeak.readLongField(counterChannelNumber, FieldNumber2, myCounterReadAPIKey);
   Serial.println(pres2);
   digitalWrite(pressureReadingsensor2,pres2);
  
}
void pirsensor(int pirStat){
  if (pirStat == HIGH) {            // if motion detected
   Serial.println("Hey I got you!!!");
    } 
 else {   
    
     }
     ThingSpeak.writeField(counterChannelNumber,FieldNumber3,pirStat, myCounterwiteAPIKey);
  int pir = ThingSpeak.readLongField(counterChannelNumber, FieldNumber3, myCounterReadAPIKey);
   Serial.println(pir);
   digitalWrite(pirStat,pir);
}






void loop() {
  // put your main code here, to run repeatedly:
  int isSecondSensorPassed = digitalRead(sensorPin2);
  int isfirstSensorPassed = digitalRead(sensorPin1);
  int pressureReadingsensor1 = analogRead(frs1);
  int pressureReadingsensor2 = analogRead(frs2);
  pirStat = digitalRead(pirPin); 
  IRsensor(isfirstSensorPassed,isSecondSensorPassed);
  pressursensor(pressureReadingsensor1);
  pressursensor2(pressureReadingsensor2);
  pirsensor(pirStat);




}
