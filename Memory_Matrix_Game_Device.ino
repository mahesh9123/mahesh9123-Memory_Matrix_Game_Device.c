/************************************************************************************
*																					*
*  File Name	: Memory_Matrix_Game_Device.c
*  Contents	    : its an game device code which determine your capabilty to remember the colours.
*  Copyright	: own by mahesh vishnoi
*  Version	    : 1.0
*  controller   : AVR ATMEGA
*  Author       : Mahesh Vishnoi

***********************************************************************************/
//#ifdef F_CPU
//#undef F_CPU
//#define F_CPU 1000000L
//#endif

#include <FastLED.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3f, 16, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
// How many leds in your strip?
#define NUM_LEDS 6
#define DATA_PIN 2
#define CLOCK_PIN 13
#define RESET    3
#define RED      7
#define SKYBLUE  8
#define PINK     9
#define GREEN    6
#define BLUE     5
#define ORANGE   4
// Define the array of leds
CRGB leds[NUM_LEDS];
//CRGB light[7] = {CRGB::Black,CRGB::Green,CRGB::Blue,CRGB::Orange,CRGB::Red,CRGB::Red,CRGB::Red};
long int light[7] = {0x00FF00,0xFF00FF,0x00FFFF,0xFF0000,0x0000FF,0x40FF00,0x000000};

void(* resetFunc) (void) = 0;//declare reset function at address 0

int randNumber ,level=1;
bool start_game_flag;
int a[20],p[20],Score;

void setup() { 

FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
pinMode(3, INPUT);
pinMode(4, INPUT);
pinMode(5, INPUT);
pinMode(6, INPUT);
pinMode(7, INPUT);  
pinMode(8, INPUT);
pinMode(9, INPUT);
randomSeed(analogRead(7));
//lcd.begin();
//lcd.begin(16,2);
lcd.init();                      // initialize the lcd 
lcd.backlight();
lcd.setCursor(4,0); 
lcd.print("WELCOME");
delay(30);
start_game_flag=1;
level=1;

}

void loop() { 

//  leds[0] = CRGB::Green;              //red   RGB    note reverse RGB TO GRB
//  leds[1] = 0xFF00FF;;//CRGB::Blue;   //CYAN SKY BLUE
//  leds[2] = 0x00FFFF;                 //pink
//  leds[3] = CRGB::Red;                //Green            
//  leds[4] = 0x0000FF;                 //blue
//  leds[5] = 0x40FF00;                 //orange
//  FastLED.show();

//  level= Pressed_button();
//  FastLED.show();
//  lcd.clear();
//  lcd.setCursor(1,0);
//  lcd.print("  LEVEL = ");
//  lcd.print(level); //  lcd.print(n++,DEC);
//  start_game_flag=0;
  if(start_game_flag!=1)
  {
   start_game_key();

  }
  if(digitalRead(3))
  {
    while(digitalRead(3));
    resetFunc();  //call reset
  }
 if(start_game_flag==1)
  {
    start_game_flag=0;
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    FastLED.show();
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("  LEVEL = ");
    lcd.print(level); //  lcd.print(n++,DEC);
    delay(1000);
    for(int j=0;j<=(level-1);j++)
    {
      lcd.clear();
      lcd.setCursor(3,0); //First line
      lcd.print(" REMEMBER ");
      lcd.setCursor(2,1); //First line
      lcd.print("LIGHT COLOR ");
      randNumber = random(0, 5);// print a random number from 1 to 5
//      Serial.println(randNumber);
      leds[randNumber] = light[randNumber]; 
      FastLED.show();
      delay(600);
      leds[randNumber] = light[6];
      FastLED.show();
      delay(350);
      a[j]=randNumber;
 //     Serial.println("randNumber");
 //     Serial.println(randNumber);
    }
    for(int k=0;k<=(level-1);k++)
    {
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      FastLED.show();
      delay(60);
      lcd.clear();
      lcd.setCursor(0,0); //First line
      lcd.print("   PRESS ");
      lcd_print_colour_order(k+1);
      lcd.setCursor(0,1);
      lcd.print(" COLOR BUTTON ");
//      lcd.setCursor(0,1); 
//      lcd.print("PRESS BUTTON");
      p[k]=Pressed_button();
      FastLED.show();
//      Serial.println(p[k]);
      delay(400);
     }
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
    delay(60);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print(" RESULT... ");
    delay(1200);
    int m=0;
    for(int l=0;l<=(level-1);l++)
    {
      if(p[l] == a[l])
        {
         m++;
        }
    }
//    Serial.println("m");
//    Serial.println(m);
    if(m==level)
    {
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("YOU WON LEVEL");
     delay(1800);
     m=0;
     level++;
     start_game_flag=1;
    }
    
    else
    {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("YOU LOSE LEVEL ");
    lcd.print(level);
    lcd.setCursor(1,1);
    lcd.print("  SCORE = ");
    lcd.print(level*level);
    delay(3500);
    Score=level*level;
    print_memory_power();
    m=0;
    level=1;
    Score=0;
    start_game_flag=0;
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("THANK YOU");
    delay(2500);
  }
  }     
  else 
  {
    lcd.setCursor(1,0); 
    lcd.print("PRESS ANY KEY ");
    lcd.setCursor(4,1); 
    lcd.print("To START ");
    delay(300);
  }
 
}


void start_game_key()
{
  if(digitalRead(3))
  {
    while(digitalRead(3));
    resetFunc();  //call reset
  }
}

int Pressed_button()
{
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
  while(1)
  {
  if(digitalRead(RED))
  {
    while(digitalRead(RED));
    leds[0] = light[0];
    return 0;
  }
    if(digitalRead(SKYBLUE))
  {  
    while(digitalRead(SKYBLUE));
    leds[1] = light[1];
    return 1;
  }
  if(digitalRead(PINK))
  {
    while(digitalRead(PINK));
    leds[2] = light[2];
    return 2;
  }
  if(digitalRead(GREEN))
  {
    while(digitalRead(GREEN));
    leds[3] = light[3];
    return 3;
  }
    if(digitalRead(BLUE))
  {
    while(digitalRead(BLUE));
    leds[4] = light[4];
    return 4;
  }
//    if(digitalRead(4))
//  {
//    while(digitalRead(4));
//    leds[5] = light[5];
//    return 6; 
//  }
  if(digitalRead(3))
  {
    while(digitalRead(3));
    resetFunc();  //call reset
  }
  
  }
}

void print_memory_power()
{         
          lcd.clear();
          lcd.setCursor(0,1); 
          lcd.print("  MEMORY POWER ");

          if(Score<=4)
          {
          lcd.setCursor(0,0);
          lcd.print("     LOW      ");
          delay(2000);
          }
          else if((Score >= 5) && (Score <=17))
          {
          lcd.setCursor(0,0);
          lcd.print("    AVERAGE   ");
          delay(2000);
          }
          else if((Score >= 18) && (Score <=37))
          {
          lcd.setCursor(0,0);
          lcd.print("     GOOD   ");
          delay(2000);
          }
          else if((Score >= 38) && (Score <=63))
          {
          lcd.setCursor(0,0);
          lcd.print("    HIGH    ");
          delay(2000);
          }
          else if(Score >= 64)
          {
          lcd.setCursor(0,0);
          lcd.print("   EXCELLENT   ");
          delay(2000);
          }
}

void lcd_print_colour_order(int var)
{
          switch (var) {
               case 1:
                 lcd.print("1st");
                 break;
               case 2:
                 lcd.print("2nd");
                 break;
               case 3:
                 lcd.print("3rd");
                 break;
               case 4:
                 lcd.print("4th");
                 break;
               case 5:
                 lcd.print("5th");
                 break;
               case 6:
                 lcd.print("6th");
                 break;
               case 7:
                 lcd.print("7th");
                 break;
               case 8:
                 lcd.print("8th");
                 break;               
               case 9:
                 lcd.print("9th");
                 break;
               case 10:
                 lcd.print("10th");
                 break;

               default: 
                  lcd.print("next");
                  break;
             }
}
