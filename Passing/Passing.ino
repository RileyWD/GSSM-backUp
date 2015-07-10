#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>
#include <NewPing.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

/* Define Constants */
const float cos30sin60 = sqrt(3.0) / 2.0; // cos(30 deg) = sin(60 deg), need for wheel

// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors
const byte SONIC_TRIGGER_PIN = 50;
const byte SONIC_ECHO_PIN = 51;

// Parameters controlling program behavior
// Bump behavior
const byte FORWARD_SPEED = 150;   // Define normal speeds
const byte BACKWARD_SPEED = 100;  // and backup/turn speed
const int  TURN_DURATION = 600;   // Turn length in milliseconds

// Sonic sensor
const float TARGET_DISTANCE_INCHES = 10; 
const int MAX_SONIC_DISTANCE = 500;      // cm, optional, 500 cm is default

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);

/* Define new untrasonic sensor with trigger & echo pins and 
   the maximum distance to be sensed. */
NewPing sonic(SONIC_TRIGGER_PIN, SONIC_ECHO_PIN, MAX_SONIC_DISTANCE); 
float direction;       // Velocity Vector Angle (DEGREES) from forward to drive
float magnitude;       // Magnitude (0-100) of movement vector in given direction
float duration;        // Duration to drive at given velocity vector

byte motorLeftdir;     // Clockwise or Counter clockwise for the 3 wheels
byte motorBackdir;
byte motorRightdir;


void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
   motorBack->run(RELEASE);
  Serial.begin(9600);  //Begin serial communcation
  
  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit, 
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN,INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN,INPUT_PULLUP);

  //  pinMode(SONIC_TRIGGER_PIN,OUTPUT);
  //  pinMode(SONIC_ECHO_PIN,INPUT);
  delay(2000);  // Two second delay to get the robot placed
}

void loop(){
  // Test some of the sonic library functions:
  int inches = sonic.ping_in();
  Serial.print(inches);
  Serial.print(" inches, cm = ");
  Serial.print(sonic.ping_cm());
  Serial.print(", actual ping time (ms) = ");
  int ping_milli = sonic.ping();
  Serial.print(ping_milli);
  Serial.print(", real inches = ");
  Serial.print(Distance_inches(ping_milli));
  Serial.print(", real cm = ");
  Serial.println(Distance_cm(ping_milli));
  // delay(100); // Just to slow things down

  /*  Assuming no switches closed initially.  Drive forward: */
  motorLeft->setSpeed(FORWARD_SPEED);
  motorRight->setSpeed(FORWARD_SPEED);
  motorBack->setSpeed(FORWARD_SPEED);
  while (Distance_inches(sonic.ping()) > TARGET_DISTANCE_INCHES) {
    
  }
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);
  delay(1000);
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  delay(500);
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  delay(500);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

/* float Distance_inches(int ping) { */
/*   float inches_per_sec = 13582.67;  // Equivilent to 345 m/s */
/*   return ping * inches_per_sec * 1e-6 *0.5; */
/* } */

/* float Distance_cm(int ping) { */
/*   float cm_per_sec = 34500.;        // Equivilent to 345 m/s */
/*   return ping * cm_per_sec * 1e-6 *0.5; */
/* } */
