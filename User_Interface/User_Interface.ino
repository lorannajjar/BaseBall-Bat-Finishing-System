#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Keypad.h>

//defining new colors
#define ILI9341_GRAY 0xA510
//
//
int devModeEn = 0;

//Stepper motors variables/setup
int CLOCK1 = 11, DIR1 = 10, CLOCK2 = 13, DIR2 = 12;

int stepCount = 1;
int cycleCount = 1;
int stepsPerRev = 2000;

float angleIndex = 15;
float stepsIndex = 360/angleIndex;

float anglePoly = 2;
float stepsPoly = stepsPerRev/anglePoly;

float rpm = 150;

float delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;

float batLength = 24;
float batCircum = 8.2;
float woodType = 0;

//Solenoid setup
int sig = 8;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
/*
char hexaKeys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};
*/

byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39, 41, 43, 45}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// For the Adafruit shield, these are the default.
#define TFT_DC 8
#define TFT_CS 9

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void SPI_WriteCom(byte byInst)
{
  digitalWrite(TFT_CS,LOW);
  digitalWrite(TFT_DC,LOW);
  SPI.transfer(byInst);
//  delay(1);
  digitalWrite(TFT_CS,HIGH);
 
//  delay(1);
}

void SPI_WriteData(word byData)
{
  digitalWrite(TFT_CS,LOW);
  digitalWrite(TFT_DC,HIGH);
  SPI.transfer(byData);
//  delay(1);
  digitalWrite(TFT_CS,HIGH);
 
//  delay(1);
}  

//ILI9341,2.8" TN PANEL,240(RGB)*320,Initialization
void LCD_Init(){
SPI_WriteCom(0xCF);
  SPI_WriteData(0x00);
  SPI_WriteData(0xD9);
  SPI_WriteData(0X30);

  SPI_WriteCom(0xED);
  SPI_WriteData(0x64);
  SPI_WriteData(0x03);
  SPI_WriteData(0X12);
  SPI_WriteData(0X81);

  SPI_WriteCom(0xE8);
  SPI_WriteData(0x85);
  SPI_WriteData(0x10);
  SPI_WriteData(0x78);

  SPI_WriteCom(0xCB);
  SPI_WriteData(0x39);
  SPI_WriteData(0x2C);
  SPI_WriteData(0x00);
  SPI_WriteData(0x34);
  SPI_WriteData(0x02);

  SPI_WriteCom(0xF7);
  SPI_WriteData(0x20);

  SPI_WriteCom(0xEA);
  SPI_WriteData(0x00);
  SPI_WriteData(0x00);

  SPI_WriteCom(0xC0);    //Power control
  SPI_WriteData(0x21);    //VRH[5:0]

  SPI_WriteCom(0xC1);    //Power control
  SPI_WriteData(0x12);    //SAP[2:0];BT[3:0]

  SPI_WriteCom(0xC5);    //VCM control
  SPI_WriteData(0x31);
  SPI_WriteData(0x3C);

  SPI_WriteCom(0xC7);    //VCM control2
  SPI_WriteData(0xC4);    //C2 水波纹调试，如有请向上调两

  SPI_WriteCom(0x36);    // Memory Access Control
  //SPI_WriteData(0xa4);   // landscape
  SPI_WriteData(0x64);   // landscape the other direction
  //SPI_WriteData(0x00);     // Vertical 
  //SPI_WriteData(0xC0);     // Vertical the other direction

  SPI_WriteCom(0x3A);
  SPI_WriteData(0x55);

  SPI_WriteCom(0xB1);
  SPI_WriteData(0x00);
  SPI_WriteData(0x15);

  SPI_WriteCom(0xB6);    // Display Function Control
  SPI_WriteData(0x0A);
  SPI_WriteData(0xA2);

  SPI_WriteCom(0xF2);    // 3Gamma Function Disable
  SPI_WriteData(0x00);

  SPI_WriteCom(0x26);    //Gamma curve selected
  SPI_WriteData(0x01);

  SPI_WriteCom(0xE0);    //Set Gamma
  SPI_WriteData(0x0F);
  SPI_WriteData(0x20);
  SPI_WriteData(0x1E);
  SPI_WriteData(0x09);
  SPI_WriteData(0x12);
  SPI_WriteData(0x0B);
  SPI_WriteData(0x50);
  SPI_WriteData(0XBA);
  SPI_WriteData(0x44);
  SPI_WriteData(0x09);
  SPI_WriteData(0x14);
  SPI_WriteData(0x05);
  SPI_WriteData(0x23);
  SPI_WriteData(0x21);
  SPI_WriteData(0x00);

  SPI_WriteCom(0XE1);    //Set Gamma
  SPI_WriteData(0x00);
  SPI_WriteData(0x19);
  SPI_WriteData(0x19);
  SPI_WriteData(0x00);
  SPI_WriteData(0x12);
  SPI_WriteData(0x07);
  SPI_WriteData(0x2D);
  SPI_WriteData(0x28);
  SPI_WriteData(0x3F);
  SPI_WriteData(0x02);
  SPI_WriteData(0x0A);
  SPI_WriteData(0x08);
  SPI_WriteData(0x25);
  SPI_WriteData(0x2D);
  SPI_WriteData(0x0F);

  SPI_WriteCom(0x35); //TE ON
  SPI_WriteData(0x00);

  
  SPI_WriteCom(0x2A); //
  SPI_WriteData(0x00);
  SPI_WriteData(0x00);
  SPI_WriteData(0x00);
  SPI_WriteData(0xEF);
  //SPI_WriteData(0x00);
  //SPI_WriteData(0x00);

  SPI_WriteCom(0x2B); //
  SPI_WriteData(0x00);
  SPI_WriteData(0x00);
  SPI_WriteData(0x01);
  SPI_WriteData(0x3F);
  //SPI_WriteData(0x00);
  //SPI_WriteData(0x00);  

  SPI_WriteCom(0x11);
  delay(120);      //Delay 120ms

  SPI_WriteCom(0x29); //display on
  SPI_WriteCom(0x2c);
}
///End Initialization

void setup() {
  Serial.begin(9600);
  //Stepper motors setup
  pinMode(CLOCK1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(CLOCK2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(reverseSwitch), revmotor, FALLING);

  //Solenoid setup
  pinMode(sig, OUTPUT);
 
  tft.begin();
  tft.setRotation(1);
  //set display 240 X 320
  LCD_Init();

  welcome();
}

void loop(void) {

  char welcomeKey = customKeypad.getKey();
 
  if (welcomeKey){
  switch (welcomeKey) {
  case '#': // main menu
  {
    mainMenu();
   break;
  }
  default:
  {
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    welcome();
    break;
    }
  } 
  }
  delay(10);
}

//This function to print welcome message
void welcome(){
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
  tft.println("--Welcome--");
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  tft.println(" Press '#' to begin!");
}

//This function to print main menu and options
void mainMenu() {

  char mainMenuKey = NULL;
  
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
  tft.println("--Main Menu--");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  tft.println(" A. User Mode");
  tft.println(" B. Developer Mode");
  tft.println(" C. Test Mode");

  while (mainMenuKey == NULL)
  {
    mainMenuKey = customKeypad.getKey();
  }
  mainMenuLoop(mainMenuKey);

}

//This function to take in keypad input for main menu
void mainMenuLoop(char mainMenuKey) {


  if (mainMenuKey){
  switch (mainMenuKey) {
  case 'A': // User Mode
    userModeMenu();
    break;
  case 'B': // Developer Mode
    developerModeMenu();
    break;
  case 'C': // Test Mode
    testModeMenu();
    break;
  case '#': // return to main Menu
    tft.print("");
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Already in Main Menu");
    delay(1000);
    mainMenu();
    break;
  default:
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    mainMenu();
    break;
    }
  } 
  delay(10);
}
//This function to print user mode menu and options
void userModeMenu() {
  char userModeKey = NULL;
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
  tft.println("--User Mode--");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.75);
  tft.println(" A. Operation");
  tft.println(" B. Configurations");
  tft.println(" #. Main Menu");

  while (userModeKey == NULL)
  {
    userModeKey = customKeypad.getKey();
  }

  userModeLoop(userModeKey);
}

//This function to take in keypad input for userMode
void userModeLoop(char input) {
  if (input){
  switch (input) {
  case 'A': // Operation
    operations();
    break;
  case 'B': // Configuration
    configurations();
    break;
   case '#': // return to main Menu
    mainMenu();
    break;
  default:
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    userModeMenu();
    break;
    }
  } 
  delay(10);
}

void operations(){

  char opKey = NULL;
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Configurations:");
  tft.setTextSize(0.6);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  tft.print("Bat Length: "); tft.println(batLength);
  tft.print("Bat Circumference: "); tft.println(batCircum);
  tft.print("Wood Type: "); tft.println(woodType);
  tft.println(" ");
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);
  tft.println("Press '1' to START");
  tft.setTextColor(ILI9341_RED);
  tft.println("Press '#' to return to main menu");

  while (opKey == NULL) {
    opKey = customKeypad.getKey();
  }

  if(opKey){
    switch(opKey){
      case '1':
      StepForward(delay_time);
      StepForward180(delay_time);
      tft.fillScreen(ILI9341_NAVY);
      tft.setCursor(5,0);
      tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
      tft.println("Configurations:");
      tft.setTextSize(0.6);
      tft.println(" ");
      tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
      tft.print("Bat Length: "); tft.println(batLength);
      tft.print("Bat Circumference: "); tft.println(batCircum);
      tft.print("Wood Type: "); tft.println(woodType);
      break;
      default:
      break;
    }
  }
}

void configurations (){
  char configKey = NULL;
 

  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3.50);
  tft.println("--Configurations--");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.75);
  tft.println(" Select Configuration");
  tft.setTextSize(2);
  tft.println(" (1) Bat 1");
  tft.println(" (2) Bat 2");
  tft.println(" (3) Bat 3");
  tft.println(" (4) Bat 4");
  tft.println(" #. Main Menu");

  while (configKey == NULL) {
    configKey = customKeypad.getKey();
  }

  if (configKey){
  switch (configKey) {
  case '1': // bat 1
    batLength = 24;
    batCircum = 8.2;
    woodType = 0;
    break;
  case '2': // bat 2
    batLength = 28;
    batCircum = 7.2;
    woodType = 1;
    break;
  case '3': // bat 3
    batLength = 30;
    batCircum = 6;
    woodType = 1;
    break;
  case '4': //bat 4
    batLength = 34;
    batCircum = 5;
    woodType = 2;
    break;
  case '#': // return to main Menu
    mainMenu();
    break;
  default:
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    configurations();
    break;
    }
  } 
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Configuration set!");
  tft.setTextSize(0.6);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  tft.print("Bat Length: "); tft.println(batLength);
  tft.print("Bat Circumference: "); tft.println(batCircum);
  tft.print("Wood Type: "); tft.println(woodType);
  tft.println(" ");
  tft.println(" ");
  tft.setTextColor(ILI9341_RED);
  tft.println("Press '#' to return to main menu");

  while (configKey != '#') {
    configKey = customKeypad.getKey();
  }
  mainMenu();

  
}

//This function to print developer mode menu and options
void developerModeMenu() {

  char developerModeKey = NULL;
  
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("--Developer Mode--");
  tft.setTextSize(0.6);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  tft.println(" 1. Bat Length");
  tft.println(" 2. Bat Circumference");
  tft.println(" 3. Wood Type");
  tft.println(" 4. Travel Speed");
  tft.println(" 5. Rotation Angle");
  tft.println(" 6. Poly Angle");
  tft.println(" 7. Force");
  tft.println(" #. Main Menu");

  while (developerModeKey == NULL)
  {
    developerModeKey = customKeypad.getKey();
  }

  developerModeLoop(developerModeKey);
  
  
  
}

//This function to take in keypad input for developerMode
void developerModeLoop(char input) {
  if (input){
  switch (input) {
  case '1': // bat length
    changeValues(batLength, 1, 24, 34, "Bat Length");
    break;
  case '2': // bat circumference
    changeValuesCircum(batCircum, 0.1, 4, 8.6, "Bat Circumference");
    break;
  case '3': // wood type
    //maybe #define type0 0, at the top
    //type: 0, 1, 2
    //int woodType = 0, 1, 2
    changeValues(woodType, 1, 0, 2, "Wood Type");
    break;
  case '4': // travel speed
    //function under test
    //travelSpeed();
    changeValues(rpm, 10, 10, 500, "RPM SPEED");
    Serial.println(rpm);
    delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    Serial.println(delay_time);
    delay(2000);
    break;
  case '5': // rotation angle
    //add function to change rotation angle
    changeValues(angleIndex, 1, 1, 30, "rotation angle");
    stepsIndex = 360/angleIndex;
    //delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    break;
  case '6': // poly angle
    //add function to change poly angle
    changeValues(anglePoly, 0.1, 0.1, 4, "poly angle");
    stepsPoly = stepsPerRev/anglePoly;
    //delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    break;
  case '7': // force
    //add function to change force option
    break;
  case '#': // return to main Menu
    mainMenu();
    break;
  default:
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    developerModeMenu();
    break;
    }
  } 
  delay(10);
}

//use this function to change "input" to increment it or/and decrement it by "changeBy"
void changeValues(float &input, float changeBy, float minValue, float maxValue, char *textName) {
  int temSpeed = -1;
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3.5);
  tft.println(textName);
  tft.println(" ");
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
  tft.println("press # to exit");
  tft.println("press 1 to Increment");
  tft.println("press 3 to Decrement");
  tft.setCursor(14, 158);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.print(textName);tft.print(":  "); 
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.print(input);

  char keyIn = 's';
  while(keyIn != '#') {
    //display updated value everytime we increase/decrease speed
    if(temSpeed != input) {
      temSpeed = input;
      tft.setCursor(14, 158);
      tft.print(textName);tft.print(":  "); 
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.print(input);tft.print("  ");
    }
  }
}

void changeValuesCircum(float &input, float changeBy, float minValue, float maxValue, char *textName) {
  int temSpeed = -1;
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3.5);
  tft.println(textName);
  tft.println(" ");
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
  tft.println("press # to exit");
  tft.println("press 1 to Increment");
  tft.println("press 3 to Decrement");
  tft.setCursor(14, 158);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.print(textName);tft.print(":  "); 
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.print(input);

  char keyIn = 's';
  while(keyIn != '#') {
    //display updated value everytime we increase/decrease speed
    if(temSpeed != input) {
      temSpeed = input;
      tft.setCursor(14, 158);
      tft.print(textName);tft.print(":  "); 
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.print(input);tft.print("  ");
    }

    //if 1 speed - changeBy
    if(keyIn == '1') {
      if(input > minValue) {
        input -= changeBy;
      }
    } 
    //if 2 speed + changeBy
    else if(keyIn == '3') {
      if(input < maxValue) {
        input += changeBy;
      }
    }
    delay(30);
    keyIn = customKeypad.getKey();
  }
}

/*
//use this function to be able to change
//the value of delay_time (motor speed) as example
void travelSpeed() {
  int temSpeed = -1;
  int upDownValue = 50;
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3.5);
  tft.println("Travel Speed");
  tft.println(" ");
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
  tft.println("press # to exit");
  tft.println("press 1 to Increment Speed");
  tft.println("press 3 to Decrement Speed");
  tft.fillRect(10,150, 222, 35, ILI9341_BLACK);
  tft.drawRect(10,150, 222, 35, ILI9341_RED);
  tft.setCursor(14, 158);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.print("Travel Speed: "); tft.println(delay_time);
  char keyIn = 's';
  while(keyIn != '#') {
    //display updated value everytime we increase/decrease speed
    if(temSpeed != delay_time) {
      temSpeed = delay_time;
      tft.fillRect(10,150, 222, 35, ILI9341_BLACK);
      tft.drawRect(10,150, 222, 35, ILI9341_RED);
      tft.setCursor(14, 158);
      tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
      tft.print("Travel Speed: "); tft.println(delay_time);
    }
    //if 1 speed - upDownValue(50)
    if(keyIn == '1') {
      if(delay_time > 50) {
        delay_time -= upDownValue;
      }
    } 
    //if 2 speed + upDownValue(50)
    else if(keyIn == '3') {
      if(delay_time < 1050) {
        delay_time += upDownValue;
      }
    }
    delay(30);
    keyIn = customKeypad.getKey();
  }
}
*/

//This function to print test menu and options
void testModeMenu() {
  char testModeKey = NULL;
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
  tft.println("--Test Mode--");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(3);
  tft.println(" A. Display  Test");
  tft.println(" B. Motor    Test");
  tft.println(" C. Solenoid Test");
  tft.println(" D. Keypad   Test");
  tft.println(" 0. All      Test");
  tft.println(" #. Main Menu");

  while (testModeKey == NULL)
  {
    testModeKey = customKeypad.getKey();
  }
  testModeLoop(testModeKey);
}

//This function to take in keypad input for developerMode
void testModeLoop(char input) {
  if (input){
  switch (input) {
  case 'A': // display test
    displayTest();
    break;
  case 'B': // motor test
    motorTest();
    break;
  case 'C': // solenoid test
    solenoidTest();
    break;
  case 'D': // keypad test
    keypadTest();
    break;
  case '0': // ALL parts test
    AllTest(); 
    break;
  case '#': // return to main Menu
    mainMenu();
    break;
  default:
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    testModeMenu();
    break;
    }
  } 
  delay(10);
}

//delay_time for stepper motor speed
void StepForward(int delay_time)
{
  //int m1 = 5, m2 = 4, m3 = 50;
  //printInfo(rpm, angleIndex, cycleCount, 1, 0, 0);
  digitalWrite(DIR1, LOW);
  for (int i = 0; i < 1; i++)
  {
    for (int x = 0; x < stepsPerRev / stepsIndex; x++)
    {
      digitalWrite(CLOCK1, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK1, LOW);
      delayMicroseconds(delay_time);
      stepCount+1;
    }
    delay(delay_time);
  }
  //printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
  //printInfo(delay_time, m2, m3, 0, 0, 0);
}

//delay_time for stepper motor speed
//solenoidMode '0' to disable or '1' to enable solenoid
void StepForward180(int delay_time)
{
  //these can be passed different values
  int m1 = 5, m2 = 4, m3 = 50;
  //printInfo(m1, m2, m3, 0, 1, 1);

  //printInfo(rpm, angleIndex, cycleCount, 0, 1, 1);
  /*
  if(solenoidMode) {
    printInfo(rpm, angleIndex, cycleCount, 0, 1, 1);
    //printInfo(delay_time, angleIndex, cycleCount, 0, 1, 1);
    //printInfo(delay_time, m2, m3, 0, 1, 1);
    digitalWrite(sig, HIGH);
  } else {
    printInfo(rpm, angleIndex, cycleCount, 0, 1, 0);
    //printInfo(delay_time, angleIndex, cycleCount, 0, 1, 0);
    //printInfo(delay_time, m2, m3, 0, 1, 0);
  }
  */
  
  digitalWrite(DIR2, LOW);
  for (int i = 0; i < 1; i++)
  {
    for (int x = 0; x < stepsPoly; x++)
    {
      digitalWrite(CLOCK2, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK2, LOW);
      delayMicroseconds(delay_time);
    }
    delay(delay_time);
  }
  digitalWrite(DIR2, HIGH);
  for (int i = 1; i < 2; i++)
  {
    for (int x = 0; x < stepsPoly; x++)
    {
      digitalWrite(CLOCK2, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK2, LOW);
      delayMicroseconds(delay_time);
      cycleCount+1;
    }
    delay(delay_time);
  }
//  if(solenoidMode) {
//    digitalWrite(sig, LOW);
//  }
  //printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
  //printInfo(delay_time, m2, m3, 0, 0, 0);
}



//make 2 boxes and display informations
//display motors informations such as speed, direction
//function update both boxes
//maybe add a feature to only
//update the needed box(both, box1, box2)
void printInfo(int mValue, int mValue2, int mValue3, int motorEN, int motorEN2, int solenoidEN) {
  //int motor = mValue, motor1 = mValue2, motor2 = mValue3;
  
  //display motors and info
  //tft.setCursor(10, 150);
  //tft.fillRect(10,150, 140, 35, ILI9341_BLACK);
  tft.drawRect(10,150, 140, 35, ILI9341_RED);
  tft.drawRect(11,151, 138, 33, ILI9341_RED);
  tft.setCursor(14, 154);
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);  tft.setTextSize(1);
  tft.print("Motor RPM   : "); tft.print(mValue);tft.println("   ");
  tft.setCursor(14, 164); 
  tft.print("Motor Angle : "); tft.print(mValue2);tft.println("   ");
  tft.setCursor(14, 174); 
  tft.print("Cycle       : "); tft.print(mValue3);tft.println("   ");
  //tft.setCursor(14, 184); 
  //tft.print("Cycle       : "); tft.println(mValue4);

  
  //display motor on/off - solenoid on/off
  //tft.fillRect(155,150, 140, 35, ILI9341_BLACK);
  tft.drawRect(155,150, 140, 35, ILI9341_RED);
  tft.drawRect(156,151, 138, 33, ILI9341_RED);
  tft.setCursor(160, 154);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.print("Stepper Motor 1: ");
  if(!motorEN) {
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK); tft.println("OFF");
  } else {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); tft.println("ON ");
  }

  tft.setCursor(160, 164); tft.setTextColor(ILI9341_BLUE);
  tft.print("Stepper Motor 2: ");
  if(!motorEN2) { 
    tft.setTextColor(ILI9341_RED, ILI9341_BLACK); tft.println("OFF");
  } else {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); tft.println("ON ");
  }
  tft.setCursor(160, 174); tft.setTextColor(ILI9341_BLUE); 
  tft.print("Solenoid       : ");
  if(!solenoidEN) {
    tft.setTextColor(ILI9341_RED, ILI9341_BLACK); tft.println("OFF");
  } else {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); tft.println("ON ");
  }
  
}

int menuPrompt() {

  //tft.setCursor(2, 70);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.setCursor(10, 70); tft.println("Press 1 to START");
  tft.setCursor(10, 95); tft.println("Press 3 to Go Back!!");
  //tft.println("Press/hold # to EXIT");
  
  char keyIn = 's';
  //press 1 to start motor
  //press 0 to go back to mainMenu
  while(1) {
    //Serial.println("All Test inside while(1)");
    delay(10);
    keyIn = customKeypad.getKey();
    tft.setCursor(20, 220);
    tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(1);
    tft.println("Invalid Option...");
    if(keyIn) {
      if(keyIn == '1'){
        return 0;
      } else if(keyIn == '3') {
        return 1;
      }else {
        tft.setCursor(20, 220);
        tft.setTextColor(ILI9341_RED);  tft.setTextSize(1);
        tft.println("Invalid Option...");
        delay(500);
      }
    }
  }
}

//This function to test the solenoid
void AllTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3);
  tft.println("TEST ALL Parts");
  tft.println(" ");

  cycleCount = 0;
  //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
  printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  //printInfo(delay_time, 0, 0, 0, 0, 0);

  //int opt = menuPrompt();
  menuPrompt();

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3);
  tft.println("TEST ALL Parts");
  tft.println(" ");
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("Press/hold # to EXIT");

  /*
  if(opt)
    goto skip;
  */
    
  char keyIn = 's';
  //press/hold # to EXIT
  //this need to be looked at
  //sometimes it does NOT exit when # is pressed
  //cycleCount = 0;
  printInfo(rpm, angleIndex, cycleCount, 0, 0, 1);
  int i = 1;
  unsigned long start = 0;
  unsigned long endTime = 0;
  while(keyIn != '#') {
    start = micros();
    digitalWrite(sig, HIGH);
    //printInfo(rpm, angleIndex, cycleCount, 0, 0, 1);
    for (; i <= stepsIndex; i++)
    {
      printInfo(rpm, angleIndex, cycleCount, 1, 0, 1);
      StepForward(delay_time);
      printInfo(rpm, angleIndex, cycleCount, 0, 1, 1);
      StepForward180(delay_time);
      
      stepCount += 1;
      cycleCount += 1;
  
      Serial.println(stepCount);
      Serial.println(cycleCount);
      keyIn = customKeypad.getKey();
      if(keyIn == '#') break;
    }
    digitalWrite(sig, LOW);
    endTime = micros() - start;

    Serial.println(endTime);
    //delay(stepsPerRev);
//    p = analogRead(A0);
//    delay_time = map(p, 0, 1023, 50, 1000);

    //delay_time = 100;
    keyIn = customKeypad.getKey();
    printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  }
  //printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  //skip:
  delay(500);
  mainMenu();
}


//This function to test the solenoid
void motorTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.println("Test Motor");
  tft.println(" ");

  cycleCount = 0;
  //printInfo(delay_time, 0, 0, 0, 0, 0);
  //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
  printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  
  //int opt = menuPrompt();
  menuPrompt();

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(2, 60);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.println("Test Motor");
  tft.println(" ");
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("Press/hold # to EXIT");

  /*
  if(opt)
    goto skip;
  */

  char keyIn = 's';
  //press/hold # to EXIT
  //this need to be looked at
  //sometimes it does NOT exit when # is pressed
  cycleCount = 0;
  int i = 1;
  unsigned long start = 0;
  unsigned long endTime = 0;
  while(keyIn != '#') {
    start = micros();
    for (; i <= stepsIndex; i++)
    {
      printInfo(rpm, angleIndex, cycleCount, 1, 0, 0);
      StepForward(delay_time);
      printInfo(rpm, angleIndex, cycleCount, 0, 1, 0);
      StepForward180(delay_time);
      
      stepCount += 1;
      cycleCount += 1;
  
      Serial.println(stepCount);
      Serial.println(cycleCount);
      
      keyIn = customKeypad.getKey();
      delay(10);
      if(keyIn == '#') break;
    }
    endTime = micros() - start;

    Serial.println(endTime);
    //delay(stepsPerRev);
//    p = analogRead(A0);
//    delay_time = map(p, 0, 1023, 50, 1000);

    //delay_time = 100;
    keyIn = customKeypad.getKey();
    printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  }
  //printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  //skip:
  delay(500);
  mainMenu();
}

//This function to test the solenoid
void solenoidTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3.5);
  tft.print("Test Solenoid");
  tft.println(" ");

  //printInfo(delay_time, 0, 0, 0, 0, 0);
  //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
  printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  
  //int opt = menuPrompt();
  menuPrompt();

  /*
  if(opt)
    goto skip;
  */

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(2, 60);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.print("Test Solenoid");
  tft.println(" ");
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("Press/hold # to EXIT");

  char keyIn = 's';
  //press/hold # to EXIT
  //this need to be looked at
  //sometimes it does NOT exit when # is pressed
  while(keyIn != '#') {
    //printInfo(delay_time, 0, 0, 0, 0, 1);
    //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 1);
    printInfo(rpm, angleIndex, cycleCount, 0, 0, 1);
    digitalWrite(sig, HIGH);
    delay(500);
    digitalWrite(sig, LOW);
    delay(500);
    printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
    //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
    //printInfo(delay_time, 0, 0, 0, 0, 0);
    
    keyIn = customKeypad.getKey();
  }
  //skip:
  //printInfo(delay_time, 0, 0, 0, 0, 0);
  //printInfo(delay_time, angleIndex, cycleCount, 0, 0, 0);
  printInfo(rpm, angleIndex, cycleCount, 0, 0, 0);
  delay(500);
  mainMenu();
}

//This function to test keypad and print the key pressed on the display
void keypadTest() {
  tft.fillScreen(ILI9341_BLACK);

  //print which key to press to exit keypad test mode
  tft.setCursor(100, 200);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.print("Press '#' to exit");
  
  //print Keypad TEST: at the top
  tft.setCursor(2, 0);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.println(" Keypad TEST:");
  tft.setTextSize(1);
  tft.println(" ");
  
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(4);
  char keyIn = 's';
  while(keyIn != '#') {
    keyIn = customKeypad.getKey();
    if (keyIn){
      tft.print(keyIn);
    }
  }
  delay(500);
  mainMenu();
}

//test display with different graphical test
void displayTest() {
  delay(10);
  testFillScreen();
  delay(500);

  testText();
  delay(3000);

  testLines(ILI9341_CYAN);
  delay(500);

  testFastLines(ILI9341_RED, ILI9341_BLUE);
  delay(500);

  testRects(ILI9341_GREEN);
  delay(500);

  testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA);
  delay(500);

  testFilledCircles(10, ILI9341_MAGENTA);

  testCircles(10, ILI9341_WHITE);
  delay(500);

  testTriangles();
  delay(500);

  testFilledTriangles();
  delay(500);

  testRoundRects();
  delay(500);

  testFilledRoundRects();
  delay(1000);

  mainMenu();
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
    tft.println("my foonting turlingdromes.hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  yield();
  
  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i*10, i*10));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i*10, i*10, 0));
    yield();
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
    yield();
  }

  return micros() - start;
}
