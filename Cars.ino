#include <Wire.h>

#define PIN_TRIG 12
#define PIN_ECHO 11

#define pin_L 4
#define pin_left 5
#define pin_R 7
#define pin_right 6

int IRpin = A0;

long duration, fdist;
int distance = 20;

void setup() {
  Serial.begin (9600);

  pinMode(pin_left, OUTPUT);
  pinMode(pin_right, OUTPUT);
  pinMode(pin_L, OUTPUT);
  pinMode(pin_R, OUTPUT);
  
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  
  int fdist = (duration / 2) / 29.1; // передний датчик расстояние
  front();
}

void front(){

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  fdist = (duration / 2) / 29.1; // передний датчик расстояние

  float volts = analogRead(IRpin)*0.0048828125;
  float ldist = 65*pow(volts, -1.10);

  
  delay(500);

  if (fdist >= 20){
    while (fdist >= 20 && ldist <= 30){

      Serial.println(fdist);
      Serial.println(ldist);
      delay(500);

      digitalWrite(pin_right, HIGH);                    // move forward
      digitalWrite(pin_R, HIGH);
      digitalWrite(pin_left, HIGH);                                
      digitalWrite(pin_L, HIGH);   // едет вперёд

      digitalWrite(PIN_TRIG, LOW);
      delayMicroseconds(5);
      digitalWrite(PIN_TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(PIN_TRIG, LOW);

      duration = pulseIn(PIN_ECHO, HIGH);
      fdist = (duration / 2) / 29.1; // передний датчик расстояние

      volts = analogRead(IRpin)*0.0048828125;
      ldist = 65*pow(volts, -1.10);
      
    }
  }
  if (ldist > 30){
    left();
    front();
  }
  stop();
}

void stop(){

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  fdist = (duration / 2) / 29.1; // передний датчик расстояние

  float volts = analogRead(IRpin)*0.0048828125;
  float ldist = 65*pow(volts, -1.10);

  Serial.println(ldist);
  delay(500);

  digitalWrite(pin_left, LOW);
  digitalWrite(pin_right, LOW); 

  if (fdist <= 20){
    right();
  }
  if (ldist >= 30){
    left();
  }
  front();
}

void right(){
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  fdist = (duration / 2) / 29.1; // передний датчик расстояние

  //Поварачивает на право, пока fdist <= 20
  while (fdist <= 20){
    digitalWrite(pin_left, HIGH);
    digitalWrite(pin_L, HIGH);

    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    duration = pulseIn(PIN_ECHO, HIGH);
    fdist = (duration / 2) / 29.1; // передний датчик расстояние
  }
  front();
}

void left(){
  
  
  float volts = analogRead(IRpin)*0.0048828125;
  float ldist = 65*pow(volts, -1.10);

  //Поварачивает на лево, пока ldist >= 30
  while (ldist >= 30){
    digitalWrite(pin_right, HIGH);
    digitalWrite(pin_R, HIGH);

    volts = analogRead(IRpin)*0.0048828125;
    ldist = 65*pow(volts, -1.10);
  }
  front();
}

