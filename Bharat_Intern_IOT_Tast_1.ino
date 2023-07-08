#include <Servo.h>

// Pin connections
const int trigPinA = 3;       // Ultrasonic sensor 1 trigger pin
const int echoPinA = 4;       // Ultrasonic sensor 1 echo pin
const int trigPinB = 12;      // Ultrasonic sensor 2 trigger pin
const int echoPinB = 11;      // Ultrasonic sensor 2 echo pin
const int ledPinA = 5;        // LED pin
const int ledPinB = 10;       // LED pin
const int buzzerPinA = 6;     // Buzzer A
const int buzzerPinB = 9;     // Buzzer A
const int servoMotorAPin = 2; // Servo Motor A
const int servoMotorBPin = 8; // Servo Motor B

Servo servoMotorA;            // Servo object for Motor A
Servo servoMotorB;            // Servo object for Motor B

void setup() {
  // Initialize the pins
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(buzzerPinA, OUTPUT);
  pinMode(buzzerPinB, OUTPUT);
  // Attach the servo motors to their respective pins
  servoMotorA.attach(servoMotorAPin);
  servoMotorA.write(90);// Closed Gates
  servoMotorB.attach(servoMotorBPin);
  servoMotorB.write(90);// Closed Gates
  // Initialize the serial communication
  Serial.begin(9600);
}
void loop() {
  int distanceA = measureDistance(trigPinA, echoPinA); // Measure distance from Ultrasonic sensor 1
  int distanceB = measureDistance(trigPinB, echoPinB); // Measure distance from Ultrasonic sensor 2
  // Car approaching first parking space
  if (distanceA < 40 && distanceA > 20 ) {
    servoMotorA.write(0); // Open Gate
    digitalWrite(ledPinA, HIGH);
    digitalWrite(buzzerPinA, HIGH);
    Serial.println("Car approaching parking space 1");
  }
  // Car inside first parking space
  if (distanceA < 40 && distanceA < 20 ) {
    servoMotorA.write(180);// Close Gate
    digitalWrite(ledPinA, HIGH);
    digitalWrite(buzzerPinA, LOW);
    Serial.println("Car parked in space 1");
  }
  // Car left first parking space
  if (distanceA > 40) {
    servoMotorA.write(180);// Close Gate
    digitalWrite(ledPinA, LOW);
    digitalWrite(buzzerPinA, LOW);
    Serial.println("Space 1 empty");
  }
  // Car approaching the second parking space
  if (distanceB < 40 && distanceB > 20) {
    servoMotorB.write(0);// Open Gate
    digitalWrite(ledPinB, HIGH);
    digitalWrite(buzzerPinB, HIGH);
    Serial.println("Car approaching parking space 2");
  }
  // Car inside second parking space
  if (distanceB < 40 && distanceB < 20) {
    servoMotorB.write(180);// Close Gate
    digitalWrite(ledPinB, HIGH);
    digitalWrite(buzzerPinB, LOW);
    Serial.println("Car parked in space 2");
  }
  // Car left second parking space
  else if (distanceB > 40) {
    servoMotorB.write(180);// Close Gate
    digitalWrite(ledPinB, LOW);
    digitalWrite(buzzerPinB, LOW);
    Serial.println("Space 2 empty");
  }
  delay(100);
}
int measureDistance(int triggerPin, int echoPin) {
  // Measure the distance using the ultrasonic sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  // Read the echo pulse duration
  long duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in centimeters
  int distance = duration * 0.034 / 2;
  return distance;
}
