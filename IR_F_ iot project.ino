#include <Wire.h>
#include <LiquidCrystal.h>
#define sensorPin1 7
#define sensorPin2 8
int sensorState1 = 0;
int sensorState2 = 0;
int isfirstSensorPassed =0 ;
int isSecondSensorPassed =0 ;
int count=0;
int state = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  pinMode (sensorPin1,INPUT_PULLUP);
  pinMode (sensorPin2, INPUT_PULLUP);
  lcd.begin(16,2);
  lcd.print("COUNTER");
  lcd.setCursor(4,0);
  lcd.setCursor(0,1);
  delay(200);
}
void loop() {
  //sensorState1 = digitalRead(sensorPin1);
  //sensorState2 = digitalRead(sensorPin2);
  int isfirstSensorPassed = digitalRead(sensorPin1);
  int isSecondSensorPassed = digitalRead(sensorPin2);

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
        count++;
        state = 0;
        delay(500);

        }
        }
        else if (state == 2) {
          if (isfirstSensorPassed==LOW) {
            
            count--;
            state = 0;
            delay(500);

            	}
              }

              
   if(count>0)
  {
    lcd.setCursor(0,1);
    lcd.print("Visitors:   ");
    lcd.setCursor(12,1);
    lcd.print(count);
  }
  else 
  {
    lcd.setCursor(0,1);
    lcd.print("No visitors    ");  
  }

}
