#include "Arduino.h"
#include "lock.h"

bool authorised = false;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 48, 47, 46, 45 };  //10,9,8,7
byte colPins[COLS] = { 44, 43, 42, 41 };  //6,5,4,3

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myServo;

LiquidCrystal_I2C lcd(0x27, 20, 4);

MFRC522 mfrc522(SS_PIN, RST_PIN);

void lockSetup() {

  SPI.begin();

  mfrc522.PCD_Init();

  TCA9548A(4);

  lcd.init();

  lcd.backlight();

  lcd.clear();

  lcd.print("Place RFID tag"); 

  myServo.attach(11);
  myServo.write(0);
}

void lock_op(String targetWard) {

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    String content = "";

    for (byte i = 0; i < mfrc522.uid.size; i++) {

      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));

    }
    content.toUpperCase();

    if (content.substring(1) == "37 6A F2 31") {// White card, 
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("White Card.");

      String password = readKeypad(0);
      password.toUpperCase();

      if (password == "123A") {
        myServo.write(90);
        // Add closing thing here, 
        String closer = readKeypad(0);
        closer.toUpperCase();

        if (closer == "****") {
          myServo.write(0); 

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Medicine Secured...");  

          delay(2000);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Destination");
          lcd.setCursor(0, 1);
          lcd.print("1 = Palliative Care");
          lcd.setCursor(0, 2);
          lcd.print("2 = Cardiology");
          lcd.setCursor(0, 3);
          lcd.print("3 = Maternity");  

          String destination = readKeypad(1);

          if (destination == "1") {
            targetWard = "red";
              
          } else if (destination == "2") {
            targetWard = "blue";  
                     
          } else if (destination == "3") {
            targetWard = "yellow";
          }           
                         
        }
      } else if (password == "1A*D") {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("karate keef");
      }

    } else if (content.substring(1) == "92 6C EB 02") {// Blue fob, 
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Blue Fob.");

      String password = readKeypad(0);
      password.toUpperCase();

      if (password == "789C") {
        myServo.write(90); 
        // Add closing thing here,    
        String closer = readKeypad(0);
        closer.toUpperCase();
        
        if (closer == "****") {
          myServo.write(0); 

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Medicine Secured...");  

          delay(2000);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Destination");
          lcd.setCursor(0, 1);
          lcd.print("1 = Palliative Care");
          lcd.setCursor(0, 2);
          lcd.print("2 = Cardiology");
          lcd.setCursor(0, 3);
          lcd.print("3 = Maternity");

          String destination = readKeypad(1);

          if (destination == "1") {
            targetWard = "red";
              
          } else if (destination == "2") {
            targetWard = "blue";  
                     
          } else if (destination == "3") {
            targetWard = "yellow";
          }      
        }          
      }    

    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Data invalid.");
    }
  }
}

String readKeypad(int mode) {
  String input = "";
  if (mode == 0) {
    while (input.length() < 4) {
      char key = keypad.getKey();   
      if (key != NO_KEY) {
        input += key;
      }
    }  
  } else if (mode == 1) {
    input = keypad.getKey();    
  }  


  return input;
}
