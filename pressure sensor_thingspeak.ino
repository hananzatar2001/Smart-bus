#include <ThingSpeak.h>               // add librery
#include <ESP8266WiFi.h>

WiFiClient  client;
unsigned long counterChannelNumber = 1977231;               // Channel ID
const char * myCounterReadAPIKey = "VPA7H7PR1THI249Q";      // Read API Key
const char * myCounterwiteAPIKey = "TW4MASDX89KO47KY";
const int FieldNumber1 = 2;
int frs =0;
int countFSR=0;
int state = 0;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); 
    pinMode(LEDpin,OUTPUT);
    pinMode(frs, INPUT);  
      delay(1000);
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

void loop() {
  // put your main code here, to run repeatedly:
    int pressureReading = analogRead(frs);

     Serial.println(pressureReading);
   if (pressureReading >100) {

      countFSR = 1;
      }
      else  {
      countFSR = 0;
        }
        if(pressureReading <100) {
          Serial.println("no one");
           }    
           else{
             
             Serial.println("have parson");
             }
   ThingSpeak.writeField(counterChannelNumber,FieldNumber1,pressureReading, myCounterwiteAPIKey);
  int A = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
   Serial.println(A);
   digitalWrite(pressureReading,A);  
}
