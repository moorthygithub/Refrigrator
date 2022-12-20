#include "max6675.h"
#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
int t;
int SetPoint;
const int pot_key=A0;
const int LED_RED=10; //Red LED
const int LED_GREEN=11; //Green LED=
const int RELAY=12; //Lock Relay or motor
const int RELAY2=13;
int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

void do_max6675_loop(void)
{
   Serial.print("Temp = ");
   int t = ktc.readCelsius();
   u8g.setPrintPos(90, 30);
   u8g.println(t);
   Serial.print(t);
   Serial.print(" Deg C");
}

void draw(void){
  Serial.begin(9600);
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("PORTABLE REFRIGERATOR");
  u8g.setPrintPos(0, 30);
  u8g.print("TEMPERATURE :");
  do_max6675_loop();
  u8g.setPrintPos(0, 50);
  u8g.print("SET POINT   :");
  u8g.setPrintPos(90, 50);
  u8g.print(SetPoint);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);  
  pinMode(RELAY,OUTPUT);  

  pinMode(RELAY2,OUTPUT);  
  pinMode(pot_key,INPUT);
 
  digitalWrite(LED_GREEN,HIGH);  //Green LED On
  digitalWrite(LED_RED,LOW);     //Red LED Off
  digitalWrite(RELAY,LOW);       //Turn off Relay
  delay(2000);
}
void loop(void)
{

  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage() );
  delay(3500);
  u8g.firstPage();
 
  SetPoint = analogRead(pot_key);
  SetPoint = map( SetPoint, 0, 1023, 5, 25);
  delay(100);

  if(t < SetPoint)
   {
   digitalWrite(RELAY,LOW);
   digitalWrite(RELAY2,LOW);    //Turn off fan
   digitalWrite(LED_RED,LOW);
   digitalWrite(LED_GREEN,HIGH);  //Turn on Green LED
   }
else
   {
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY,HIGH);    //Turn on fan
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED  
   }
   
   do_max6675_loop();
   Serial.print("\n");
   delay(500);
}
