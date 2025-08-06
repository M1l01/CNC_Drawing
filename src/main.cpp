#include <Arduino.h>

#define Module_IN1 2
#define Module_IN2 3
#define Module_IN3 4
#define Module_IN4 5

int step = 0;

// Function prototype
void OneStep(bool dir);

void setup() {
    pinMode(Module_IN1, OUTPUT);
    pinMode(Module_IN2, OUTPUT);
    pinMode(Module_IN3, OUTPUT);
    pinMode(Module_IN4, OUTPUT);
}

void loop() {
    OneStep(false);
    delay(2);
}

// Functions
void OneStep(bool dir) {
  if (dir) {
    switch (step){
    case 0:
      digitalWrite(Module_IN1, HIGH);
      digitalWrite(Module_IN2, LOW);
      digitalWrite(Module_IN3, LOW);
      digitalWrite(Module_IN4, LOW);
      break;
    case 1:
      digitalWrite(Module_IN1, LOW);
      digitalWrite(Module_IN2, HIGH);
      digitalWrite(Module_IN3, LOW);
      digitalWrite(Module_IN4, LOW);
      break;
    case 2:
      digitalWrite(Module_IN1, LOW);
      digitalWrite(Module_IN2, LOW);
      digitalWrite(Module_IN3, HIGH);
      digitalWrite(Module_IN4, LOW);
      break;
    case 3:
      digitalWrite(Module_IN1, LOW);
      digitalWrite(Module_IN2, LOW);
      digitalWrite(Module_IN3, LOW);
      digitalWrite(Module_IN4, HIGH);
      break;
    default:
      break;
    }
  }else{
    switch (step) {
    case 0:
      digitalWrite(Module_IN1, LOW);
      digitalWrite(Module_IN2, LOW);
      digitalWrite(Module_IN3, LOW);
      digitalWrite(Module_IN4, HIGH);
      break;
    case 1:
      digitalWrite(Module_IN1, LOW);
      digitalWrite(Module_IN2, LOW);
      digitalWrite(Module_IN3, HIGH);
      digitalWrite(Module_IN4, LOW);
      break;
    case 2:
      digitalWrite(Module_IN1, LOW);
      digitalWrite(Module_IN2, HIGH);
      digitalWrite(Module_IN3, LOW);
      digitalWrite(Module_IN4, LOW);
      break;
    case 3:
      digitalWrite(Module_IN1, HIGH);
      digitalWrite(Module_IN2, LOW);
      digitalWrite(Module_IN3, LOW);
      digitalWrite(Module_IN4, LOW);
      break;
    default:
      break;
    }
  }
  step++;
  if (step > 3) {
    step = 0;
  }
}