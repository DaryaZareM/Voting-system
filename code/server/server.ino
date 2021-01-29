//server
//client
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <stdint.h>
#include <string.h>
#define  nominates 3
#define Dev_add 0b1010000
#define ADDR_Ax 0b000 //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax

int votes[nominates]={0};
String candidates[nominates] = {"Hilary", "Obama", "Terump"};

//lcd init
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void show();

void writeEEPROM(int address){
    Wire.beginTransmission(Dev_add);
    Wire.write(100+address);
    Wire.write(votes[address]);
    Wire.endTransmission();
}

void writeI2CByte(byte data_addr, byte data){
  Wire.beginTransmission(Dev_add);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr){
  byte data = NULL;
  Wire.beginTransmission(Dev_add);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(Dev_add, 1); //retrieve 1 returned byte
  delay(1);
  if(Wire.available()){
    data = Wire.read();
  }
  lcd.print(data);
  return data;
}

void setup() {
  Wire.begin();
  lcd.begin(16, 4);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  
  for(int i=0;i<3;i++){
  //votes[i] = readI2CByte(100+i);
  
  }
    
}

void loop() {
  show();
 
   if (Serial.available() > 0) {
    int incoming = int (Serial.read());
    incoming = incoming-49;
    lcd.clear();
    lcd.setCursor(0,4);
    lcd.print("received:");
    lcd.println(candidates[incoming]);
    votes[incoming]++;
    writeEEPROM(incoming);
    delay(200);
  }
  
  if (Serial1.available() > 0) {
    int incoming = int (Serial1.read());
    incoming = incoming-49;
    lcd.clear();
    lcd.setCursor(0,4);
    lcd.print("received:");
    lcd.println(candidates[incoming]);
    votes[incoming]++;
    writeEEPROM(incoming);
    delay(100);
  }
  
    if (Serial2.available() > 0) {
    int incoming = int (Serial2.read());
    incoming = incoming-49;
    lcd.clear();
    lcd.setCursor(0,4);
    lcd.print("received:");
    lcd.println(candidates[incoming]);
    votes[incoming]++;
    writeEEPROM(incoming);
    delay(100);
  }
  
    if (Serial3.available() > 0) {
    int incoming = int (Serial3.read());
    incoming = incoming-49;
    lcd.clear();
    lcd.setCursor(0,4);
    lcd.print("received:");
    lcd.println(candidates[incoming]);
    votes[incoming]++;
    writeEEPROM(incoming);
    delay(100);
  }
  delay(100);
 
}


void show(){
  lcd.clear();
  for(int i=0;i<nominates;i++){
    lcd.setCursor(0,i);
    lcd.print(candidates[i]);
    lcd.setCursor(7,i);
    lcd.print(votes[i]);
  }
}
