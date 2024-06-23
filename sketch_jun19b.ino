#include <Servo.h>
int feedbackPin=A0;
int servoPin=9;
int feedback;
Servo MyServo;
int angle=-120;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  MyServo.attach(servoPin);
}

void loop() {
  // int PWM = map(angle,0,280,1000,2000);
  // MyServo.writeMicroseconds(PWM);
  MyServo.write(angle);
  delay(100);
  feedback=analogRead(feedbackPin);
 
  Serial.println(feedback);
  delay(100);
}
