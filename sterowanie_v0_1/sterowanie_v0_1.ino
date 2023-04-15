// A0 - Błękitny, wewnętrzny
// A1 - Zielony, zewnętrzny
// Błękitny do białego drukarki
// Fioletowy do czarnego drukarki
#include <Arduino.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 60 // domyślnie 120

int in1 = 0;
int lastIn = 0;
int count = 0;
int stanMoj = 0; //Zmienna określająca stan drukarki
char sensor[4] = {0, 1, 3, 2}; 

void setup() 
{
  Serial.begin(9600); 
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(10, LOW);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, OUTPUT);
}

void loop() 
{
  in1 = digitalRead(A0)|digitalRead(A1)<<1;
  Serial.println(in1);


  if(in1 == 1 || in1 == 2)
  {
    stanMoj = in1;
    count = 0;
  }
  else //jesli nic sie nie zmienia, to chwile czekamy, czy to nie suszum
  {
    count++;
    if(count > 30) //bezwladnosc ukladu, filtruje przypadkowe sygnaly
    {
      stanMoj = in1;
    }
  }
  if(stanMoj == 2)
  { //tu jest problem
    if(count > 300)
    {
      digitalWrite(2, HIGH); 
    }
    else
    {
      digitalWrite(2, LOW); 
    }
    //Serial.println("wysoko");
  }
  else 
  { //tu jest problem
    if(count > 300)
    {
      digitalWrite(2, LOW);
    }
    else
    {
      digitalWrite(2, HIGH);
    }
    
    //Serial.println("nisko");
  }
  Serial.print("\t");
  delay(1);
}
