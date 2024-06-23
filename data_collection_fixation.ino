#include <Servo.h>

int feedbackPin = A0; // Analog pin for feedback
int servoPin = 9;     // PWM pin for servo
Servo MyServo;

// Define an array of known angles for calibration
int angles[] = {0, 45, 90, 135, 180, 225, 280};
int numAngles = sizeof(angles) / sizeof(angles[0]);

// Function to read the analog feedback value multiple times and return the average
int readAverageFeedback(int numReadings) {
  long sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(feedbackPin);
    delay(10); // Small delay between readings
  }
  return sum / numReadings;
}

// Function to map feedback to angle using a more refined mapping
float mapFeedbackToAngle(int feedback) {
  if (feedback >= 564) {
    return map(feedback, 812, 564, 0, 90); // Map feedback values to 0-90 degrees
  } else if (feedback >= 182) {
    return map(feedback, 564, 182, 90, 225); // Map feedback values to 90-225 degrees
  } else {
    return map(feedback, 182, 33, 225, 280); // Map feedback values to 225-280 degrees
  }
}

void setup() {
  Serial.begin(9600);        // Initialize serial communication
  MyServo.attach(servoPin);  // Attach the servo to the specified pin
}

void loop() {
  for (int i = 0; i < numAngles; i++) {
    int pos = angles[i];
    // Convert the angle to a microsecond value for the servo
    int PWM = map(pos, 0, 280, 1000, 2000); // Adjust the range if necessary
    MyServo.writeMicroseconds(PWM); // Write PWM to servo
    
    // Allow some time for the servo to reach the position
    delay(2000);
    
    // Read the average analog feedback value
    int feedback = readAverageFeedback(10); // Take 10 readings and average them

    // Map the feedback to an angle
    float mappedAngle = mapFeedbackToAngle(feedback);
    
    // Debugging output to check the raw feedback and mapped angle
    Serial.print("Desired Angle: ");
    Serial.print(pos);
    Serial.print(", PWM: ");
    Serial.print(PWM);
    Serial.print(", Raw Feedback: ");
    Serial.print(analogRead(feedbackPin)); // Print a single raw reading for reference
    Serial.print(", Averaged Feedback: ");
    Serial.print(feedback);
    Serial.print(", Mapped Angle: ");
    Serial.println(mappedAngle);
    
    // Wait a moment before moving to the next position
    delay(1000);
  }
  
  // Optional: Pause after completing one full sweep
  Serial.println("Calibration cycle complete. Restarting...");
  delay(5000);
}