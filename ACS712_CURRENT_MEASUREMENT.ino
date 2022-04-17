#include <LiquidCrystal.h>
#define RS 13
#define EN 12
#define d4 11
#define d5 10
#define d6 9
#define d7 8
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
const int sensorIn = A0;
const int currSensor_pot = A2;
int mVperAmp = 66;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0; 
int offsetVoltage = 2500;
float getVPP();
void setup() {
  pinMode(sensorIn, INPUT);
  pinMode(currSensor_pot, INPUT);
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.print("ACS712 30A");
  delay(1000);
  lcd.setCursor(0,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.print("hello");
  Voltage = getVPP();
  //VRMS = (Voltage/2.0) * 0.707; // root 2 is 0.707
  VRMS = ((Voltage - offsetVoltage)/mVperAmp);
  AmpsRMS = (VRMS)/(sqrt(2));
  lcd.setCursor(0,1);
  lcd.print(AmpsRMS);
  lcd.print("A RMS");
  delay(1000);
  lcd.clear();
//   Voltage = analogRead(sensorIn);
//   lcd.setCursor(0,1);
//   lcd.print(Voltage);
//   delay(500);
//   lcd.clear();
}
float getVPP(){
  float result;
  int readValue;
  int maxValue = 0;
  int minValue = 1024;
      
  for(int i =0; i<500;i ++){
     readValue = analogRead(sensorIn);
     if (readValue > maxValue){ 
         maxValue = readValue;
     }
  }
  
  result = (maxValue / 1024.0) * 5000;
  return result;
}
