#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define L1 10 // можно отключать на плате перемычкой
#define L2 9  // можно отключать на плате перемычкой
#define H1 13 // можно отключать или переназначить на плате перемычкой
#define H2 12 // можно отключать или переназначить на плате перемычкой 

#define LED1 0
#define LED2 1
#define LED3 4
#define LED4 5

#define BUZ 5  // можно отключать на плате перемычкой

#define ENC_A 7
#define ENC_B 8
#define ENC_BUT 6

#define RES A0

#define BUT1 3
#define BUT2 2

int brightness = 255;     
int fadeAmount = 5; 
unsigned char cnt;    

unsigned long currentTime;
unsigned long loopTime;
unsigned char edge;


Servo myservo;

void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  //pinMode(LED4, OUTPUT);

  myservo.attach(A2); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.display();

 
}

void loop() 
{
 
 unsigned int analog_mem = analogRead(RES)/4;
    
    digitalWrite(LED1, !digitalRead(BUT2));
    digitalWrite(LED2, !digitalRead(BUT1));
    digitalWrite(LED3, !digitalRead(ENC_BUT));
    analogWrite(LED4, brightness);  
    
    myservo.write(analog_mem); 

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Servo     ");
    display.print(analog_mem, DEC);
    display.display();
    
                                
}
