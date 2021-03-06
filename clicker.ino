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

//i'm adding LEDs that light up when you press a button, just because i have some now
#define ledPinA 8
#define ledPinB 9
#define ledPinC 10

Adafruit_SSD1306 disp(OLED_DC, OLED_RESET, OLED_CS);

unsigned int credit = 0;
unsigned int farm = 0;

unsigned int plusClick = 10;
unsigned int plusFarm = 1;

unsigned int costFarm = 100;

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
  disp.println("Clicker++");
  disp.display();
  //setup LEDs
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  digitalWrite(ledPinA, HIGH);
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinC, HIGH);

  delay(1000);

  //turn off those LEDs!
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinC, LOW);
}

void loop() {
  //read button A
  bStateA = digitalRead(bPinA);
  if(bStateA != bStateA1) {
    if(bStateA == HIGH) {
      digitalWrite(ledPinA, HIGH);
      add_credits(plusClick);
    } else {
      digitalWrite(ledPinA, LOW);
      
    }
    //delay(10);
  }  
  bStateA1 = bStateA;
  //read button B
  bStateB = digitalRead(bPinB);
  if(bStateB != bStateB1) {
    if(bStateB == HIGH) {
      digitalWrite(ledPinB, HIGH);
      if(credit >= costFarm) {
        credit -= costFarm;
        farm ++;
      }
    } else {
      digitalWrite(ledPinB, LOW);
      
    }
    //delay(10);
  }  
  bStateB1 = bStateB;
  //read button C
  bStateC = digitalRead(bPinC);
  if(bStateC != bStateC1) {
    if(bStateC == HIGH) {
      digitalWrite(ledPinC, HIGH);
      add_credits(10000);
    } else {
      digitalWrite(ledPinC, LOW);
      
    }
    //delay(10);
  }  
  bStateC1 = bStateC;

  //once per <interval>
  cMillis = millis();
  if(cMillis - pMillis >= interval) {
    pMillis = cMillis;

    add_credits(farm * plusFarm);
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

void add_credits(int in) {
  if(credit + in >= credit) {
    credit += in;
  } else {
    while(credit + 1 > credit) {
      credit ++;
    }
  }
}
