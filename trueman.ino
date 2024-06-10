#include <LiquidCrystal.h>

int phase1 = 10;
int phase2 = 9;
int phase3 = 8;
int relay = 13;
int temperature = A1;
float temperature_threshold = 30.0;
int temp_ok = 1;
float temp_before = 0.0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(20, 4);

  pinMode(phase1,INPUT);
  pinMode(phase2,INPUT);
  pinMode(phase3,INPUT);
  pinMode(relay,OUTPUT);
  
  pinMode(temperature,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int phase1value = digitalRead(phase1);
  int phase2value = digitalRead(phase2);
  int phase3value = digitalRead(phase3);
  float vout = analogRead(temperature);
  float temperature_value = (vout*500)/1023;

  if(temp_before > 0) {
    temperature_value = (temp_before + temperature_value) / 2;
    temp_before = 0;
  } else {
    temp_before = temperature_value;
  }

  float deg = 25.0 + (25.0-temperature_value);
  if(deg > temperature_threshold) {
    temp_ok = 0;
  }

  if(temp_ok == 1) {
    if (phase1value == 1 && phase2value == 1 && phase3value == 1) {
      digitalWrite(relay,LOW);
    } else {
      digitalWrite(relay,HIGH);
    }
  } else {
    digitalWrite(relay,HIGH);
  }
  
  lcd.setCursor(0, 0);  
  lcd.print("Phase1: ");
  lcd.print(phase1value);
  lcd.setCursor(0, 1);
  lcd.print("Phase2: ");
  lcd.print(phase2value);
  lcd.setCursor(0, 2);
  lcd.print("Phase3: ");
  lcd.print(phase3value);
  lcd.setCursor(0, 3);
  lcd.print("Temp: ");
  lcd.print(deg);

  Serial.println(deg);
  delay(500);
}