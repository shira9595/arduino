#include <Servo.h>
int servoPin=9;
int feedbackPin=A0;
int feedbackValue;
int vibrationmotorPin=10;
Servo MyServo; //defining a nickname to my servo


void setup() {
 Serial.begin(9600); //defining a wanted baud rate
 MyServo.attach(servoPin);
 //MyServo.write(0); //determines the prinmal angle of the servo to be at zero regarding its own axes -- i need to think if i need this or its not necessary!!
 pinMode(vibrationmotorPin,OUTPUT); //define the vibration motor as a one who accepts an order from arduino
}

void loop() {
  if (Serial.available() >0){ //checks if the port is available to preform the assignment
    String(command) = Serial.readStringUntil('\n'); //the communication between python and arduino works by strings
    // Serial.println(String(command));
    if (command.startsWith("set_servo_angle:")){ 
      int desired_angle = command.substring(16).toInt(); // the specification of the substring finds the desired angle in the form of a string, i need to understand if its 18 or 15
      int PWM = map(desired_angle,0,270,1000,2000); // translating the wanted angle into PWM, so the servomotor can read it --- need to think if this range is good
      MyServo.writeMicroseconds(PWM); //transfer the PWM high voltage value to the servomotor, with the information recieved 
      //MyServo.write(desired_angle);
      delay(1000);//need to make sure this delay is suitble--
      int feedback = analogRead(feedbackPin); //reads the given voltage from the potentiometer about the angle the servo motor has reached to 
      int feedback_angle=map(feedback,27,817,0,280);
      //int actual_angle= -0.04 * feedback_angle + 257.19;
      //int actual_angle=-1.074581*feedback_angle+273.456922;
      //float actual_angle=-1.115075825*feedback_angle+296.8777877;
      //float actual_angle=-0.8968*feedback_angle+266.24;
      //float actual_angle = -1.93539009*feedback_angle+393.1875363;
      float actual_angle = -1.950438358*feedback_angle+394.3631753;
      Serial.println("Moved to angle:"+String(actual_angle)); // sending the needed string to python
      delay(1000);//need to make sure this delay is suitble
      
      String(command) = Serial.readStringUntil('\n'); //the communication between python and arduino works by strings
      if (command.startsWith("activate_vibrationmotor")){ 
        //Serial.println("vib_mot");
        digitalWrite(vibrationmotorPin,HIGH);
        delay(3000); // activiating the vibration motor for 3000ms, can be determined to any wanted value
        digitalWrite(vibrationmotorPin,LOW);
        Serial.println("vibration motor activated for 3 sec"); // sending the needed string to python
      } else {
        Serial.println("vibration motor wasn't activated");
      }
    }
  }    
}
