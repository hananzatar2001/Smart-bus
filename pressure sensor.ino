
#define frs 8

int countFSR=0;
int state = 0;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); 
    pinMode(frs, INPUT_PULLUP);  
      delay(1000);


}

void loop() {
  // put your main code here, to run repeatedly:
    int pressureReading = analogRead(frs);

     Serial.println(pressureReading);
     delay(1000);
   if (pressureReading >0) {
      countFSR = 1;
      }
      else  {
        countFSR = 0;
        }
   if(countFSR==0) 
   {
     Serial.println("no one");

   }    
   else
   {
     Serial.println("have parson");

   }
}
