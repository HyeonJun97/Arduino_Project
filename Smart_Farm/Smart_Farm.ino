#define DC_N 22
#define DC_P 24
#define DC_En A15
#define TEMP A4
#define SW 13
#define CDS A1
#define LED 12
#include "DHT.h"
#include <LiquidCrystal.h>

int Mode=0;
int pin_SIGNAL = 3 ;
int temp;
int tmp ;
DHT dht(TEMP, DHT11) ;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7) ;
int lcd_key = 0 ;


void setup(void)
{
 Serial.begin(9600) ;
 dht.begin();
 pinMode(SW, INPUT_PULLUP) ;
 pinMode(TEMP, INPUT);
 pinMode(DC_N, OUTPUT) ;
 pinMode(DC_P, OUTPUT) ;
 pinMode(DC_En, OUTPUT) ;
 pinMode(CDS, INPUT) ;
 pinMode(LED, OUTPUT) ;
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
 analogWrite(10, 255);
 lcd.begin(16,2) ;
 lcd.setCursor(0,0) ;
}

void SW_config(){                              //스위치
  if(digitalRead(SW)==0)
    {
      Mode +=1;
      delay(200) ;
     }
      
    if(Mode==5)
    {
      Mode=1;
    }
}

void Temperature() {                          //온도인식
  temp = dht.readTemperature();
  Serial.print("Temperature : ") ;
  Serial.print(temp) ;
  Serial.println(" [C] ") ;
  lcd.clear() ;
  lcd.setCursor(0,0) ;
  lcd.print("Temperature : ") ;
  lcd.print(temp) ;
  lcd.println(" [C] ") ;
  delay(500);
  }

void Auto() {                                 //자동모드
  tmp = dht.readTemperature() ;
  if(tmp<=25){
    digitalWrite(DC_N, LOW) ;
    digitalWrite(DC_P, HIGH) ;
    analogWrite(DC_En, 180) ;
  }
  if(25<tmp && tmp<30){
    digitalWrite(DC_N, LOW) ;
    digitalWrite(DC_P, HIGH) ;
    analogWrite(DC_En, 150) ;
  }
  if(tmp>=30){
    digitalWrite(DC_N, LOW) ;
    digitalWrite(DC_P, LOW) ;
  }
}

void Direction_rotation(int Mode)        //모드1~4지정
{
  if(Mode==1)
  {
      Auto() ; 
  }
  
  if (Mode==2)
  {
    digitalWrite(DC_N, LOW) ;
    digitalWrite(DC_P, HIGH) ;
    analogWrite(DC_En, 150) ;
  }
  
  if(Mode==3)
  {
    digitalWrite(DC_N, LOW) ;
    digitalWrite(DC_P, HIGH) ;
    analogWrite(DC_En, 180) ;   
  }
 if(Mode==4)
 {
    digitalWrite(DC_N, LOW) ;
    digitalWrite(DC_P, LOW) ;
 }
}

void Light(){                            //LED 제어
  if(analogRead(CDS)>=330){
    digitalWrite(LED, LOW) ;
    lcd.setCursor(0,1) ;
    lcd.println("Light : OFF") ;
  }
  else{
  digitalWrite(LED, HIGH);
  lcd.setCursor(0,1) ;
  lcd.println("Light : ON") ;
  }
  delay(300);
}

void loop(void)
{
    SW_config() ;
    Temperature() ;
    Serial.println(Mode) ;
    Direction_rotation(Mode) ;
    Serial.println(analogRead(CDS)) ;
    Light() ;
}
