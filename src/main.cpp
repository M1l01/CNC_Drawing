#include <Arduino.h>
#include <Servo.h>

// Motor 1 control pins
#define Module1_IN1 4
#define Module1_IN2 5
#define Module1_IN3 6
#define Module1_IN4 7

// Motor 2 control pins
#define Module2_IN1 8
#define Module2_IN2 10
#define Module2_IN3 11
#define Module2_IN4 12

// Control de Sentido
//#define BTN_DIR 2
#define BTN_ON_OFF 3

int step = 0;
bool system_state = false; // System state: off
bool direction_state = true; // Direction: CW

int cont_steps = 0; // Step counter
int max_steps = 7732; // Maximum steps for a full translation (15 cm)

long valor_pot;
float sp_posicion; // Setpoint position in mm (0-150)
float paso_mm = 0.0194; // mm per step
int sp_step;

// Define Servo Motor
Servo ServoSketcher;

// Function prototype
void OneStep(bool dir, int IN1, int IN2, int IN3, int IN4);
void StopMotor(int IN1, int IN2, int IN3, int IN4);
//void direction_callback(void);
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

    //pinMode(BTN_DIR, INPUT);
    pinMode(BTN_ON_OFF, INPUT);

    // Configure the pin for the Servo motor
    ServoSketcher.attach(9); // Attach the servo to pin 9
    ServoSketcher.write(70); // Initialize servo position to 0 degrees

    // Configuration of interrupts pins
    //attachInterrupt(digitalPinToInterrupt(BTN_DIR), direction_callback, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_ON_OFF), on_off_callback, RISING);

    Serial.print("Setpoint position (steps): ");
    Serial.println(sp_step);
}

void loop() {
  // Read the potenciometer value (0-1023)
  valor_pot = analogRead(A0);
  sp_posicion = map(valor_pot, 0, 1023, 0, 150); // Map to range 0-150 mm
  sp_step = sp_posicion/paso_mm; // Convert to steps

  // Check if the system is ON
  if (system_state) {

    // Identify the direction of the movement
    if (sp_step == cont_steps) {
      system_state = false;
    } else if (sp_step > cont_steps) {
      direction_state = true; // Direction CW - Right
    } else {
      direction_state = false; // Direction CCW - Left
    }

    // Check Saturation of steps counter
    // Direction: CW - Right
    if (direction_state) {
      // Check for saturation of steps
      if (cont_steps >= max_steps){
        cont_steps = max_steps;
      } else {
        cont_steps++;
      }
    // Direction: CCW - Left
    }else {
      // Check for saturation of steps
      if (cont_steps <= 0){
        cont_steps = 0;
      } else {
        cont_steps--;
      }
    }

    // Move the motor one step
    OneStep(direction_state, Module2_IN1, Module2_IN2, Module2_IN3, Module2_IN4);
    delay(3);

  } else {
    StopMotor(Module1_IN1, Module1_IN2, Module1_IN3, Module1_IN4); // Ensure Motor 1 is stopped
    StopMotor(Module2_IN1, Module2_IN2, Module2_IN3, Module2_IN4); // Ensure Motor 2 is stopped
  }
}

// ********************* Functions *********************

// Callback function to change the state of the system (on/off)
void on_off_callback(void) {
  delay(20); // Debounce delay
  system_state = !system_state; // Toggle system state
}

// Callback function to change the direction of the motor
/*void direction_callback(void) {
  delay(20); // Debounce delay
  direction_state = !direction_state; // Toggle direction state
  //Serial.print("Direction state: ");
  //Serial.println(direction_state);
}*/

// Funtion to stop the motor
void StopMotor(int IN1, int IN2, int IN3, int IN4) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Function to perform one step of the stepper motor
void OneStep(bool dir, int IN1, int IN2, int IN3, int IN4) {
  // Counter of steps and saturation
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