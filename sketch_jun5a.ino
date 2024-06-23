#include <Servo.h>

int servoPin = 9;
int feedbackPin = A0;
int vibrationmotorPin = 10;
Servo MyServo;

void setup() {
  Serial.begin(9600);
  MyServo.attach(servoPin);
  MyServo.write(0);
  pinMode(vibrationmotorPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    
    if (command.startsWith("set_servo_angle:")) {
      int desired_angle = command.substring(16).toInt();
      int PWM = map(desired_angle, 0, 280, 1000, 2000);
      MyServo.writeMicroseconds(PWM);
      delay(1000);
      int feedback = analogRead(feedbackPin);
      int feedback_angle = map(feedback, 27, 817, 0, 280);
      int actual_angle = -1.074581 * feedback_angle + 273.456922;
      Serial.println("Moved to angle:" + String(actual_angle));
    } else if (command == "activate_vibrationmotor") {
      digitalWrite(vibrationmotorPin, HIGH);
      Serial.println("vibration motor activated");
      delay(1000); // Activate the vibration motor for 3 seconds
      digitalWrite(vibrationmotorPin, LOW);
      Serial.println("vibration motor deactivated");
    } else {
      Serial.println("Invalid command");
    }
  }
}