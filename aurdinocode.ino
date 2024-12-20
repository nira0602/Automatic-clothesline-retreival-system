#include <Servo.h>

Servo tap_servo;
int sensor_pin = 4; 
int tap_servo_pin = 5;  // Servo connected to pin 5
int pop; 
int val;  // Variable to store the received POP value from Python

void setup() {
  tap_servo.attach(tap_servo_pin);  // Attach the servo to pin 5
  Serial.begin(9600);               // Start serial communication at 9600 baud rate
  Serial.println("Servo initialized. Waiting for POP values...");
}

void loop() {
  val = digitalRead(sensor_pin);    // Read the rain sensor value

  if (val == 0) {                   // No rain detected
    moveServoSlowly(0);             // Move servo to 0 degrees slowly
    Serial.println("Rain");
    delay(500);
  }
  
  if (val == 1) {                   // Rain detected
    moveServoSlowly(180);           // Move servo to 180 degrees slowly
    delay(500);
  }
  
  if (Serial.available() > 0) {     // If data is available on Serial
    pop = Serial.parseInt();        // Read the POP value sent from Python

    
    // Control the servo motor based on the POP value
    if (pop == 0) {
      Serial.println("No rain detected, moving servo to 0 degrees slowly.");        
    } 
    else if (pop > 0) {
      Serial.println("Rain detected, moving servo to 180 degrees slowly.");
      moveServoSlowly(180);         // Move the servo to 180 degrees slowly
    }
  }

  delay(500);  // Small delay for smooth operation
}

// Function to move servo to target position slowly
void moveServoSlowly(int targetAngle) {
  int currentAngle = tap_servo.read();  // Get the current angle of the servo
  if (currentAngle < targetAngle) {
    for (int angle = currentAngle; angle <= targetAngle; angle++) {
      tap_servo.write(angle);          // Incrementally move to target angle
      delay(10);                        // Small delay between steps for smooth movement
    }
  } else {
    for (int angle = currentAngle; angle >= targetAngle; angle--) {
      tap_servo.write(angle);          // Decrementally move to target angle
      delay(10);                        // Small delay between steps for smooth movement
    }
  }
}