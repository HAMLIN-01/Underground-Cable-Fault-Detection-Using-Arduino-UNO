#include <LiquidCrystal.h>           
LiquidCrystal lcd(2,3,4,5,6,7);
#define sensor A0
#define relay1 8
#define relay2 9
#define relay3 10
#define redLED 1
#define yellowLED 11
#define blueLED 12
#define buzzer 13
int read_ADC;
int distance; 
byte symbol[8]={
  B00000,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00000
}; 
void setup() {
  pinMode(sensor, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  lcd.createChar(1, symbol);
  lcd.begin(16, 2); 
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Cable Fault Test");
  lcd.setCursor(0, 1);
  lcd.print("Fault Detection");
  delay(2000);  
  lcd.clear();  
}
void loop() {
  lcd.setCursor(1,0);
  lcd.print("R");
  lcd.write(1);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  delay(500);
  data();

  lcd.setCursor(0, 1);
  if (distance > 0) {
    lcd.print(distance);
    lcd.print("Km ");
    digitalWrite(redLED, HIGH); 
  } else {
    lcd.print(" NF ");
    digitalWrite(redLED, LOW);  
  }
  lcd.setCursor(7,0);
  lcd.print("Y");
  lcd.write(1);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  delay(500);
  data();

  lcd.setCursor(6, 1);
  if (distance > 0) {
    lcd.print(distance);
    lcd.print("Km ");
    digitalWrite(yellowLED, HIGH);  
  } else {
    lcd.print(" NF ");
    digitalWrite(yellowLED, LOW);  
  }
  lcd.setCursor(13,0);
  lcd.print("B");
  lcd.write(1);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH); 
  delay(500);
  data();

  lcd.setCursor(12, 1);
  if (distance > 0) {
    lcd.print(distance);
    lcd.print("Km ");
    digitalWrite(blueLED, HIGH);  
  } else {
    lcd.print(" NF ");
    digitalWrite(blueLED, LOW);   
  }
}
void data()
{
  read_ADC=analogRead(sensor);
  distance=read_ADC/100;
  if(distance>9)distance=0;
  if(distance>0){
    digitalWrite(buzzer,HIGH);
    delay(1000);
    digitalWrite(buzzer,LOW);
  }
}
