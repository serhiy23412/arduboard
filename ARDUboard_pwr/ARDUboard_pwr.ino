
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define SAMPLES 1000
#define LDO 3.25
#define DCDC 5.15
#define VCC LDO
#define Rs 0.1
#define CURR_CONST VCC/(Rs*1000)
#define VOLT_CONST 6*VCC/1024

#define L1 10
#define L2 9
#define H1 13
#define H2 12

#define LED1 0
#define LED2 1
#define LED3 4
#define LED4 5

#define BUZ 5

#define ENC_A 7
#define ENC_B 8
#define ENC_BUT 6

#define RES A0
#define SENSE A7

#define BUT1 3
#define BUT2 2


void full_bridge(char polarity, char pwm)
{
  if(polarity)
  {
    digitalWrite(L1, LOW);
    digitalWrite(H2, LOW);
    digitalWrite(H1, HIGH);
    analogWrite(L2, pwm);
  }
  else
  {
    digitalWrite(L2, LOW);
    digitalWrite(H1, LOW);
    digitalWrite(H2, HIGH);
    analogWrite(L1, pwm);
  }
}

void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);

   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.display();

   Serial.begin(9600);
}

void loop() 
{
  full_bridge(digitalRead(BUT1), analogRead(RES)/4);

int val = 0;
unsigned long val1 = 0;
int temp = 0;
int i = 0;

while(i<SAMPLES)
{
  val = val + analogRead(A7);
  val1 = val1 + analogRead(A6);
  i = i + 1;
}

delay(100);
 
    display.clearDisplay();
    display.setCursor(0, 0);
    temp = val1*VOLT_CONST;
    display.print("V= ");
    display.print(temp, DEC);
    display.println("mV");
    
    display.print("I= ");
    temp = val*CURR_CONST;
    display.print(temp, DEC);
    display.print("mA");
    display.display();
  
}
