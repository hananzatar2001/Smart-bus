You sent
#include <ThingSpeak.h>               // add librery
#include <WiFi.h>

#define sensorPin1 18
#define sensorPin2 5
#define pirPin 32
#define frs1 35
#define frs2 34

const int FieldNumber1 = 1;  //pressure sensor1
const int FieldNumber2= 2;   //pressure sensor2
const int FieldNumber3= 3;   //PIR
const int FieldNumber4= 4;   //ir


WiFiClient  client;
unsigned long counterChannelNumber = 1977231;               // Channel ID
const char * myCounterReadAPIKey = "VPA7H7PR1THI249Q";      // Read API Key
const char * myCounterwiteAPIKey = "TW4MASDX89KO47KY";

int pirStat = 0;              // PIR status

int isfirstSensorPassed =0 ;
int isSecondSensorPassed =0 ;
int firstIRSensorValue = 0;
int SecondIRSensorValue = 0;
int pressureReadingsensor1 = 0;
int pressureReadingsensor2 = 0;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); 
    pinMode (sensorPin1,INPUT);
    pinMode (sensorPin2, INPUT);
    pinMode(pirPin, INPUT);     
    pinMode(frs1, INPUT);
    pinMode(frs2, INPUT);
    WiFi.begin("H.R.Z","(CaP)!.9997");                       // write wifi name & password           
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
int countIR=0;
int state = 0;
void IRsensor(int isfirstSensorPassed,int isSecondSensorPassed)
{
  if (state == 0){
  if (isfirstSensorPassed==1) 
  {
    state = 1;      
    }
    else if (isSecondSensorPassed==1) 
    {
      state = 2;
      }}
  else if(state == 1){
  if (isSecondSensorPassed==1) {
    countIR++;
    state = 0;
    delay(500);
    }}
  else if(state == 2){
  if (isfirstSensorPassed==1) {
    countIR--;
    state = 0;
    }}
  if(countIR>0){
  Serial.print("Visitors:   ");
  Serial.println(countIR);
  }
  else {
    Serial.println("No visitors.......");  
    }
}


void loop() {

  firstIRSensorValue = digitalRead(sensorPin1);
  SecondIRSensorValue = digitalRead(sensorPin2);
  isSecondSensorPassed = !SecondIRSensorValue;
  isfirstSensorPassed = !firstIRSensorValue;
  pressureReadingsensor1 = analogRead(frs1);
  pressureReadingsensor2 = analogRead(frs2);
  pirStat = digitalRead(pirPin); 
  IRsensor(isfirstSensorPassed,isSecondSensorPassed);


  ThingSpeak.setField(FieldNumber1,pressureReadingsensor1);
  ThingSpeak.setField(FieldNumber2,pressureReadingsensor2);
  ThingSpeak.setField(FieldNumber3,pirStat);
  ThingSpeak.setField(FieldNumber4,countIR);

  
  // write to the ThingSpeak channel 
  ThingSpeak.writeFields(counterChannelNumber, myCounterReadAPIKey);



}