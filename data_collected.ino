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
for (float pos=0; pos <=280; pos +=random(281)){
  float PWM = mapFloat (pos,0.0,280.0,1000.0,2000.0);
  MyServo.writeMicroseconds((int)PWM);
  Serial.print("desired angle:" +String(pos));
  Serial.print(", ");
  feedback=analogRead(feedbackPin);
  Serial.print("analog value is: " +String(feedback));
  Serial.print(", ");
  //float feedback_angle = mapFloat(feedback,0.0,.0,0.0,280.0);
  float feedback_angle = mapFloat(feedback,27.0,817.0,0.0,280.0);
  //float actual_angle = -1.3259*feedback_angle+288.97;
  Serial.println("actual angle:" +String(feedback_angle));
  delay(1000);
  }
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
