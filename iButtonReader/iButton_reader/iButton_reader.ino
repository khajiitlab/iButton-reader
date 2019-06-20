#include <OneWire.h>
#include <LiquidCrystal.h>


//Arduino nano : D7,  D6,  D5,  D4,  D3, D2
//LCD          : DB7, DB6, DB5, DB4, E , RS

int RS = 2;
int E = 3;
int DB4 = 4;
int DB5 = 5;
int DB6 = 6;
int DB7 = 7;

LiquidCrystal lcd(DB7, DB6, DB5, DB4, E, RS);
OneWire  ds(10);
byte counter = 0;
 
void setup(void) {
  Serial.begin(9600); 
  lcd.begin(20, 2);
  lcd.setCursor(0, 0);
  lcd.print("Attach iButton...");
  Serial.print("Attach iButton...");
}
 
void loop(void) {
  byte addr[8];
     
  if ( !ds.search(addr)) {
    ds.reset_search();
    counter++;
    delay(100);

    if (counter >= 50) {
      counter = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Attach iButton...");
    }
    return;
  }

  counter = 0;
  lcd.clear(); 
  lcd.setCursor(0, 0);
  
  for(byte i = 0; i < 8; i++) {
    if (addr[i] < 0x10) { 
      lcd.print("0");
      Serial.print("0");
    }
    lcd.print(addr[i], HEX);
    Serial.print(addr[i], HEX);
  }
 
  if ( OneWire::crc8( addr, 7) != addr[7]) {
    lcd.setCursor(0, 1);
    lcd.print("CRC is not valid!");
    Serial.println("CRC is not valid!");
    return;
  }
   
  ds.reset();
   
  delay(1000);
}
