/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

byte onoff = digitalRead(13);
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.

}

// the loop function runs over and over again forever
void loop() {
  if (onoff == 1) {
    pinMode(13, OUTPUT);
  digitalWrite(13, 0);   // turn the LED on (HIGH is the voltage level)
  delay(3000);  // wait for a second
}
else
{
  pinMode(13, OUTPUT);
  digitalWrite(13, 1);    // turn the LED off by making the voltage LOW
  delay(3000);              // wait for a second
}
pinMode(13,INPUT);
}
