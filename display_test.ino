
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Keypad.h>
#include <Stepper.h>

const int stepsPerRevolution = 100;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39, 41, 43, 45}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

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
  // set the speed at 60 rpm (Stepper Motor)
  myStepper.setSpeed(150);
  Serial.begin(9600);
 
  tft.begin();
  tft.setRotation(1);
  //set display 240 X 320
  LCD_Init();
 
  mainMenu();
}

void loop(void) {

  char customKey = customKeypad.getKey();
  if (customKey){
  switch (customKey) {
  case 'A': // Display Test
    //tft.fillScreen(ILI9341_YELLOW);
    displayTest();
    break;
  case 'B': // Motor Test
    //tft.fillScreen(ILI9341_GREEN);
    motorTest();
    break;
  case 'C': // Solenoid Test
    solenoidTest();
    break;
  case 'D': // Keypad Test    mainMenu();
    //tft.fillScreen(ILI9341_RED);
    keypadTest();
    break;
  case '#': // Main Menu
    mainMenu();
    break;
  default:
    //tft.fillRect(20, 190, 100, 32,ILI9341_GREEN);
    tft.setCursor(20, 190);
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
    tft.print("Invalid Option ...");
    delay(1000);
    break;
    }
  } 
  delay(10);
}

//This function to print main menu and options
void mainMenu() {
  tft.fillScreen(ILI9341_NAVY);
  tft.setCursor(5,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
  tft.println("--Main Menu--");
  tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(3);
  tft.println(" A. Display  Test");
  tft.println(" B. Motor    Test");
  tft.println(" C. Solenoid Test");
  tft.println(" D. Keypad   Test");
}

//This function to test the solenoid
void motorTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(40, 60);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.println("Test Motor");
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println(" ");
  tft.println("Press 1 to START");
  tft.println("Press/hold # to EXIT");

  char keyIn = 0;
  while((customKeypad.getKey()) != '1');
  while(keyIn != '#') {
    // step one revolution  in one direction:
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    //delay(100);

    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    //delay(100);
    
    keyIn = customKeypad.getKey();
  }
  delay(500);
  mainMenu();
}

//This function to test the solenoid
void solenoidTest() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(2, 100);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.print("Test Solenoid");
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
  char keyIn = 1;
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
