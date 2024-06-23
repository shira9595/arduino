#include <Servo.h>
int feedbackPin=A0;
int servoPin=9;
int feedback;
Servo MyServo;

void setup() {
Serial.begin(9600);
MyServo.attach(servoPin);
//MyServo.write(0);
}

void loop() {
while (true) {
  int random_pos=random(0,280);
  int PWM = map(random_pos,0,270,1000,2000);
  MyServo.writeMicroseconds(PWM);
  //Serial.print("desired angle:" +String(pos));
  Serial.print(random_pos);
  Serial.print(", ");
  delay(1500);
  feedback=analogRead(feedbackPin);
  //Serial.print("analog value is: " +String(feedback));
  //Serial.print(", ");
  //float feedback_angle = mapFloat(feedback,0.0,.0,0.0,280.0);
  int feedback_angle = map(feedback,27,817,0,270);
  //int actual_angle=-1.074581*feedback_angle+273.456922;
  //float actual_angle = -1.93539009*feedback_angle+393.1875363;
  //Serial.println("actual angle:" +String(feedback_angle));
  //Serial.println(actual_angle);
  Serial.println(feedback_angle);
  //delay(1000);
  }
}

//float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  //return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}
