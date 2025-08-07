#include <Arduino.h>

// Motor 1 control pins
#define Module1_IN1 2
#define Module1_IN2 3
#define Module1_IN3 4
#define Module1_IN4 5

// Motor 2 control pins
#define Module2_IN1 6
#define Module2_IN2 7
#define Module2_IN3 8
#define Module2_IN4 9

int cont_step = 0;
int steps_per_rev = 2064;
int step = 0;

// Function prototype
void OneStep(bool dir, int IN1, int IN2, int IN3, int IN4);

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    pinMode(Module1_IN1, OUTPUT);
    pinMode(Module1_IN2, OUTPUT);
    pinMode(Module1_IN3, OUTPUT);
    pinMode(Module1_IN4, OUTPUT);

    pinMode(Module2_IN1, OUTPUT);
    pinMode(Module2_IN2, OUTPUT);
    pinMode(Module2_IN3, OUTPUT);
    pinMode(Module2_IN4, OUTPUT);
}

void loop() {
    if (cont_step <= steps_per_rev) {
      //OneStep(true, Module1_IN1, Module1_IN2, Module1_IN3, Module1_IN4); // Motor 1 Rotate clockwise
      OneStep(true, Module2_IN1, Module2_IN2, Module2_IN3, Module2_IN4); // Motor 2 Rotate clockwise
      cont_step++;
      delay(3);
    }
}

// Functions
void OneStep(bool dir, int IN1, int IN2, int IN3, int IN4) {
  if (dir) {
    // Advance step
    step++;
    if (step > 3) {
      step = 0;
    }
  }else {
    // Reverse step
    step--;
    if (step < 0) {
      step = 3;
    }
  }

  switch (step) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    default:
      break;
  }
}