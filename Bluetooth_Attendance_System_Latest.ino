#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include<LiquidCrystal.h>

//Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,6,5,4,3,2);

uint8_t getFingerprintEnroll(uint8_t id);

SoftwareSerial mySerial(11, 10);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int process=0;
int numberpressed=0;
int IDNumber;
String fingerID="";

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {12, 9, 8};    //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()  
{
  Serial.begin(9600);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  //lcd display
  lcd.begin(16,2);
  //
  delay(500);
  //
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initializing....");
  lcd.setCursor(0,1);
  lcd.print("Please Wait..!!!");
  //
  delay(500);
  //
  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Finger Print  ");
    lcd.setCursor(0,1);
    lcd.print("   Attendance   ");
    delay(3000);
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("       By       ");
//    lcd.setCursor(0,1);
//    lcd.print("David .O. Daniel");
//    delay(3000);
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention User!!");
    lcd.setCursor(0,1);
    lcd.print("Sensor Unpluged.");
    while (1);
  }
  lcd.clear();
  process = 2;
}

void loop()                     // run over and over again
{
  char customKey = customKeypad.getKey();
  if (customKey){
    process=0;
    if(customKey=='0'){
      numberpressed=0;
    }
    if(customKey=='1'){
      numberpressed=1;
    }
    if(customKey=='2'){
      numberpressed=2;
    }
    if(customKey=='3'){
      numberpressed=3;
    }
    if(customKey=='4'){
      numberpressed=4;
    }
    if(customKey=='5'){
      numberpressed=5;
    }
    if(customKey=='6'){
      numberpressed=6;
    }
    if(customKey=='7'){
      numberpressed=7;
    }
    if(customKey=='8'){
      numberpressed=8;
    }
    if(customKey=='9'){
      numberpressed=9;
    }
    if(customKey=='C'){
      fingerID = "";
      IDNumber = fingerID.toInt();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter FingerID:");
      lcd.setCursor(0,1);
      lcd.print("               ");
    }
    if (customKey!='*' && customKey!='#' && customKey!='C'){
      fingerID += numberpressed;
      IDNumber = fingerID.toInt();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter FingerID:");
      lcd.setCursor(0,1);
      lcd.print(IDNumber); 
    }
    if (customKey=='*'){
      if (IDNumber>=1){
        newregistration();
      }
      if (fingerID == ""){
        fingerID = "";
        IDNumber = fingerID.toInt();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter FingerID:");
      }
    }
    if (customKey=='#'){
      process=2;
    }    
  }
  if (process==2){
    lcd.setCursor(0,0);
    lcd.print("Place Finger For");
    lcd.setCursor(0,1);
    lcd.print("Class Attendance");
    getFingerprintIDez();
    delay(50);
  }
}
//
//
void newregistration(){
  int id = IDNumber;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enrolling ID:");
  lcd.setCursor(13,0);
  lcd.print(id);
  delay(2000);
  while (!getFingerprintEnroll(id));             
}
//
//
uint8_t getFingerprintEnroll(uint8_t id) {
  uint8_t p = -1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please...! Place");
  lcd.setCursor(0,1);
  lcd.print("your Finger Now!");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Thanks!!! Finger");
    lcd.setCursor(0,1);
    lcd.print("Image Captured!!");
    delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
    lcd.setCursor(0,0);
    lcd.print("Please...! Place");
    lcd.setCursor(0,1);
    lcd.print("your Finger Now!");  
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Imaging Error!!!");
    delay(1000);
      break;
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Image Converted ");
    lcd.setCursor(0,1);
    lcd.print("Successfully!!!!");
    delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finger Image Too");
    lcd.setCursor(0,1);
    lcd.print("Messy Try Again.");
    delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
      return p;
  }
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Remove Finger ");
    lcd.setCursor(0,1);
    lcd.print("and Wait Please");
    delay(2000);
    p = 0;
    while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

    p = -1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Please...! Place");
    lcd.setCursor(0,1);
    lcd.print("your Finger Now!");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Thanks!!! Finger");
    lcd.setCursor(0,1);
    lcd.print("Image Captured!!");
    delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
    lcd.setCursor(0,0);
    lcd.print("Please...! Place");
    lcd.setCursor(0,1);
    lcd.print("your Finger Now!");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Imaging Error!!!");
    delay(1000);
      break;
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Image Converted ");
    lcd.setCursor(0,1);
    lcd.print("Successfully!!!!");
    delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finger Image Too");
    lcd.setCursor(0,1);
    lcd.print("Messy Try Again.");
    delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
      return p;
  }
  
  
  // OK converted!
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finger Matched!!");
    fingerID = "";
    IDNumber = fingerID.toInt();
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger not Match");
    delay(1000);
    return p;
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
    return p;
  }   
  
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.print("W");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Could not Store!");
    lcd.setCursor(0,1);
    lcd.print("in the Location.");
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Writing to Flash");
    lcd.setCursor(0,1);
    lcd.print("Error..Restart!!");
    delay(1000);
    return p;
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
    return p;
  }   
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Image Taken   ");
    lcd.setCursor(0,1);
    lcd.print("Successfully!!!!");
    delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
      return p;
    case FINGERPRINT_IMAGEFAIL:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Imaging Error!!!");
    delay(1000);
      return p;
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Image Converted ");
    lcd.setCursor(0,1);
    lcd.print("Successfully!!!!");
    delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finger Image Too");
    lcd.setCursor(0,1);
    lcd.print("Messy Try Again.");
    delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger Not Found");
    delay(1000);
      return p;
    default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finger Matched!!");
    fingerID = "";
    IDNumber = fingerID.toInt();
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Communication...");
    lcd.setCursor(0,1);
    lcd.print("Error.....Wait!!");
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Attention Please");
    lcd.setCursor(0,1);
    lcd.print("Finger not Match");
    delay(1000);
    return p;
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error...");
    lcd.setCursor(0,1);
    lcd.print("Restart Device!!");
    delay(1000);
    return p;
  }   
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK){
    //Serial.println("0");
    return -1;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK){
    //Serial.println("0"); 
    return -1;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){
    //Serial.println("0"); 
    return -1;
  }
  // found a match!
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Finger ID Found!");
  lcd.setCursor(0,1);
  lcd.print("ID Number:");
  lcd.setCursor(10,1);
  lcd.print(finger.fingerID);
  delay(500); 
  Serial.println(finger.fingerID);
  Serial.flush();
  delay(500); 
  for(int i = 0; i <= 300; i++){
    if(Serial.available() > 0){
      i = 300;
      //
      String readText = "";
      //
      readText = Serial.readStringUntil('\n');
      delay(10);
      readText.toUpperCase();
      //
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Matric Number:  ");
      lcd.setCursor(0,1);
      lcd.print(readText);
      //
      delay(3000);
    }
    delay(10);
  }
  lcd.clear();
  return finger.fingerID; 
}
