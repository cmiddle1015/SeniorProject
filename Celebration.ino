#include <Servo.h>

// Define servo motor
Servo myServo;

int angle = 0;
// Function to move servo from 0 to 180 degrees
void moveServo() {
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(10);  // Adjust the delay as needed
  }

  delay(20);  // Wait for 1 second at 180 degrees

  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(10);  // Adjust the delay as needed
  }

  delay(20);  // Wait for 
}

void setup() {
  // Attach the servo to pin 9
  myServo.attach(9);
}

void loop() {
  moveServo();  // Call the function to move the servo
}
