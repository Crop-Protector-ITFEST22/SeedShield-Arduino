#include <LiquidCrystal.h>

String readString;

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  lcd.begin(16, 2); // set up number of columns and rows
  lcd.setCursor(0,0);
  lcd.println("SeedShield!");
}

void loop() {
 while (Serial.available()) {
    delay(10);  //small delay to allow input buffer to fill
    char c = Serial.read();  //gets one byte from serial buffer
    blinkLed(13, true);
    if (c == ',') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c; 
  } //makes the string readString  

  if (readString.length() >0) {
    Serial.println(readString); //prints string to serial port out
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(readString);
    delay(1000 * 5);

    readString=""; //clears variable for new input
  } else {
    lcd.clear();
    lcd.println("Waiting..");
  }

  delay(100);
}

void blinkLed(int pin, boolean fast) {
    if (!fast) {
      digitalWrite(pin, HIGH);
      delay(250);
      digitalWrite(pin, LOW);
      delay(250);
    } else {
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(1000);
    }
}
