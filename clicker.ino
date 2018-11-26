#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//SPI pins
#define OLED_DC 4
#define OLED_CS 0xff
#define OLED_RESET 7

//button pins
#define bPinA 5
#define bPinB 2
#define bPinC 3

Adafruit_SSD1306 disp(OLED_DC, OLED_RESET, OLED_CS);

int credit = 0;
int farm = 0;

int bStateA = 0;
int bStateA1 = 0;
int bStateB = 0;
int bStateB1 = 0;
int bStateC = 0;
int bStateC1 = 0;

const long interval = 1000;
unsigned long cMillis = 0;
unsigned long pMillis = 0;

void setup() {
  //init
  Serial.begin(9600); //what does this do?
  disp.begin(SSD1306_SWITCHCAPVCC);
  disp.clearDisplay();
  //splash screen
  disp.setTextSize(2);
  disp.setTextColor(WHITE);
  disp.setCursor(0,20);
  disp.println("XDRduino");
  disp.display(); 
  delay(1000);
}

void loop() {
  //read button A
  bStateA = digitalRead(bPinA);
  if(bStateA != bStateA1) {
    if(bStateA == HIGH) {
      credit ++;
    } else {
      
    }
    //delay(10);
  }  
  bStateA1 = bStateA;
  //read button B
  bStateB = digitalRead(bPinB);
  if(bStateB != bStateB1) {
    if(bStateB == HIGH) {
      if(credit >= 10) {
        credit -= 10;
        farm ++;
      }
    } else {
      
    }
    //delay(10);
  }  
  bStateB1 = bStateB;
  //read button C
  bStateC = digitalRead(bPinC);
  if(bStateC != bStateC1) {
    if(bStateC == HIGH) {
      
    } else {
      
    }
    //delay(10);
  }  
  bStateC1 = bStateC;

  //once per <interval>
  cMillis = millis();
  if(cMillis - pMillis >= interval) {
    pMillis = cMillis;

    credit += (farm * 2);
  }

  //refresh screen
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setCursor(0,0);
  disp.println("CREDITS:");
  disp.setCursor(0,8);
  disp.println(credit);
  disp.setCursor(0,16);
  disp.println("FARMS:");
  disp.setCursor(0,24);
  disp.println(farm);
  disp.display();
}