
#include <ThingSpeak.h>               // add librery
#include <WiFi.h>
//منحددو بكرا
#define sensorPin1 2
#define sensorPin2 27
#define pirPin 0



//تم التحدييد 
#define frs1 36
#define frs2 34     




const char* ssid     = "H.R.Z.";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "(CaP)!.9997";     // The password of the Wi-Fi network          
WiFiClient  client;
unsigned long counterChannelNumber = 1977231;               // Channel ID
const char * myCounterReadAPIKey = "VPA7H7PR1THI249Q";      // Read API Key
const char * myCounterwiteAPIKey = "TW4MASDX89KO47KY";
const int FieldNumber1 = 1;
const int FieldNumber2= 2;
const int FieldNumber3= 3;
const int FieldNumber4= 4;

int isfirstSensorPassed =0 ;
int isSecondSensorPassed =0 ;
int pirStat = 0;                   // PIR status
int countIR=0;
int countFSR=0;
int state = 0;





void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); 
    pinMode (sensorPin1,INPUT_PULLUP);
    pinMode (sensorPin2, INPUT_PULLUP);
    pinMode(pirPin, INPUT);     
    pinMode(frs1, INPUT);
    pinMode(frs2, INPUT);  
    WiFi.begin(ssid,password);                       // write wifi name & password           
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
void irsensor(int isfirstSensorPassed,int isSecondSensorPassed){
  
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
         delay(500);
         }
         }
     else if (state == 2) {
       if (isfirstSensorPassed==LOW) {
         countIR--;
         state = 0;
         delay(500);
         }
     }
        
    if(countIR>0){
      Serial.print("Visitors:   ");
      Serial.println(countIR);
      }
      else {
        Serial.println("No visitors.......");  
        }
}
void pressursensor(int pressureReadingsensor1){

     Serial.println(pressureReadingsensor1);
   if (pressureReadingsensor1 >100) {

      countFSR = 1;
      }
      else  {
      countFSR = 0;
        }
        if(pressureReadingsensor1 <100) {
          Serial.println("no one");
           }    
           else{
             
             Serial.println("have parson");
             }
   ThingSpeak.writeField(counterChannelNumber,FieldNumber1,pressureReadingsensor1, myCounterwiteAPIKey);
  int A = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
   Serial.println(A);
   digitalWrite(pressureReadingsensor1,A);
  
}
void pressursensor2(int pressureReadingsensor2){

     Serial.println(pressureReadingsensor2);
        if( pressureReadingsensor2 <100) {
          Serial.println("no one");
           }    
           else{
             
             Serial.println("have parson");
             }
   ThingSpeak.writeField(counterChannelNumber,FieldNumber2,pressureReadingsensor2, myCounterwiteAPIKey);
  int B = ThingSpeak.readLongField(counterChannelNumber, FieldNumber2, myCounterReadAPIKey);
   Serial.println(B);
   digitalWrite(pressureReadingsensor2,B);
  
}
void pirsensor(int pirStat){
  if (pirStat == HIGH) {            // if motion detected
   Serial.println("Hey I got you!!!");
    } 
 else {   
   Serial.println("no one .....");
    
     }
     ThingSpeak.writeField(counterChannelNumber,FieldNumber3,pirStat, myCounterwiteAPIKey);
  int C = ThingSpeak.readLongField(counterChannelNumber, FieldNumber3, myCounterReadAPIKey);
   Serial.println(C);
   digitalWrite(pirStat,C);
}


void loop() 
{
  // put your main code here, to run repeatedly:
  int isfirstSensorPassed = digitalRead(sensorPin1);
  int isSecondSensorPassed = digitalRead(sensorPin2);
  int pressureReadingsensor1 = analogRead(frs1);
  int pressureReadingsensor2 = analogRead(frs2);
  pirStat = digitalRead(pirPin); 


  irsensor(isfirstSensorPassed,isSecondSensorPassed);
  pressursensor(pressureReadingsensor1);
  pressursensor2(pressureReadingsensor2);
  pirsensor(pirStat);
 
      
}
