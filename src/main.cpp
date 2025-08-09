#include <Arduino.h>

// Motor 1 control pins
#define Module1_IN1 4
#define Module1_IN2 5
#define Module1_IN3 6
#define Module1_IN4 7

// Motor 2 control pins
#define Module2_IN1 8
#define Module2_IN2 9
#define Module2_IN3 10
#define Module2_IN4 11

// Control de Sentido
#define BTN_DIR 2
#define BTN_ON_OFF 3

int step = 0;
bool system_state = false; // System state: off
bool direction_state = false; // Direction: CCW

// Function prototype
void OneStep(bool dir, int IN1, int IN2, int IN3, int IN4);
void StopMotor(int IN1, int IN2, int IN3, int IN4);
void direction_callback(void);
void on_off_callback(void);

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

    pinMode(BTN_DIR, INPUT);
    pinMode(BTN_ON_OFF, INPUT);

    // Configuration of interrupts pins
    attachInterrupt(digitalPinToInterrupt(BTN_DIR), direction_callback, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_ON_OFF), on_off_callback, RISING);
}

void loop() {
  // Check if the system is ON
  if (system_state) {
    // Perform one step in the selected direction
    OneStep(direction_state, Module2_IN1, Module2_IN2, Module2_IN3, Module2_IN4);
    delay(3);
  } else {
    Serial.println("System is OFF");
    StopMotor(Module2_IN1, Module2_IN2, Module2_IN3, Module2_IN4);
  }
}

// Functions
// Callback function to change the state of the system (on/off)
void on_off_callback(void) {
  delay(20); // Debounce delay
  system_state = !system_state; // Toggle system state
}

// Callback function to change the direction of the motor
void direction_callback(void) {
  delay(20); // Debounce delay
  direction_state = !direction_state; // Toggle direction state
}

// Funtion to stop the motor
void StopMotor(int IN1, int IN2, int IN3, int IN4) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Function to perform one step of the stepper motor
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