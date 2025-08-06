#include <Arduino.h>

#define Module_IN1 2
#define Module_IN2 3
#define Module_IN3 4
#define Module_IN4 5

int cont_step = 0;
int steps_per_rev = 2064;
int step = 0;

// Function prototype
void OneStep(bool dir);

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    pinMode(Module_IN1, OUTPUT);
    pinMode(Module_IN2, OUTPUT);
    pinMode(Module_IN3, OUTPUT);
    pinMode(Module_IN4, OUTPUT);
}

void loop() {
    if (cont_step <= steps_per_rev) {
      OneStep(true); // Rotate clockwise
      cont_step++;
      delay(2);
    }
}

// Functions
void OneStep(bool dir) {
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
}