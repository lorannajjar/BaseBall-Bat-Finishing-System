#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Keypad.h>

//defining new colors
#define ILI9341_GRAY 0xA510
//
#define HALL_SENSOR      41

//Stepper motors variables/setup
int CLOCK1 = 11, DIR1 = 23, CLOCK2 = 12, DIR2 = 24;

//to track time
//unsigned long start = 0;
unsigned long endTime = 0;

int stepCount = 1;
int cycleCount = 1;
int stepsPerRev = 2000;

float angleIndex = 5;
float stepsIndex = 360/angleIndex;


float anglePoly = 0.5;
//float stepsPoly = stepsPerRev/anglePoly;


float rpm = 180;

float delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;

float setPsi = 20;
float batLength = 24;
float lengthToRub = batLength - 20;

float batCircum = 8.2;
float woodType = 0;

//Solenoid setup
int sig = 1;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
/*
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
*/

char hexaKeys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};


byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// For the Adafruit shield, these are the default.
#define TFT_DC 29
#define TFT_CS 27

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

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
  pinMode(HALL_SENSOR, INPUT);

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
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.85);
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
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.8);
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
    changeValues(batLength, 5, 24, 36, "Set Bat Length");
    lengthToRub = batLength - 20;
    //operations();
    AllTest();
    userModeMenu();
    break;

  case 'B': // Configuration
    configurations();
    userModeMenu();
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


void configurations (){
  char configKey = NULL;
 

  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3.30);
  tft.println("-Configurations-");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.75);
  tft.println(" Select Configuration");
  tft.setTextSize(2);
  tft.println(" (1) 180 RPM");
  tft.println(" (2) 150 RPM");
  tft.println(" (3) 120 RPM");
  tft.println(" (4) 100 RPM");
  tft.println(" #. User mode Menu");

  while (configKey == NULL) {
    configKey = customKeypad.getKey();
  }

  //add rpm, angle of rotation, polyangle
  if (configKey){
  switch (configKey) {
  case '1': // bat 1
    rpm = 180;
    delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    break;
  case '2': // bat 2
    rpm = 150;
    delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    break;
  case '3': // bat 3
    rpm = 120;
    delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    break;
  case '4': //bat 4
    rpm = 100;
    delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
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
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2.8);
  tft.println("Configuration set!");
  tft.setTextSize(0.6);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  ///tft.print("Speed is set !! "); tft.println(batLength);
  tft.print("Travel Speed: "); tft.println(rpm);
  //tft.print("Rotational Angle: "); tft.println(angleIndex);
  tft.println(" ");
  tft.println(" ");
  tft.setTextColor(ILI9341_RED);tft.setTextSize(2.25);
  tft.println("Press '#' to return to user mode menu");

  while (configKey != '#') {
    configKey = customKeypad.getKey();
  }
  //mainMenu();

  
}

//This function to print developer mode menu and options
void developerModeMenu() {

  char developerModeKey = NULL;
  
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2.75);
  tft.println("-Developer Mode-");
  tft.setTextSize(0.6);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2.5);
  tft.println(" 0. Start");
  tft.println(" 1. Bat Length");
  tft.println(" 2. Speed");
  tft.println(" 3. Rotation Angle");
  tft.println(" 4. Set pressure/PSI");
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
  case '0': // bat length
    AllTest();
    developerModeMenu();
    break;
  case '1': // bat length
    changeValues(batLength, 5, 24, 36, "Bat Length");
    lengthToRub = batLength - 20;
    developerModeMenu();
    break;
  case '2': // travel speed
    //function under test
    changeValues(rpm, 10, 10, 300, "RPM SPEED");
    delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
    developerModeMenu();
    break;
  case '3': // rotation angle
    //add function to change rotation angle
    changeValues(angleIndex, 5, 1, 30, "rotation angle");
    stepsIndex = 360/angleIndex;
    developerModeMenu();
    break;
    /*
  case '4': // poly angle
    //add function to change poly angle
    changeValues(anglePoly, 2, 0.1, 4, "poly angle");
    stepsPoly = stepsPerRev/anglePoly;
    developerModeMenu();
    break;
    */
  case '4': // Change PSI/pressure
    //add function to change poly angle
    changeValues(setPsi, 10, 1, 40, "Pressure PSI");
    developerModeMenu();
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
  float temSpeed = -1;
  float minChange = .1;
  float midChange = 1;
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(20, 10);
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(3.5);
  tft.println(textName);
  tft.setTextSize(1); tft.println("");
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2); tft.print(" 1 Down - 3 Up By: "); tft.println(changeBy); tft.setTextSize(1); tft.println("");
  tft.setTextSize(2); tft.print(" 4 Down - 6 Up By: "); tft.println(midChange); tft.setTextSize(1); tft.println("");
  tft.setTextSize(2); tft.print(" 7 Down - 9 Up By: "); tft.println(minChange); tft.setTextSize(1); tft.println("");

  tft.setTextSize(2); tft.setCursor(130, 220); tft.setTextColor(ILI9341_GREEN); tft.println("press # to exit");

  tft.setTextSize(2);
  tft.setCursor(20, 158);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.print(textName);tft.print(": "); 
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.print(input);

  char keyIn = 's';
  while(keyIn != '#') {
    //display updated value everytime we increase/decrease speed
    if(temSpeed != input) {
      if(input > maxValue) input = maxValue;
      if(input < minValue) input = minValue;
      temSpeed = input;
      tft.setTextSize(2);
      tft.setCursor(20, 158);
      tft.print(textName);tft.print(": "); 
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.print(input);tft.print("  ");
    }

    //if 1 speed - changeBy
    if(keyIn == '1') {
      if(input > minValue) {
        input -= changeBy;
      }
    } 
    //if 3 speed + changeBy
    else if(keyIn == '3') {
      if(input < maxValue) {
        input += changeBy;
      }
    }
    else if(keyIn == '4') {
      if(input > minValue) {
        input -= midChange;
      }
    }
    else if(keyIn == '6') {
      if(input < maxValue) {
        input += midChange;
      }
    }
    else if(keyIn == '7') {
      if(input > minValue) {
        input -= minChange;
      }
    }
    else if(keyIn == '9') {
      if(input < maxValue) {
        input += minChange;
      }
    }
    delay(30);
    keyIn = customKeypad.getKey();
  }
}

//This function to print test menu and options
void testModeMenu() {
  //define default values here
  //No changes to any of these values in the TEST MODE
  //purpose of it just to check if all the components works
  batLength = 24;
  lengthToRub = batLength - 20;
  rpm = 100;
  angleIndex = 15;
  //anglePoly = 2;

  //calculate with these default values
  delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;
  stepsIndex = 360/angleIndex;
  //stepsPoly = stepsPerRev/anglePoly;
  
  char testModeKey = NULL;
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
  tft.println("-Test Mode-");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(3);
  tft.println(" A. Display  Test");
  tft.println(" B. Motor    Test");
  tft.println(" C. Solenoid Test");
  tft.println(" D. Keypad   Test");
  //tft.println(" 0. All      Test");
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
    testModeMenu();
    break;
  case 'B': // motor test
    motorTest();
    testModeMenu();
    break;
  case 'C': // solenoid test
    solenoidTest();
    testModeMenu();
    break;
  case 'D': // keypad test
    keypadTest();
    testModeMenu();
    break;
    /*
  case '0': // ALL parts test
    AllTest(); 
    break;
    */
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
void StepForward()
{
  digitalWrite(DIR1, LOW);
  
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

//delay_time for stepper motor speed
//solenoidMode '0' to disable or '1' to enable solenoid
void StepForward180()
{
  digitalWrite(DIR2, HIGH);

  for (int x = 0; x < (307.6923 * lengthToRub); x++)
  {
      digitalWrite(CLOCK2, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK2, LOW);
      delayMicroseconds(delay_time);
  }
   delay(delay_time);
    
  digitalWrite(DIR2, LOW);

  while(digitalRead(HALL_SENSOR) == HIGH)
  {
    digitalWrite(CLOCK2, HIGH);
    delayMicroseconds(delay_time);
    digitalWrite(CLOCK2, LOW);
    delayMicroseconds(delay_time);
    cycleCount+1; 
  }
  delay(delay_time);
}

void calibrate()
{
  digitalWrite(DIR2, LOW);
  while(digitalRead(HALL_SENSOR) == HIGH)
  {
    digitalWrite(CLOCK2, HIGH);
    delayMicroseconds(1500);
    digitalWrite(CLOCK2, LOW);
    delayMicroseconds(1500);
  }
  delay(delay_time);
}

//make 2 boxes and display informations
//display motors informations such as speed, direction
//function update both boxes
//maybe add a feature to only
//update the needed box(both, box1, box2)
void printInfo(float mValue, float mValue2, int mValue3, float mValue4, int motorEN, int motorEN2, int solenoidEN) {
  float timeCount = (endTime/1000000);
  
  //display motors and info
  tft.drawRect(10,130, 170, 85, ILI9341_RED);
  tft.drawRect(11,131, 168, 83, ILI9341_RED);
  tft.setCursor(14, 134);
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);  tft.setTextSize(1);
  tft.print("Motor RPM      : "); tft.print(mValue);tft.println("  ");
  tft.setCursor(14, 144); 
  tft.print("Rotation Angle : "); tft.print(mValue2);tft.println("  ");
  //tft.setCursor(14, 154); 
  //tft.print("Poly Angle     : "); tft.print(mValue4);tft.println("  ");
  tft.setCursor(14, 154); 
  tft.print("batLength      : "); tft.print(batLength);tft.println("  ");
  tft.setCursor(14, 164); 
  tft.print("Set PSI To     : "); tft.print(setPsi);tft.println("  ");
  tft.setCursor(14, 174); 
  tft.print("Cycle          : "); tft.print(mValue3);tft.println("  ");
  tft.setCursor(14, 184); 
  tft.print("Time           : "); tft.print(timeCount/60);tft.print("  ");
  tft.setCursor(14, 194); 
  tft.print("lengthToRub    : "); tft.print(lengthToRub);tft.print("  ");
  
  //display motor on/off - solenoid on/off
  //tft.fillRect(155,150, 140, 35, ILI9341_BLACK);
  tft.drawRect(190,130, 102, 35, ILI9341_RED);
  tft.drawRect(191,131, 100, 33, ILI9341_RED);
  tft.setCursor(194, 134);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.print("Motor 1 : ");
  if(!motorEN) {
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK); tft.println("OFF");
  } else {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); tft.println("ON ");
  }

  tft.setCursor(194, 144); tft.setTextColor(ILI9341_BLUE);
  tft.print("Motor 2 : ");
  if(!motorEN2) { 
    tft.setTextColor(ILI9341_RED, ILI9341_BLACK); tft.println("OFF");
  } else {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); tft.println("ON ");
  }
  tft.setCursor(194, 154); tft.setTextColor(ILI9341_BLUE); 
  tft.print("Solenoid: ");
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
  tft.setCursor(1, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3);
  tft.println("Rubbing Process");
  tft.println(" ");

  cycleCount = 0;
  endTime = 0;
  char keyIn = 's';
  printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);

  int opt = menuPrompt();

  if(!opt) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 30);
    tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3);
    tft.println("Rubbing Process");
    tft.println(" ");
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    //tft.println("Press/hold # to EXIT");
    //char keyIn = 's';
    //press/hold # to EXIT
    //this need to be looked at
    //sometimes it does NOT exit when # is pressed
    //cycleCount = 0;
    printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 1);
    int i = 1;
    unsigned long start = 0;

      start = micros();
      calibrate();
      digitalWrite(sig, HIGH);
      //for (; i <= stepsIndex; i++)
      //keyIn = NULL;
      while(i <= stepsIndex)
      {
        printInfo(rpm, angleIndex, cycleCount, anglePoly, 1, 0, 1);
        StepForward180();
        printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 1, 1);
        StepForward();
      
        stepCount += 1;
        cycleCount += 1;

        if(i == stepsIndex) {
          endTime = micros() - start;
        }
        
        i++;
      }
      digitalWrite(sig, LOW);
      printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);

      keyIn = '7';
      while(keyIn != '#') {
        keyIn = customKeypad.getKey();
      }
    }
    
  delay(500);
  //mainMenu();
}


//This function to test the solenoid
void motorTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.println("Test Motor");
  tft.println(" ");

  cycleCount = 0;
  endTime = 0;
  char keyIn = 's';
  printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);
  
  int opt = menuPrompt();

  if(!opt) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 30);
    tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
    tft.println("Test Motor");
    tft.println(" ");
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    //tft.println("Press/hold # to EXIT");

    //char keyIn = 's';
    //press/hold # to EXIT
    //this need to be looked at
    //sometimes it does NOT exit when # is pressed
    cycleCount = 0;
    int i = 1;
    unsigned long start = 0;
      start = micros();
      //2-5 just to make sure motors are working
      calibrate();
      for (; i <= 3; i++)
      {
        //tft.setTextSize(2); tft.setTextColor(ILI9341_RED, ILI9341_YELLOW); tft.print(setdir);
        printInfo(rpm, angleIndex, cycleCount, anglePoly, 1, 0, 0);
        StepForward180();
        printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 1, 0);
        StepForward();
      
        stepCount += 1;
        cycleCount += 1;
      }
      endTime = micros() - start;   
      printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);
      
      keyIn = '7';
      while(keyIn != '#') {
        keyIn = customKeypad.getKey();
      }
    }
    
  delay(500);
  //mainMenu();
}

//This function to test the solenoid
void solenoidTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3);
  tft.print("Test Solenoid");
  tft.println(" ");

  printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);
  
  int opt = menuPrompt();
  
  if(!opt) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 30);
    tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(3);
    tft.print("Test Solenoid");
    tft.println(" ");
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.println(" ");
    //tft.println("Press/hold # to EXIT");

    char keyIn = 's';
    //press/hold # to EXIT
    //this need to be looked at
    //sometimes it does NOT exit when # is pressed
    int j;
    for(j = 0; j < 3; j++) {
      printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 1);
      digitalWrite(sig, HIGH);
      delay(500);
      digitalWrite(sig, LOW);
      delay(500);
      printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);
    
      //keyIn = customKeypad.getKey();
    }
  }
  printInfo(rpm, angleIndex, cycleCount, anglePoly, 0, 0, 0);
  delay(500);
  //mainMenu();
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
  //mainMenu();
}

//test display with different graphical test
void displayTest() {
  delay(10);
  testFillScreen();
  delay(2000);

  //mainMenu();
}

unsigned long testFillScreen() {
  //unsigned long start = micros();
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
  //return micros() - start;
}
