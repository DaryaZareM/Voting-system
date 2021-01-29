//client
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <stdint.h>
#include <string.h>

String candidates[3] = {"Hilary", "Obama", "Trump"};
//keypad init
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'n','0','=','+'}
};
byte rowPins[ROWS] = {A4,A5,A6,A7}; 
byte colPins[COLS] = {A3,A2,A1,A0};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//lcd init
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  lcd.begin(16, 4);
//   sprintf(candidate," ");
//  mode=0;//set mode to default
}

byte x = 0;

void loop() {
  //menu
  lcd.setCursor(0,0);
  for(int i=0; i<3; i++){
    lcd.print(i+1);
    lcd.print(candidates[i]);
  }
  char vote;
  vote=keypad.waitForKey();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("on/c: reset");
  lcd.setCursor(0,1);
  lcd.print("+: set");

  char key;
  key=keypad.waitForKey();
  if(key=='+'){ //SET
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("YOU VOTED TO ");
    lcd.setCursor(0,1);
    lcd.print(candidates[int(vote)-49]);
    delay(500);
    //send to server
    Serial.write(vote);
  }else if(key=='n'){ //RESET
    lcd.clear();
    lcd.print("choos again plz...");
    delay(500);
  }
}
