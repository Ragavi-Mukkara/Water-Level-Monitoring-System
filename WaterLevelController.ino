// Define Ultrasonic Sensor PinsA
#define TRIG_TANK 3
#define ECHO_TANK 2
#define TRIG_SUMP 5
#define ECHO_SUMP 4
// Define Relay for Motor Control
#define MOTOR_RELAY 6
// Define Thresholds (in cm)
const int TANK_LOW = 15; // Adjust based on tank size
const int TANK_HIGH = 80; // Adjust based on tank size
const int SUMP_LOW = 10; // Adjust based on sump capacity
// Function to measure distance using Ultrasonic Sensor
long getDistance(int trigPin, int echoPin) {
 long total = 0;

 int readings = 5; // Take 5 samples for better accuracy
 for (int i = 0; i < readings; i++) {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 long duration = pulseIn(echoPin, HIGH);
 total += duration * 0.034 / 2; // Convert to cm
 delay(10); // Small delay between readings
 }
 return total / readings; // Return average value
}
void setup() {
 pinMode(TRIG_TANK, OUTPUT);
 pinMode(ECHO_TANK, INPUT);
 pinMode(TRIG_SUMP, OUTPUT);
 pinMode(ECHO_SUMP, INPUT);
 pinMode(MOTOR_RELAY, OUTPUT);
 digitalWrite(MOTOR_RELAY, LOW); // Ensure motor is OFF at start
 Serial.begin(9600);
}
void loop() {
 long tankLevel = getDistance(TRIG_TANK, ECHO_TANK);
 long sumpLevel = getDistance(TRIG_SUMP, ECHO_SUMP);
 Serial.print("Tank Level: "); Serial.print(tankLevel); Serial.print(" cm, ");
 Serial.print("Sump Level: "); Serial.print(sumpLevel); Serial.println(" cm");
 // Turn ON Motor: If Tank Level is LOW and Sump Level is OK
 if (tankLevel <= TANK_LOW && sumpLevel > SUMP_LOW) {
 digitalWrite(MOTOR_RELAY, HIGH); // Turn ON Motor
 Serial.println("Motor ON");
 }
 // Turn OFF Motor: If Tank is Full OR Sump Level is too Low
 if (tankLevel >= TANK_HIGH || sumpLevel <= SUMP_LOW) {
 digitalWrite(MOTOR_RELAY, LOW); // Turn OFF Motor
 Serial.println("Motor OFF");
 }
 delay(2000); // Wait before next reading
}
